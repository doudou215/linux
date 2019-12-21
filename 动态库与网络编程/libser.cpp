/*************************************************************************
	> File Name: libser.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 21 Dec 2019 12:30:12 AM PST
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<memory.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;


extern "C" void open_server(int *serverSock){
    *serverSock=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in serverAddress;
    memset(&serverAddress,0,sizeof(sockaddr_in));
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    serverAddress.sin_port=htons(4000);
    if(bind((*serverSock),(sockaddr *)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"bind error"<<endl;
        return;
    }
    if(listen((*serverSock),13)==-1){
        cout<<"listen error"<<endl;
        return;
    }
    return;
}
