#include<sys/socket.h>
#include<memory.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#include<time.h>
#include<signal.h>
#include<dlfcn.h>

int main(){
    struct sigaction sa;
    sa.sa_handler=SIG_IGN;
    sigaction(SIGPIPE,&sa,NULL);
    void *handle=dlopen("./libclient.so",RTLD_LAZY);
    if(!handle){
        std::cout<<"handle error"<<std::endl;
        return 0;
    }
    typedef void (*FUNC_CLIENT)(char *str);
    int ServerSock;
    FUNC_CLIENT dl_client=(FUNC_CLIENT)dlsym(handle,"open_client");
    char buf[5]="test";
    (dl_client)(buf);
    dlclose(handle);
    std::cout<<"begin transition after 30s"<<std::endl;
    sleep(30);
    void *handle1=dlopen("./libserver.so",RTLD_LAZY);
    if(!handle){
        std::cout<<"handle1 error"<<std::endl;
        return 0;
    }
    typedef void (*FUNC_SERVER)(int *serversock);
    FUNC_SERVER dl_server=(FUNC_SERVER)dlsym(handle1,"open_server");
    (dl_server)(&ServerSock);
    if(ServerSock==-1){
        std::cout<<"socket error"<<std::endl;
        return 0;
    }
    sockaddr_in ClientAddress;
    socklen_t length=sizeof(ClientAddress);
    std::cout<<"waiting for the connectin"<<std::endl;
    int ClientSock=accept(ServerSock,(sockaddr *)&ClientAddress,&length);
    if(ClientSock==-1){
        std::cout<<"connectin failed"<<std::endl;
        return 0;
    }
    int fd=open("data",O_RDONLY);
    std::cout<<"This is backup server"<<std::endl;
    read(fd,buf,6);
    std::cout<<buf<<std::endl;
    for(int j=0;j<4;j++){
        read(ClientSock,buf,7);
        std::cout<<buf<<std::endl;
    }
    close(fd);
    close(ServerSock);
    close(ClientSock);
    return 0;
}
