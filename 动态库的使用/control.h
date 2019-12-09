#ifndef CONTROL_H
#define CONTROL_H


#include "a.h"
#include <dlfcn.h>

typedef void (*PRINT) ();
typedef int (*GETID) ();
typedef void (*HELP) (); 
using namespace std;


class C{
public:
	C() {};
	~C() {};
	void init();
	void help();
	void request(int n);
private:
	vector<void *> handles;
	vector<string> str;
	vector<PRINT> fun1;
	vector<GETID> fun2;
	vector<HELP> fun3;
};

#endif
