#pragma once

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
        SocketBase() = default;
        SocketBase(SocketBase const &) = delete;
        SocketBase(SocketBase &&) = default;
        virtual ~SocketBase() = default;
        SocketBase& operator=(SocketBase const &) = delete;
        SocketBase& operator=(SocketBase &&) = default;

        // virtual bool Listen() = 0;
        StateInfo GetState() { return state; }

    protected:
        void SetState(StateInfo newState) { state = newState; }

    private:
        StateInfo state = StateInfo::Success;
    };
}