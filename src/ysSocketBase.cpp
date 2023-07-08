#include "../inc/ysSocketBase.hpp"
#include <memory>
#include <thread>

#define _YS_NETWORK_BEGIN   namespace YS::Network {
#define _YS_NETWORK_END     }

_YS_NETWORK_BEGIN
SocketBase::SocketBase(IPVersion ipVersion, ProtocolType protocol)
    : protocol(protocol)
{
#ifdef WIN32
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
#endif

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
        sock = socket(protocolFamily, SOCK_STREAM, IPPROTO_TCP);
        break;
    case ProtocolType::UDP:
        sock = socket(protocolFamily, SOCK_DGRAM, IPPROTO_UDP);
        break;
    }

    if (sock == InvalidSocket)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
}
SocketBase::SocketBase(SocketType socket, int protocolFamily, int addressFamily, ProtocolType protocol)
    : sock(socket), protocolFamily(protocolFamily), addressFamily(addressFamily), protocol(protocol), bNeedWSACleanup(false)
{
}
SocketBase::~SocketBase()
{
    closesocket(sock);
#ifdef WIN32
    if (bNeedWSACleanup)
        WSACleanup();
#endif
}


ClientSocket::ClientSocket(IPVersion ipVersion, ProtocolType protocol, std::string_view server_ip, int port)
    : SocketBase(ipVersion, protocol)
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

    if (connect(GetSocket(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) == -1)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
}

ServerSocket::ServerSocket(IPVersion ipVersion, ProtocolType protocol, int port, void(*handleClient)(SocketBase* clientSocket))
    : SocketBase(ipVersion, protocol)
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
_YS_NETWORK_END