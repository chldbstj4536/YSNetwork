#include "../inc/ysUDPSocket.hpp"

#define _YS_NETWORK_BEGIN namespace YS::Network {
#define _YS_NETWORK_END }

_YS_NETWORK_BEGIN
UDP_Socket::UDP_Socket(IPVersion ipVersion, int port)
    : SocketBase(ipVersion, ProtocolType::UDP)
{
    if (port > 0)
    {
        sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = GetAddressFamily();
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);
        if (bind(GetSocket(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
        {
            SetState(StateInfo::CreateFail);
            return;
        }
    }

    recvThread = std::thread(UDP_Socket::UDP_Entry, this);
}

bool UDP_Socket::SendTo(std::string_view send_ip, int port, void *buff, size_t nbytes)
{
    sockaddr_in send_addr;
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = GetAddressFamily();
    if (inet_pton(GetAddressFamily(), send_ip.data(), &(send_addr.sin_addr.s_addr)) == -1)
    {
        SetState(StateInfo::CreateFail);
        return;
    }
    send_addr.sin_port = htons(port);

    sendto(GetSocket(), static_cast<const char*>(buff), nbytes, 0, reinterpret_cast<sockaddr*>(&send_addr), sizeof(send_addr));
}

void UDP_Socket::UDP_Entry(UDP_Socket* caller)
{
    char buff[MaxSocketBufferSize] {};

    while (caller->GetState() != StateInfo::Close)
    {
        sockaddr_in recv_addr;
        int recv_addr_size;
        int recvBuffSize;
        
        recvBuffSize = recvfrom(caller->GetSocket(), buff, MaxSocketBufferSize, 0, reinterpret_cast<sockaddr*>(&recv_addr), &recv_addr_size);

        caller->OnReceive(inet_ntoa(recv_addr.sin_addr), ntohs(recv_addr.sin_port), buff, recvBuffSize);
    }
}
_YS_NETWORK_END