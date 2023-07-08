#include <YSNetwork/ysTCPSocket.hpp>
#include <thread>
#include <iostream>

using namespace std;
using namespace YS::Network;

void ServerEntry()
{
    TCP_ServerSocket server(IPVersion::IPv4, 9010);

    if (server.Listen(5) == false)
    {
        cout << "Listen Fail!\n";
        return;
    }

}
void ClientEntry()
{
    TCP_ClientSocket client(IPVersion::IPv4, "128.0.0.1", 9010);

}

int main()
{
    thread server_thread(ServerEntry);
    thread client_thread(ClientEntry);

}