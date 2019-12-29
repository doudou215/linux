#include "control.h"
#include <string.h>



void C::init(){
	B b;
	b.getName(str);
    typedef void (*func)(D **plug);
	for(int i=0;i<2;i++){
		void *handle=dlopen(str[i].c_str(),RTLD_LAZY);
		if(!handle){
			cerr<<"handle error"<<endl;
			return;
		}
        func o1=(func)dlsym(handle,"createObject");
        D *a;
        o1(&a);
        a->help();
        fun.push_back(a);
        handles.push_back(handle);
    }
}
void C::help(){
	fun[1]->help();
	fun[0]->help();
	dlclose(handles[0]);
	dlclose(handles[1]);	
}


void C::request(int n){
	if(n==(fun[0]->getId())){
	    fun[0]->print();
		dlclose(handles[0]);
	}
	else{
		fun[1]->print();
		dlclose(handles[1]);
	}		
}
	










