#include <iostream>
#include <string>
#include "VirtualMahine.cpp"

int main()
{
	VirtualMachine* machine = new VirtualMachine();
	machine -> run();
	delete machine;
	return 0;
}