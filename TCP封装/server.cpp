#include "Socket.h"
#include <iostream>

using namespace std;



int main()
{
    try
    {
        Socket::TCPserver server;
        Socket::Address address = {"127.0.0.1", 4000};
        server.run(address);
        server.recv();
        server.close();
        
    }
    catch(Socket::Exception &e)
    {
        cout << e.what() <<endl;
    }

    return 0;

}
