#include <main.hpp>

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>

void sender()
{   
    int PORT{9020}; 
    int serverSocket{};
    int clientSocket{};

    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    socklen_t clientLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket < 0)
    {
        std::cerr << "Socket creation failed\n";
        return;
    } else {
        std::cout << "Socket created...\n";
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 1);

    std::cout << "Waiting for client...\n";

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

    std::cout << "Client connected.\n";

    int timestamp{};
    int temp_pr{};
    int data[2];

    while(true)
    {
        temp_pr = 100 + rand() % 20;

        data[0] = htonl(timestamp);
        data[1] = htonl(temp_pr);

        //write(clientSocket, data, sizeof(data));
        send(clientSocket, data, sizeof(data), 0);
        std::cout << "data sent: t:" << timestamp << " p: " << temp_pr << "\n";
        timestamp++;
        usleep(1000000); // 1 sec between ticks
    }

    close(clientSocket);
    close(serverSocket);
}

int main() {
    sender();
    return 0;
}