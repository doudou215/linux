#include<netinet/in.h>
#include<memory.h>
#include<unistd.h>
#include<iostream>
#include<time.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<dlfcn.h>
#define MY_MODE S_IRWXU|S_IRWXO|S_IRWXG


void *link1(void *argv){
    long BackSock=(long)argv;
    char buf[10];
    time_t last,now;
    time(&last);
    time(&now);
    while(now-last<35){
        read(BackSock,buf,4);
        std::cout<<buf<<std::endl;
        time(&now);
    }
    close(BackSock);
    pthread_exit((void *)0);
}

void *link2(void *argv){
    long CliSock=(long)argv;
    char buf[10];
    time_t last,now;
    time(&last);
    time(&now);
    int fd=open("data",O_TRUNC|O_CREAT|O_RDWR,MY_MODE);
    if(fd<0)
        std::cerr<<"can not open file"<<std::endl;
    while(1){
        read(CliSock,buf,6);
        time(&now);
        if(now-last>30)
            break;
        std::cout<<buf<<std::endl;
    }
    write(fd,buf,6);
    close(fd);
    close(CliSock);
    pthread_exit((void *)0);
}

int myTcpServer(int port){
    void *handle=dlopen("./libserver.so",RTLD_LAZY);
    if(!handle){
        std::cout<<"handle error"<<std::endl;
        return 0;
    }
    typedef void (*FUNC_SERVER)(int *serversock);

    int ServerSock;
    FUNC_SERVER server=(FUNC_SERVER)dlsym(handle,"open_server");
    if(server==0){
        std::cout<<"dlsym error"<<std::endl;
        return 0;
    }
    (server)(&ServerSock);
    if(ServerSock==-1){
        std::cout<<"serversock error"<<std::endl;
        return 0;
    }
    pthread_t pid[2]; 
    long i=0;
    while(i<2){
        sockaddr_in ClientAddress;
        socklen_t length=sizeof(ClientAddress);
        long ClientSock=accept(ServerSock,(sockaddr *)&ClientAddress,&length);

        int err;
        if(i==0)
            err=pthread_create(&pid[i++],NULL,link1,(void *)ClientSock);
        else
            err=pthread_create(&pid[i++],NULL,link2,(void *)ClientSock);
        if(err!=0){
            std::cerr<<"creat thread error"<<std::endl;
            return 0;
        }
    }
    for(i=0;i<2;i++){
        int err=pthread_join(pid[i],NULL);
        if(err!=0)
        {
            std::cerr<<"join thread error "<<i<<std::endl;
            return 0;
        }
    }
    close(ServerSock);
    dlclose(handle);
}


int main(){
    myTcpServer(4000);
    return 0;
}
