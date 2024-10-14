
#include <iostream>
#include "dionis.h"
#include <string>

using namespace std;

int main(int argc, char ** argv)
{
	dionis da(argv[1]);
	da.print();
	da.drow();
	return 0;
}
