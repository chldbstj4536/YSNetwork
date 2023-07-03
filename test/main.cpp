#include <YSNetwork/ysWindowSocket.hpp>
#include <iostream>

using namespace std;
using namespace YS::Network;

int main()
{
    WindowServerSocket ws(IPVersion::IPv4, ProtocolType::TCP, 10000);
    cout << static_cast<int>(ws.GetState()) << endl;
    WindowClientSocket cs(IPVersion::IPv4, ProtocolType::TCP, "128.0.0.1", 10000);
    cout << static_cast<int>(cs.GetState()) << endl;
}