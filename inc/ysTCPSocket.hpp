#pragma once

namespace YS::Network
{
    #if defined(WIN32)
    using NativeSocket = WindowSocket;
    #elif defined(LINUX)
    using NativeSocket = LinuxSocket;
    #endif

    class TCP_Socket : public NativeSocket
    {
    public:
        TCP_Socket();
        TCP_Socket(TCP_Socket const &) = delete;
        TCP_Socket(TCP_Socket &&) = default;
        ~TCP_Socket();
        TCP_Socket& operator=(TCP_Socket const &) = delete;
        TCP_Socket& operator=(TCP_Socket &&) = default;
    };
}