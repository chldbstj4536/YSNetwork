#pragma once

#include <vector>
#include <string_view>
#include <thread>

#if defined(WIN32)
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

namespace YS::Network
{
    using SocketType = SOCKET;
    const SocketType InvalidSocket = INVALID_SOCKET;
}
#elif defined(LINUX)
#include "ysLinuxSocket.hpp"
namespace YS::Network
{
    using SocketType = int;
    const SocketType InvalidSocket = -1;
}
#endif


namespace YS::Network
{
    enum class IPVersion
    {
        IPv4,
        IPv6
    };
    enum class ProtocolType
    {
        TCP,
        UDP
    };
    enum class StateInfo 
    {
        Success,
        CreateFail,
        ConnectFail,
    };
    class SocketBase
    {
    public:
        SocketBase(IPVersion ipVersion, ProtocolType protocol);
        SocketBase(SocketBase const &) = delete;
        SocketBase(SocketBase &&) = default;
        virtual ~SocketBase();
        SocketBase& operator=(SocketBase const &) = delete;
        SocketBase& operator=(SocketBase &&) = default;

    protected:
        SocketBase(SocketType socket, int protocolFamily, int addressFamily, ProtocolType protocol);

        SocketType GetSocket() { return sock; }
        int GetProtocolFamily() { return protocolFamily; }
        int GetAddressFamily() { return addressFamily; }
        // virtual bool Listen() = 0;
        StateInfo GetState() { return state; }

    protected:
        void SetState(StateInfo newState) { state = newState; }

    private:
        SocketType sock = InvalidSocket;
        int protocolFamily = PF_UNSPEC;
        int addressFamily = AF_UNSPEC;
        ProtocolType protocol;
        StateInfo state = StateInfo::Success;
        bool bNeedWSACleanup = true;
    };

    class ClientSocket : public SocketBase
    {
    public:
        ClientSocket(IPVersion ipVersion, ProtocolType protocol, std::string_view server_ip, int port);
        ClientSocket(ClientSocket const &) = delete;
        ClientSocket(ClientSocket&&) = default;
        virtual ~ClientSocket() = default;
        ClientSocket& operator=(ClientSocket const &) = delete;
        ClientSocket& operator=(ClientSocket&&) = default;
    };

    class ServerSocket : public SocketBase
    {
    public:
        ServerSocket(IPVersion ipVersion, ProtocolType protocol, int port);
        ServerSocket(ServerSocket const &) = delete;
        ServerSocket(ServerSocket&&) = default;
        virtual ~ServerSocket() = default;
        ServerSocket& operator=(ServerSocket const &) = delete;
        ServerSocket& operator=(ServerSocket&&) = default;

        bool Listen(int backlog);

    private:

    };
}