#include <client.hpp>

int Comm::start()
{
    Ssocket = socket(AF_INET, SOCK_STREAM, 0);

    if (Ssocket < 0) {
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(Ssocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed\n";
        close(Ssocket);
        return -1;
    }

    std::cout << "Connected to server\n";
    return 1;
}

void Comm::reader(Tick& t) {
    
    int data[2];

    read(Ssocket, data, sizeof(data));

    t.timestamp = ntohl(data[0]);
    t.price = ntohl(data[1]);

    return;
}