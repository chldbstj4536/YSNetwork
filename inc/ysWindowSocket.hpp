#pragma once

#ifdef WIN32
#include <string_view>
#include <ws2tcpip.h>
#include "ysSocketBase.hpp"

#pragma comment(lib, "Ws2_32.lib")

namespace YS::Network
{
    class WindowSocket : public SocketBase
    {
    public:
        WindowSocket(IPVersion ipVersion, ProtocolType protocol);
        WindowSocket(WindowSocket const &) = delete;
        WindowSocket(WindowSocket &&) = default;
        virtual ~WindowSocket();
        WindowSocket& operator=(WindowSocket const &) = delete;
        WindowSocket& operator=(WindowSocket &&) = default;

    protected:
        SOCKET GetSocket() { return winSocket; }
        int GetProtocolFamily() { return protocolFamily; }
        int GetAddressFamily() { return addressFamily; }

    private:
        SOCKET winSocket = INVALID_SOCKET;
        int protocolFamily = PF_UNSPEC;
        int addressFamily = AF_UNSPEC;
        ProtocolType protocol;
    };

    class WindowServerSocket : public WindowSocket
    {
    public:
        WindowServerSocket(IPVersion ipVersion, ProtocolType protocol, int port);
        WindowServerSocket(WindowServerSocket const &) = delete;
        WindowServerSocket(WindowServerSocket&&) = default;
        virtual ~WindowServerSocket() = default;
        WindowServerSocket& operator=(WindowServerSocket const &) = delete;
        WindowServerSocket& operator=(WindowServerSocket&&) = default;

    };

    class WindowClientSocket : public WindowSocket
    {
    public:
        WindowClientSocket(IPVersion ipVersion, ProtocolType protocol, std::string_view server_ip, int port);
        WindowClientSocket(WindowClientSocket const &) = delete;
        WindowClientSocket(WindowClientSocket&&) = default;
        virtual ~WindowClientSocket() = default;
        WindowClientSocket& operator=(WindowClientSocket const &) = delete;
        WindowClientSocket& operator=(WindowClientSocket&&) = default;

    };
}
#endif