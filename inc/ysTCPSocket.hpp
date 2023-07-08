#pragma once

#include "../inc/ysSocketBase.hpp"

namespace YS::Network
{
    class TCP_ClientSocket : public ClientSocket
    {
    public:
        TCP_ClientSocket(IPVersion ipVersion, std::string_view server_ip, int port);
        TCP_ClientSocket(TCP_ClientSocket const &) = delete;
        TCP_ClientSocket(TCP_ClientSocket &&) = default;
        virtual ~TCP_ClientSocket() = default;
        TCP_ClientSocket& operator=(TCP_ClientSocket const &) = delete;
        TCP_ClientSocket& operator=(TCP_ClientSocket &&) = default;
    };

    class TCP_ServerSocket : public ServerSocket
    {
    public:
        TCP_ServerSocket(IPVersion ipVersion, int port);
        TCP_ServerSocket(TCP_ServerSocket const &) = delete;
        TCP_ServerSocket(TCP_ServerSocket &&) = default;
        virtual ~TCP_ServerSocket() = default;
        TCP_ServerSocket& operator=(TCP_ServerSocket const &) = delete;
        TCP_ServerSocket& operator=(TCP_ServerSocket &&) = default;
    };
}