#include <iostream>

const int ID=2;

extern "C" void print()
{
	std::cout<<"Hello Linux"<<std::endl;
}

extern "C" int getId()
{
	return ID;
}

extern "C" void help()
{
	std::cout<<"This is function2,Do you understand?"<<std::endl;
}
