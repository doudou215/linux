#include "base.h"
#include <iostream>


using namespace std;


class F:public D{
public:
	F() {}
	virtual ~F() {}
    virtual void print(){
        cout<<"hello world"<<endl;
    }
    virtual int getId(){
        return ID;
    }
    virtual void help(){
        cout<<"This is function1 and it will print hello world"<<endl;
    }		
private:
	const int ID=1;

};


extern "C"  void createObject(D **plug){
    static F f;
    *plug=&f;
}
