#include <stdio.h>
#include <fstream>
using namespace std;

int main()
{

   
    printf("Hello World");
	fstream f;
	f.open(("./Users/Test"), ios::out);
	f.close();

    return 0;
}