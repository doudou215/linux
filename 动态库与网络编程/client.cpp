/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Dec 2019 08:45:23 AM PST
 ************************************************************************/

#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <dlfcn.h>

int main()
{
	struct sigaction sa;
	sa.sa_handler=SIG_IGN;
	sigaction(SIGPIPE,&sa,NULL);
    void *handle=dlopen("./libclient.so",RTLD_LAZY);
    if(!handle){
        std::cout<<"handle error"<<std::endl;
        return 0;
    }
    typedef void(*FUNC_CLIENT)(char *str);
    FUNC_CLIENT dl_client=(FUNC_CLIENT)dlsym(handle,"open_client");
    if(dl_client==0){
        std::cout<<"dl_client error"<<std::endl;
        return 0;
    }
    char buf[7]="client";
    dl_client(buf);
    std::cout<<"connection error reconnect after 35s"<<std::endl;
    char buf1[9]="newlink";
    sleep(35);
    dl_client(buf1);
    dlclose(handle);
    return 0;
}
