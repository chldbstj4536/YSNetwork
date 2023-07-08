#pragma once

#include "../inc/ysSocketBase.hpp"

namespace YS::Network
{
    class UDP_Socket : public SocketBase
    {
    public:
        UDP_Socket(IPVersion ipVersion, int port = -1);
        UDP_Socket(UDP_Socket const &) = delete;
        UDP_Socket(UDP_Socket &&) = default;
        virtual ~UDP_Socket() = default;
        UDP_Socket& operator=(UDP_Socket const &) = delete;
        UDP_Socket& operator=(UDP_Socket &&) = default;

        bool SendTo(std::string_view send_ip, int port, void* buff, size_t nbytes);
        void OnRecvFrom(std::string_view recv_ip, int port, void* buff, size_t nbytes);

    private:
        static void UDP_Entry(UDP_Socket* caller);

    private:
        std::thread recvThread;
        Event<void(std::string_view, int, void*, size_t)> OnReceive;
    };
}