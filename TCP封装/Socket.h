/*************************************************************************
	> File Name: Socket.h
	> Author: 
	> Mail: 
	> Created Time: Fri 22 May 2020 09:46:00 PM PDT
 ************************************************************************/

#ifndef _SOCKET_H
#define _SOCKET_H

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

using namespace std;

namespace Socket
{
    typedef int Socket;
    typedef string Ip;
    typedef unsigned int Port;
    typedef string Data; 
    typedef struct
    {
        Ip ip;
        Port port;
    }Address;

    class Exception
    {
    private:
        string _message;
    public:
        Exception(string error) { this->_message = error; }
        virtual const char *what() { return this->_message.c_str(); }
    };

    class TCP
    {
    public:
        Socket socket_fd;
        struct sockaddr_in servaddr;
        TCP();
        virtual ~TCP() {}
        virtual void close(void) {}
        virtual void run(Address &address) {}
        void send(Data data);
        void recv(void);
    };

    TCP::TCP()
    {
        if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw Exception("constructor cannot create socket");
  
    }

    
    void TCP::send(Data data)
    {
        if(::send(socket_fd, data.c_str(), data.length(), 0) < 0)
            throw Exception("send error");
    }

    void TCP::recv(void)
    {
        char *buffer = new char[MAX_SIZE];
        if(::recv(socket_fd, buffer, MAX_SIZE, 0) < 0)
            throw Exception("recv error");
        printf("%s \n", buffer);
        delete [] buffer;
    }


    class TCPclient: public TCP
    {
    public:
        TCPclient() {}
        ~TCPclient() {}
        void run(Address &address);
        void close(void);
    };

    void TCPclient::run(Address &address)
    {
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = address.port;
        if(inet_pton(AF_INET, address.ip.c_str(), &servaddr.sin_addr) <= 0)
            throw Exception("inet_pton error");
        if(connect(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
            throw Exception("connect error");
        std::cout << "connent success"<< std::endl;
    }
    
    void TCPclient::close(void)
    {
        ::close(socket_fd);
    }


    class TCPserver: public TCP
    {
    public:
        TCPserver();
        ~TCPserver() {}
        void run(Address &address);
        void close() {::close(socket_fd); ::close(connect_sock);}
        void send(Data data);
        void recv(void);
    private:
        Socket connect_sock;
    };
    

    void TCPserver::run(Address &address)
    {
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = address.port;


        if(bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
            throw Exception("bind error");

        if(listen(socket_fd, 10) == -1)
            throw Exception("listen error");

        if((connect_sock = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
            throw Exception("accept error");
        std::cout <<"connect success"<< std::endl;
            
    }

    void TCPserver::send(Data data)
    {
        if(::send(connect_sock, data.c_str(), data.length(), 0) < 0)
            throw Exception("send error");
    }

    void TCPserver::recv(void)
    {
        char *buffer = new char[MAX_SIZE];
        if(::recv(connect_sock, buffer, MAX_SIZE, 0) < 0)
            throw Exception("recv error");
        printf("%s \n", buffer);
        delete [] buffer;
    }
    
    TCPserver::TCPserver()
    {    
        if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw Exception("constructor cannot create socket");

    }

}
#endif
