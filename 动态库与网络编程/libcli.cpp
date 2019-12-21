/*************************************************************************
	> File Name: libcli.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 20 Dec 2019 11:50:55 PM PST
 ************************************************************************/
#include<iostream>

#include<unistd.h>
#include<memory.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;



extern "C" void open_client(char *str){
    int clientSocket=socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket==-1){
        cout<<"socket error"<<endl;
        return;
    }

    sockaddr_in serverAddress;
    memset(&serverAddress,0,sizeof(sockaddr_in));
    serverAddress.sin_family=AF_INET;
    if(inet_pton(AF_INET,"127.0.0.1",&serverAddress.sin_addr)!=1){
        cout<<"inet_pton error"<<endl;
        return;
    }

    serverAddress.sin_port=htons(4000);
    if(connect(clientSocket,(sockaddr*)&serverAddress,sizeof(serverAddress))==-1){
        cout<<"connect error"<<endl;
        return;
    }

    int n;
    while(1){
        n=write(clientSocket,str,sizeof(str));
        if(n==-1)
            break;   
        sleep(2);
    }
    close(clientSocket);
}
