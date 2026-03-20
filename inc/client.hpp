#ifndef CLIENT_H
#define CLIENT_H

#include <main.hpp>

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string>

// this is a client side system, receiving data from other server
class Comm {

  public:
    Comm() {}
    int start();
    void reader(Tick& t);
    ~Comm() {
        close(Ssocket);
        Ssocket = 0;
    }

  private:
    int PORT = 9020;
    int Csocket;
    struct sockaddr_in clientAddress;
    int Ssocket;
    struct sockaddr_in serverAddress;
    socklen_t serverLength;

};


#endif // CLIENT_H