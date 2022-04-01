#include "BlackJack.h"



string AI::turn(string options[], int length, PacketManager& pM, queue<int> values, dealer* deal, SOCKET* connection, int index) {	// random choice until a good algorithm can be implemented

	PacketRoundUpdate* pkt = new PacketRoundUpdate();
	int output_values[MAX_PLAYERS]; // values in never changing order

		for (int i = 0; i < values.size() - index; i++) { // if index == 0 dont change if index == 1 rotate by 3 meaning back to original | repeat
			int temp = 0;
			temp = values.front();
			values.pop();
			values.push(temp);
		}

	
	for (int i = 0; i < values.size(); i++) {
		int temp = 0;
		temp = values.front();
		output_values[i] = temp;
		values.pop();
		values.push(temp);
	}
	
	int numValues = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (output_values[i] > 0) {
			numValues++;
		}
		else {
			break;
		}
	}

	pkt->setTotalGameValues(numValues);
	pkt->setGameValues(output_values);
	pkt->setDealerValue(deal->getCardTotal() - deal->hiddenCard->getValue());
	pkt->setSequence(pM.getPacket()->getSequence());
	pM = PacketManager(pkt->serialize());
	//Sleep(50);

	sendClientPacket(*connection, pM);
	Sleep(3000);
	// chance to break
	float break_Card = BROKEVALUE - (this->getCardTotal());
	//	////cout << "\nbreak card : " << break_Card << "\n";
		 // 21 - 12 = 9 + 1 = 10 is break
	float breakodds = (13 - (break_Card - 1)) / 13;
	//cout << "\nChance to break : %" << breakodds << "\n";
	if (length < 4) { // game choices
		if (breakodds > this->standValue) {
			return options[0];
		}
		else {
			return options[1];
		}
	}
	else { // bet choices
		float WL;
		if (this->games != 0) {
			WL = this->wins / this->games;
		}
		else {
			WL = 50;
		}
		if (WL <= 25) { // if computer wins less then 25%
			return options[0]; // bet 5
		}
		else if (WL > 25 && WL <= 50) { // win loss is 26-50%
			return options[1]; // bet 10
		}
		else if (WL > 50 && WL <= 75) { // win loss is 51-75%
			return options[2]; // bet 20
		}
		else if (WL > 75) { // win loss is greater then 75%
			return options[3]; // bet 50
		}
	}
	int choice = rand() % length;
	return options[choice];

}
bool AI::getCard(card* card) {
	if (this->hiddenCard == NULL) {
		this->hiddenCard = card;
		return true;
	}
	else {
		for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
			if (this->publicCard[i] == NULL) {
				this->publicCard[i] = card;
				return true;
			}
		}
	}
	return false;
}
int AI::getCardTotal() {
	int total = 0;
	switch (this->hiddenCard->getValue()) {
	case 11: // jack
		total += 10;
		break;
	case 12: // queen
		total += 10;
		break;
	case 13: // king
		total += 10;
		break;
	case 14: // ace
		if ((total + 11) > BROKEVALUE) {
			total += 1;
		}
		else {
			total += 11;
		}
		break;
	default:
		total += this->hiddenCard->getValue();
		break;
	}
	int ace = 0;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		switch (publicCard[i]->getValue()) {
		case 11: // jack
			total += 10;
			break;
		case 12: // queen
			total += 10;
			break;
		case 13: // king
			total += 10;
			break;
		case 14: // ace
			ace++;
			break;
		default:
			total += publicCard[i]->getValue();
			break;
		}
	}
	if (ace > 0) { // NOTE ----------------------- this algorithem is only good if they have one ace if they have more then one this needs to be revised
		if (total + (11 * ace) > BROKEVALUE) {
			total += (1 * ace);
		}
		else {
			total += (11 * ace);
		}
	}
	return total;
}
void AI::reset() {
	this->hiddenCard = NULL;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		this->publicCard[i] = NULL;
	}
	this->status = 'i';
}

void player::reset() {
	this->hiddenCard = NULL;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		this->publicCard[i] = NULL;
	}
	this->status = 'i';
}
void dealer::reset() {
	this->hiddenCard = NULL;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		this->publicCard[i] = NULL;
	}
	this->status = 'i';
}

