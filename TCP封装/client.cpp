/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 24 May 2020 06:56:55 AM PDT
 ************************************************************************/

#include "Socket.h"
#include <iostream>
using namespace std;



int main()
{
    try
    {
        Socket::TCPclient client;
        Socket::Address address = {"127.0.0.1", 4000};
        client.run(address);
        client.send("I am client");
    //      client.recv();
        client.close();
    }
    catch(Socket::Exception &e)
    {
        cout << e.what() <<endl;
    }

    return 0;
}
