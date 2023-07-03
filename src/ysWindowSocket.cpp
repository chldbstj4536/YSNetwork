#ifdef WIN32
#include "../inc/ysWindowSocket.hpp"

#define _YS_NETWORK_BEGIN   namespace YS::Network {
#define _YS_NETWORK_END     }

_YS_NETWORK_BEGIN
WindowSocket::WindowSocket(IPVersion ipVersion, ProtocolType protocol)
    : protocol(protocol)
{
    WSADATA wd;
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));

    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        SetState(StateInfo::CreateFail);
        return;
    }

    switch (ipVersion)
    {
    case IPVersion::IPv4:
        protocolFamily = PF_INET;
        addressFamily = AF_INET;
        break;
    case IPVersion::IPv6:
        protocolFamily = PF_INET6;
        addressFamily = AF_INET6;
        break;
    default:
        SetState(StateInfo::CreateFail);
        return;
    }

    switch (protocol)
    {
    case ProtocolType::TCP:
        winSocket = socket(protocolFamily, SOCK_STREAM, IPPROTO_TCP);
        break;
    case ProtocolType::UDP:
        winSocket = socket(protocolFamily, SOCK_DGRAM, IPPROTO_UDP);
        break;
    }
    if (winSocket == INVALID_SOCKET)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
}
WindowSocket::~WindowSocket()
{
    closesocket(winSocket);
    WSACleanup();
}

WindowServerSocket::WindowServerSocket(IPVersion ipVersion, ProtocolType protocol, int port)
    : WindowSocket(ipVersion, protocol)
{
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = GetAddressFamily();
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(GetSocket(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) == -1)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
}

WindowClientSocket::WindowClientSocket(IPVersion ipVersion, ProtocolType protocol, std::string_view server_ip, int port)
    : WindowSocket(ipVersion, protocol)
{
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = GetAddressFamily();
    if (inet_pton(AF_INET, server_ip.data(), &(serv_addr.sin_addr.s_addr)) == -1)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
    serv_addr.sin_port = htons(port);

    if (connect(GetSocket(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) == SOCKET_ERROR)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
}
_YS_NETWORK_END
#endif