string player::turn(PacketManager &pM, string options[], int length, queue<int> values, dealer* deal,int index) {	// random choice until a good algorithm can be implemented
	int choice = 0;
	PacketPlayerTurn* pkt = new PacketPlayerTurn();
	if (this->acc->getFunds() < 0) {
		return options[2];
	}

	int output_values[MAX_PLAYERS]; // values in never changing order

	for (int i = 0; i < values.size() - index; i++) { // if index == 0 dont change if index == 1 rotate by 3 meaning back to original | repeat
		int temp = 0;
		temp = values.front();
		values.pop();
		values.push(temp);
	}


	for (int i = 0; i < values.size(); i++) {
		int temp = 0;
		temp = values.front();
		output_values[i] = temp;
		values.pop();
		values.push(temp);
	}

	int numValues = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (output_values[i] > 0) {
			numValues++;
		}
		else {
			break;
		}
	}


	pkt->setTotalGameValues(numValues);
	pkt->setGameValues(output_values);
	pkt->setDealerValue(deal->getCardTotal() - deal->hiddenCard->getValue());
	pkt->setSequence(pM.getPacket()->getSequence());
	pkt->setOptions(options);
	pkt->setOptionSize(length);
	pkt->setPublicCards(this->publicCard);
	pkt->setPrivateCard(*this->hiddenCard);
	pM = PacketManager(pkt->serialize());
	//Sleep(50);
	
	sendClientPacket(*this->acc->connection, pM);

	//sequence[0] = pM->getPacket()->getSequence();
	//send(*acc->connection, pM.getPacket()->serialize(), maxPacketSize, 0);
	//cout << "\n\n " << "WSA ERROR : " << "\n\n";

	//char RxBuffer[maxPacketSize] = {};

	//pkt = new PacketPlayerTurn(pM.getPacket()->serialize());

	//recv(*acc->connection, RxBuffer, maxPacketSize, 0);

	pkt = new PacketPlayerTurn(pM.getPacket()->serialize());
	return options[pkt->getOption() - 1];
}


