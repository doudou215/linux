/*************************************************************************
	> File Name: fucntion1.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 09 Dec 2019 06:07:30 PM PST
 ************************************************************************/
#include "base.h"
#include<iostream>
using namespace std;


class E:public D{
public:
    E(){}
    virtual ~E(){}
    virtual void print(){
        cout<<"hello linux"<<endl;
    }
    virtual void help(){
        cout<<"Thiis is function2 and it will print hello linux"<<endl;
    }
    virtual int getId(){
        return ID;
    }
private:
    const int ID=2;
}; 

extern "C" void createObject(D **plug){
    static E e;
    *plug=&e;
}


