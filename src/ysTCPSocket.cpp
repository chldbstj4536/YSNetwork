#include "../inc/ysTCPSocket.hpp"

#define _YS_NETWORK_BEGIN namespace YS::Network {
#define _YS_NETWORK_END }

_YS_NETWORK_BEGIN
TCP_ClientSocket::TCP_ClientSocket(IPVersion ipVersion, std::string_view server_ip, int port)
    : ClientSocket(ipVersion, ProtocolType::TCP, server_ip, port) {}

TCP_ServerSocket::TCP_ServerSocket(IPVersion ipVersion, int port)
    : ServerSocket(ipVersion, ProtocolType::TCP, port) {}

_YS_NETWORK_END