bool player::getCard(card* card) {
	if (this->hiddenCard == NULL) {
		this->hiddenCard = card;
		return true;
	}
	else {
		for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
			if (this->publicCard[i] == NULL) {
				this->publicCard[i] = card;
				return true;
			}
		}
	}
	return false;
}
int player::getCardTotal() {
	int total = 0;
	switch (this->hiddenCard->getValue()) {
	case 11: // jack
		total += 10;
		break;
	case 12: // queen
		total += 10;
		break;
	case 13: // king
		total += 10;
		break;
	case 14: // ace
		if ((total + 11) > BROKEVALUE) {
			total += 1;
		}
		else {
			total += 11;
		}
		break;
	default:
		total += this->hiddenCard->getValue();
		break;
	}
	int ace = 0;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		switch (publicCard[i]->getValue()) {
		case 11: // jack
			total += 10;
			break;
		case 12: // queen
			total += 10;
			break;
		case 13: // king
			total += 10;
			break;
		case 14: // ace
			ace++;
			break;
		default:
			total += publicCard[i]->getValue();
			break;
		}
	}
	if (ace > 0) { // NOTE ----------------------- this algorithem is only good if they have one ace if they have more then one this needs to be revised
		if (total + (11 * ace) > BROKEVALUE) {
			total += (1 * ace);
		}
		else {
			total += (11 * ace);
		}
	}
	return total;
}
player::player(account* acc) {

	this->acc = acc;
}
bool dealer::getCard(card* card) {
	if (this->hiddenCard == NULL) {
		this->hiddenCard = card;
		return true;
	}
	else {
		for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
			if (this->publicCard[i] == NULL) {
				this->publicCard[i] = card;
				return true;
			}
		}
	}
	return false;
}
string dealer::turn(string options[], int length) {
	if (this->getCardTotal() >= 17) {
		return options[0];
	}
	else {
		return options[1];
	}
}
int dealer::getCardTotal() {
	int total = 0;
	switch (this->hiddenCard->getValue()) {
	case 11: // jack
		total += 10;
		break;
	case 12: // queen
		total += 10;
		break;
	case 13: // king
		total += 10;
		break;
	case 14: // ace
		if ((total + 11) > BROKEVALUE) {
			total += 1;
		}
		else {
			total += 11;
		}
		break;
	default:
		total += this->hiddenCard->getValue();
		break;
	}
	int ace = 0;
	for (int i = 0; i < MAX_PUBLIC_CARDS; i++) {
		switch (publicCard[i]->getValue()) {
		case 11: // jack
			total += 10;
			break;
		case 12: // queen
			total += 10;
			break;
		case 13: // king
			total += 10;
			break;
		case 14: // ace
			ace++;
			break;
		default:
			total += publicCard[i]->getValue();
			break;
		}
	}
	if (ace > 0) { // NOTE ----------------------- this algorithem is only good if they have one ace if they have more then one this needs to be revised
		if (total + (11 * ace) > BROKEVALUE) {
			total += (1 * ace);
		}
		else {
			total += (11 * ace);
		}
	}
	return total;
}
void blackjack::takeBets(PacketManager &pM) {
	////cout << "Bets in";
	int bets[] = { 5,10,20,50 };
	string options[] = { "Bet 5", "Bet 10", "Bet 20", "bet 50" };
	int b = 0;
	int i = 0;
	queue<int> computer_values;


	//player
	for (int b = 0; b < computer_values.size(); b++) {
		computer_values.pop();
	}
	for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
		computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
		AI* comp = this->computers.front(); // set first player 
		this->computers.pop(); // front player from front of queue
		this->computers.push(comp); // inserts front player to back of queue
	}
	while (i != this->players.size()) {
		string input = this->players.front()->turn(pM, options, 4, computer_values,this->deal,i);
		for (int c = 0; c < sizeof(bets) / sizeof(int); c++) {
			if (input == options[c]) {
				b = c;
			}
		}

		this->deal->bets[i] = bets[b]; // gets players bet choice and converts it to a bet to go to the dealer
		this->players.front()->acc->reduceFunds(bets[b]);
		player* p1 = this->players.front(); // set first player 
		this->players.pop(); // front player from front of queue
		this->players.push(p1); // inserts front player to back of queue
		i++;
	}
	// player


	//computer
	while (i != this->computers.size() + this->players.size()) {
		int z = computer_values.size();
		for (int b = 0; b < z; b++) {
			computer_values.pop();
		}
		for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
			computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
			AI* comp = this->computers.front(); // set first player 
			this->computers.pop(); // front player from front of queue
			this->computers.push(comp); // inserts front player to back of queue
		}
		string input = this->computers.front()->turn(options, 4,pM,computer_values,this->deal,this->players.front()->acc->connection,(i-players.size()));
		for (int c = 0; c < sizeof(bets) / sizeof(int); c++) {
			if (input == options[c]) {
				b = c;
			}
		}


		this->deal->bets[i] = bets[b]; // gets players bet choice and converts it to a bet to go to the dealer
		this->computers.front()->funds -= bets[b];

		AI* comp = this->computers.front(); // set first player 
		this->computers.pop(); // front player from front of queue
		this->computers.push(comp); // inserts front player to back of queue
		i++;
	}
	//computer
}
void blackjack::dealBets() {
	//cout << "Bets delt";
	int i = 0;

	while (i != this->players.size()) {
		if (this->players.front()->getCardTotal() > BROKEVALUE) {

		}
		else if (this->players.front()->status == 105 && this->deal->status != 105) { // if player is still in and has a greater hand then the dealer
			this->players.front()->acc->addFunds(this->deal->bets[i] * 2);
		}
		else if (this->players.front()->status == 105 && this->players.front()->getCardTotal() > this->deal->getCardTotal()) {
			this->players.front()->acc->addFunds(this->deal->bets[i] * 2);
		}
		player* p1 = this->players.front(); // set first player 
		this->players.pop(); // front player from front of queue
		this->players.push(p1); // inserts front player to back of queue
		i++;
	} // pay out all players |ORDER MATTERS

	while (i != this->computers.size() + this->players.size()) {
		if (this->computers.front()->getCardTotal() > BROKEVALUE) {
			this->loss++;
			this->computers.front()->games++;
		}
		else if (this->computers.front()->status == 105 && this->deal->status != 105) { // if computer is still in and has a greater total then the dealer
			this->computers.front()->funds += this->deal->bets[i] * 2;
			this->computers.front()->wins++;
			this->computers.front()->games++;
			this->win++;
		}
		else if (this->computers.front()->status == 105 && this->computers.front()->getCardTotal() > this->deal->getCardTotal()) {
			this->computers.front()->funds += this->deal->bets[i] * 2;
			this->computers.front()->wins++;
			this->computers.front()->games++;
			this->win++;
		}
		else {
			this->computers.front()->games++;
			this->loss++;
		}
		AI* comp = this->computers.front(); // set first player 
		this->computers.pop(); // front player from front of queue
		this->computers.push(comp); // inserts front player to back of queue
		i++;
	}
}
void blackjack::startGame(PacketManager &pM) {
	//if (this->players.size() > -3) { // should be 0 converted to -1 for testing
	int changeName = 0;
	int diff = 1;
	while (this->players.size() + this->computers.size() < MIN_PLAYERS) { // inserts computers to fill min requirements
		AI* comp = new AI();
		switch (diff) {
		case 1:
			comp->standValue = 0.8;
			break;
		case 2:
			comp->standValue = 0.68;
			break;
		case 3:
			comp->standValue = 0.26;
			break;
		}
		diff++;
	/*	switch (changeName) {
		case 0:
			comp->name = "Islam";
			break;
		case 1:
			comp->name = "Danny";
			break;
		case 2:
			comp->name = "Nick";
			break;
		case 4:
			comp->name = "Amanuel";
			break;
		default:
			comp->name = "Unnamed";
			break;

		}
		*/
		this->computers.push(comp);
		//cout << "Computer player added!\n";
	}
	
	while (!this->players.empty()) { // play games over and over until there are no players at the table


		// add incoming players to the game
		if (!incomingPlayers.empty()) {
			if (this->computers.size() + this->players.size() + this->incomingPlayers.size() < MAX_PLAYERS) { // if adding all players wont go over the max players
				while (!this->incomingPlayers.empty()) {
					this->players.push(this->incomingPlayers.front());
					this->incomingPlayers.pop();
				}
			}
			else { // remove number of required computers to allow players in
				int compsToRemove = MAX_PLAYERS - (this->computers.size() + this->players.size() + this->incomingPlayers.size());
				for (int i = 0; i < compsToRemove; i++) {
					this->computers.pop();
				}
				while (!this->incomingPlayers.empty()) {
					this->players.push(this->incomingPlayers.front());
					this->incomingPlayers.pop();
				}
			}
		} // if incoming players not empty

		string options[] = { "Stand","Hit","Quit" }; // game options      | Should be "Hit", "Stand", "Quit" quit was edited so computers cant quit until proper implementation has been done
		SOCKET* peerSocket = this->players.front()->acc->connection;

		if (this->computers.size() + this->players.size() < MIN_PLAYERS) { // add computers to min allowed characters if players left
			int compsToAdd = MIN_PLAYERS - (this->computers.size() + this->players.size());
			for (int i = 0; i < compsToAdd; i++) {
				AI* comp = new AI();
				this->computers.push(comp);
			}
		}


		this->dealCards(); // deal cards
		this->takeBets(pM); // take bets from players and computers

		//cout << "\n\n";
	//cout << "Cards Dealt\n";
		queue<int> computer_values;


		// player turns
		for (int i = 0; i < this->players.size(); i++) { // give all computer players a turn
			string turnValue;
			if (this->players.front()->status != 'o') { // if computers not out
				int z = computer_values.size();
				for (int b = 0; b < z; b++) {
					computer_values.pop();
				}
				for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
					computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
					AI* comp = this->computers.front(); // set first player 
					this->computers.pop(); // front player from front of queue
					this->computers.push(comp); // inserts front player to back of queue
				}
				turnValue = this->players.front()->turn(pM, options, (sizeof(options) / sizeof(string)), computer_values, this->deal,0);// add opt packet manager
				//cout << "player " << i + 1 << " Decided to " << turnValue << "\n";
			}
			while (turnValue != "Stand" && this->terminated == false) { // while player has not chosen stand and they didnt break

				if (turnValue == "Hit") {
					this->players.front()->getCard(this->DECK->drawCard()); // give player card from deck if they hit
				}
				else if (turnValue == "Quit") {
					if (this->players.size() == 1) {
						this->terminated = true;
					}

					PacketQuitGame* pQg = new PacketQuitGame();
					pQg->setSequence(pM.getPacket()->getSequence());

					pQg->setAccFunds(this->players.front()->acc->getFunds());
					pM = PacketManager(pQg->serialize());

					sendClientPacket(*peerSocket, pM);
					this->players.front()->reset();
					this->save();
					this->players.pop(); // remove from queue without being inserted into back thus removing computer from game
				}
				if (this->terminated == false) {
					if (this->players.front()->getCardTotal() > BROKEVALUE) { // if computer is broke they are given out status and turn is done
							//cout << "player " << i + 1 << "is Broke " << this->computers.front()->getCardTotal() << "\n";
						this->players.front()->status = 'o';
						turnValue = "Stand";
					}
					else {
						int z = computer_values.size();
						for (int b = 0; b < z; b++) {
							computer_values.pop();
						}
						for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
							computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
							AI* comp = this->computers.front(); // set first player 
							this->computers.pop(); // front player from front of queue
							this->computers.push(comp); // inserts front player to back of queue
						}
						turnValue = this->players.front()->turn(pM, options, (sizeof(options) / sizeof(string)),computer_values,this->deal,0); // player gets another turn if they are not broke and didnt stand
						//cout << "player " << i + 1 << "Decided to " << turnValue << "\n";
					}
				}
			}
			if (this->terminated == false) {
				// move to next computer once this one is done
				player* p1 = this->players.front(); // set first player 
				this->players.pop(); // front player from front of queue
				this->players.push(p1); // inserts front player to back of queue
			}
		}
		// player turns


		if (this->terminated == false) {
			// Computer turns
			for (int i = 0; i < this->computers.size(); i++) { // give all computer players a turn
				string turnValue;
				if (this->computers.front()->status != 'o') { // if computers not out
					int z = computer_values.size();
					for (int b = 0; b < z; b++) {
						computer_values.pop();
					}
					for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
						computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
						AI* comp = this->computers.front(); // set first player 
						this->computers.pop(); // front player from front of queue
						this->computers.push(comp); // inserts front player to back of queue
					}
					turnValue = this->computers.front()->turn(options, (sizeof(options) / sizeof(string)),pM, computer_values ,this->deal, peerSocket,i);
					//cout << "player " << i + 1 << "c Decided to " << turnValue << "   Card Value : " << this->computers.front()->getCardTotal()<<"\n";
				}
				while (turnValue != "Stand") { // while player has not chosen stand and they didnt break

					if (turnValue == "Hit") {
						this->computers.front()->getCard(this->DECK->drawCard()); // give player card from deck if they hit
					}
					else if (turnValue == "Quit") {
						this->computers.pop(); // remove from queue without being inserted into back thus removing computer from game
					}
					if (this->computers.front()->getCardTotal() > BROKEVALUE) { // if computer is broke they are given out status and turn is done
						//cout << "player " << i + 1 << "c is Broke " << this->computers.front()->getCardTotal() << "\n";
						this->computers.front()->status = 'o';
						int z = computer_values.size();
						for (int b = 0; b < z; b++) {
							computer_values.pop();
						}
						turnValue = "Stand";
					}
					else {
						int z = computer_values.size();
						for (int b = 0; b < z; b++) {
							computer_values.pop();
						}
						for (int b = 0; b < this->computers.size(); b++) { // give all computer players a turn
							computer_values.push(this->computers.front()->getCardTotal() - this->computers.front()->hiddenCard->getValue());
							AI* comp = this->computers.front(); // set first player 
							this->computers.pop(); // front player from front of queue
							this->computers.push(comp); // inserts front player to back of queue
						}
						turnValue = this->computers.front()->turn(options, (sizeof(options) / sizeof(string)), pM, computer_values, this->deal, peerSocket,i);
						//cout << "player " << i + 1 << "c Decided to " << turnValue << "   Card Value : " << this->computers.front()->getCardTotal() << "\n";
					}
				}

				// move to next computer once this one is done

				AI* comp = this->computers.front(); // set first player 
				this->computers.pop(); // front player from front of queue
				this->computers.push(comp); // inserts front player to back of queue
			}
			// Computer Turns

			//Dealer Turn
			string turnValue;
			turnValue = this->deal->turn(options, (sizeof(options) / sizeof(string)));
			while (turnValue != "Stand") { // while player has not chosen stand and they didnt break

				if (turnValue == "Hit") {
					this->deal->getCard(this->DECK->drawCard()); // give player card from deck if they hit
				}
				if (this->deal->getCardTotal() > BROKEVALUE) { // if computer is broke they are given out status and turn is done
					////cout << "Dealer is Broke " << this->deal->getCardTotal() << "\n";
					this->deal->status = 'o';
					turnValue = "Stand";
				}
				else {
					turnValue = this->deal->turn(options, (sizeof(options) / sizeof(string)));
					//cout << "Dealer decided to " << turnValue << "\n";
				}
			}
			//Dealer Turn

			this->dealBets(); // pay players out

			// display all totals
			int i = 0;
			//cout << "\n\n";
			int comps = this->computers.size();
			int plays = this->players.size();
			// gamepacket h = new ga

			PacketGameUpdate* pGu = new PacketGameUpdate();
			pGu->setSequence(pM.getPacket()->getSequence());
			string* message[MAX_LINES] = {};
			int messageIndex = 0;
			//cout << "\n\n";
			string compsMessage;
			for (int i = 0; i < comps; i++) {
				// h.printStrings[0] = 
				message[messageIndex] = new string("Player " + std::to_string(i) + "c had " + std::to_string(this->computers.front()->getCardTotal()) + "\tPlayer funds = " + std::to_string(this->computers.front()->funds) + "\n");
				messageIndex++;
				this->computers.front()->reset();
				AI* comp = this->computers.front(); // set first player 
				this->computers.pop(); // front player from front of queue
				this->computers.push(comp); // inserts front player to back of queue
			} // display totals computers
			//cout << "\n\n";
			// display totals players
			for (int i = 0; i < plays; i++) {
				message[messageIndex] = new string("Player " + std::to_string(i) + "  had " + std::to_string(this->players.front()->getCardTotal()) + "\tPlayer funds = " + std::to_string(this->players.front()->acc->getFunds()) + "\n");
				messageIndex++;
				this->players.front()->reset();
				player* p1 = this->players.front(); // set first player 
				this->players.pop(); // front player from front of queue
				this->players.push(p1); // inserts front player to back of queue
			}
			// display totals dealer
			//cout << "\n\n";
			message[messageIndex] = new string("Dealer had " + std::to_string(this->deal->getCardTotal()) + "\n");
			messageIndex++;
			
			char* messageChars[MAX_LINES] = {};

			for (int i = 0; i < MAX_LINES; i++) {
				if (message[i] != NULL) {
					messageChars[i] = new char[MAX_MESSAGE_SIZE] {};
					strcpy_s(messageChars[i], MAX_MESSAGE_SIZE, message[i]->c_str());
				}

			}

			pGu->setMessages(messageChars);

			pM = PacketManager(pGu->serialize());

			sendClientPacket(*peerSocket, pM);

			this->deal->reset();

			this->DECK->reset();
			this->DECK->shuffle(6);
		} // if terminate == false
		
		int comps = this->computers.size();
		for (int i = 0; i < comps; i++) { // reset all comps on game ending
			this->computers.front()->reset();
			AI* comp = this->computers.front(); // set first player 
			this->computers.pop(); // front player from front of queue
			this->computers.push(comp); // inserts front player to back of queue
		} 
		this->deal->reset();
		this->DECK->reset(); // reset everything else on game ending
		this->DECK->shuffle(6);
	} // while true
}
void blackjack::dealCards() {

	// deal cards to computers
	for (int i = 0; i < this->computers.size() * CARDS_TO_DEAL; i++) { // give all computer players x number of cards
		this->computers.front()->getCard(this->DECK->drawCard()); // give front player card from the deck
		AI* comp = this->computers.front(); // store first player
		this->computers.pop(); // remove front player from front of queue
		this->computers.push(comp); // inserts front player to back of queue
	}
	// deal cards to computers


	// deal cards to human players
	for (int i = 0; i < this->players.size() * CARDS_TO_DEAL; i++) { // give all computer players x number of cards
		this->players.front()->getCard(this->DECK->drawCard()); // give front player card from the deck
		player* pl = this->players.front(); // store first player
		this->players.pop(); // remove front player from front of queue
		this->players.push(pl); // inserts front player to back of queue
	}
	// deal cards to human players

	//deal cards to dealer
	for (int i = 0; i < CARDS_TO_DEAL; i++) {
		this->deal->getCard(this->DECK->drawCard());
	}
	//deal cards to dealer

}
blackjack::blackjack(player* players[], int computers, int people) {
	if (people > MAX_PLAYERS) {
		people = MAX_PLAYERS;
	}
	for (int i = 0; i < people; i++) { // Only allow up to max players | PRIORITY HUMAN PLAYERS
		this->players.push(players[i]);
		this->playerSave.push(players[i]);
		////cout << "player added!\n";
	}
	if (people + computers > MAX_PLAYERS) { // if max players is 10 and there are 7 humans only 3 computers will be added
		computers = MAX_PLAYERS - people;
	}

	for (int i = 0; i < computers; i++) { // add computer players as requested if room left
		AI* comp = new AI();
		this->computers.push(comp);
		////cout << "Computer player added!\n";
	}
	this->saveThread = thread(SAVE, this);
}
blackjack::blackjack(float winloss) {
	while (this->players.size() + this->computers.size() < MIN_PLAYERS) { // inserts computers to fill min requirements
		AI* comp = new AI();
		comp->standValue = winloss;
		this->computers.push(comp);
		//cout << "Computer player added!\n";
	}
	this->saveThread = thread(SAVE, this);
}
blackjack::blackjack() {
	int diff = 1;
	while (this->players.size() + this->computers.size() < MIN_PLAYERS) { // inserts computers to fill min requirements
		AI* comp = new AI();
		switch (diff) {
		case 1:
			comp->standValue = 0.8;
			break;
		case 2:
			comp->standValue = 0.68;
			break;
		case 3:
			comp->standValue = 0.26;
			break;
		}
		diff++;
		this->computers.push(comp);
		//cout << "Computer player added!\n";
	}
	this->saveThread = thread(SAVE, this);
}
blackjack::blackjack(player* players[], int computers, int people, int difficulty[]) {
	if (people > MAX_PLAYERS) {
		people = MAX_PLAYERS;
	}
	for (int i = 0; i < people; i++) { // Only allow up to max players | PRIORITY HUMAN PLAYERS
		this->players.push(players[i]);
		this->playerSave.push(players[i]);
		////cout << "player added!\n";
	}
	if (people + computers > MAX_PLAYERS) { // if max players is 10 and there are 7 humans only 3 computers will be added
		computers = MAX_PLAYERS - people;
	}

	for (int i = 0; i < computers; i++) { // add computer players as requested if room left
		AI* comp = new AI();
		switch (difficulty[i]) {
		case 1:
			comp->standValue = 0.8;
			break;
		case 2:
			comp->standValue = 0.68;
			break;
		case 3:
			comp->standValue = 0.26;
			break;
		default:
			comp->standValue = 0.68;
			break;
		}
		this->computers.push(comp);
		////cout << "Computer player added!\n";
	}
	this->saveThread = thread(SAVE, this);
}
blackjack::~blackjack()
{
	this->saveThread.join();
	while (!this->computers.empty()) { // delete all computers
		delete(this->computers.front());
		this->computers.pop();
	}
	while (!this->players.empty()) { // delete all players
		delete(this->players.front());
		this->players.pop();
	}
	while (!this->playerSave.empty()) { // delete all players from save queue
		delete(this->playerSave.front());
		this->playerSave.pop();
	}
	delete(this->DECK); // delete deck
	delete(this->deal); // delete dealer=
}
void blackjack::save() {
	fstream f;
	string input;
	int x = this->playerSave.size();
	for (int i = 0; i < x; i++) {
		f.open(("./Users/" + this->playerSave.front()->acc->getUsername()), ios::in);
		getline(f, input);
		f.close();
		f.open(("./Users/" + this->playerSave.front()->acc->getUsername()), ios::out);
		f << input << "\n";
		f << this->playerSave.front()->acc->getFunds() << "\n";
		f << this->playerSave.front()->acc->getAge() << "\n";
		f << this->playerSave.front()->acc->getName();
		f.close();
		player* temp = this->playerSave.front();
		this->playerSave.pop();
		this->playerSave.push(temp);
	}
}
void SAVE(blackjack* game) {
	while (game->terminated == false) {
		sleep_for(std::chrono::seconds(SAVETIME));
		game->save();
	}
}