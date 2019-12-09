#include "control.h"
#include <string.h>



void C::init(){
	B b;
	b.getName(str);
	for(auto it=str.begin();it!=str.end();it++){
		void *handle=dlopen((*it).c_str(),RTLD_LAZY);
		if(!handle){
			cerr<<"handle error"<<endl;
			return;
		}
		PRINT p=(PRINT)dlsym(handle,"print");
		if(!p){
			cerr<<"function print error"<<endl;
			return;
		}
		fun1.push_back(p);
		GETID q=(GETID)dlsym(handle,"getId");
		if(!q){
			cerr<<"function getid error"<<endl;
			return;
		}
		fun2.push_back(q);
		HELP l=(HELP)dlsym(handle,"help");
		if(!l){
			cerr<<"funtion help error"<<endl;
			return;
		}
		fun3.push_back(l);
		handles.push_back(handle);	
	}	
	return ;

}

void C::help(){
	fun3[0]();
	fun3[1]();
	dlclose(handles[0]);
	dlclose(handles[1]);	
}


void C::request(int n){
	if(n==(fun2[0]())){
		(fun1[0])();
		dlclose(handles[0]);
	}
	else{
		fun1[1]();
		dlclose(handles[1]);
	}		
}
	










