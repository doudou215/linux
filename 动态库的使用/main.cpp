#include<iostream>
#include "control.h"
#include <string.h>
#include <stdlib.h>

using namespace std;



int main(int argc,char **argv){
	if(argc!=2){
		cout<<"usage: main help or main 1"<<endl;
		return 0;
	}
	C c;
	c.init();
	if(strcmp(argv[1],"help")==0)
	{
		c.help();
		return 0;
	}
	int n=atoi(argv[1]);
	c.request(n);
	return 0;
}
