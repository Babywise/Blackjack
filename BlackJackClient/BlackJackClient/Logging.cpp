
#include "Logging.h"



void ErrorLog(string message, string Severity) {

	fstream f;
	time_t now = time(0);
	tm* time = gmtime(&now);
	f.open(ERRORLOG, ios::app);
	f << message << " | Severity : " << Severity<< " 2022" << "/" << time->tm_mon << "/" << time->tm_mday << " " << (time->tm_hour) - 4 << ":" << time->tm_min << ":" << time->tm_sec << "EST"<<endl;
	f.close();

}
void DataLog(string message) {

	fstream f;
	time_t now = time(0);
	tm* time = gmtime(&now);
	f.open(DATALOG, ios::app);
	f << message<<" 2022" << "/" << time->tm_mon << "/" << time->tm_mday << " " << (time->tm_hour) - 4 << ":" << time->tm_min << ":" << time->tm_sec << "EST" <<endl;
	f.close();


}