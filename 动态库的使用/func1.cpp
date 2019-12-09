#include <iostream>

const int ID=1;

extern "C" void print()
{
	std::cout<<"Hello China"<<std::endl;
}

extern "C" int getId()
{
	return ID;
}

extern "C" void help()
{
	std::cout<<"This is function1,Do you understand?"<<std::endl;
}
