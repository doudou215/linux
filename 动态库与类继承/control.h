#ifndef CONTROL_H
#define CONTROL_H

#include "base.h"
#include "a.h"
#include <dlfcn.h>

using namespace std;


class C{
public:
	C() {};
	~C() {};
    void init();
    void help();
    void request(int n);
private: 
    vector<D*> fun; 
	vector<void *> handles;
	vector<string> str;
};

#endif
