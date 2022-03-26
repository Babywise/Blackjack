#include <stdio.h>
#include <fstream>
#include "Logging.h"
using namespace std;

int main()
{

   
    printf("Hello World");
    ErrorLog("Error", "Severe");
    string errors[5];
    errors[0] = "Client Recieved xxx";
    errors[1] = "Thread 2001";
    DataLog("Client send Ack");
    return 0;
}