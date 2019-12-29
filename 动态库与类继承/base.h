#ifndef BASE_H
#define BASE_H

#include<iostream>


using namespace std;


class D{
public:
	D(); 
	virtual ~D(); 
	virtual void print()=0;
	virtual int getId()=0;
	virtual void help()=0;
};

#endif
