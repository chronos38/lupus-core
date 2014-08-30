﻿#include "UdpClient.h"
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Integer.h"
#include "NetUtility.h"

#include <thread>

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Sockets {
            UdpClient::UdpClient(AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Datagram, ProtocolType::UDP);
            }

            UdpClient::UdpClient(uint16_t port)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(make_shared<IPEndPoint>(IPAddress::Loopback(), port));
            }

            UdpClient::UdpClient(shared_ptr<IPEndPoint> ep)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(ep);
            }

            UdpClient::UdpClient(uint16_t port, AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(make_shared<IPEndPoint>(IPAddress::Loopback(), port));
            }

            UdpClient::UdpClient(const string& hostname, uint16_t port)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Connect(GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP));
            }

            size_t UdpClient::Available() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->Available();
            }

            shared_ptr<Socket> UdpClient::Client() const
            {
                return mClient;
            }

            void UdpClient::Client(shared_ptr<Socket> client)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient = client;
            }

            bool UdpClient::ExclusiveAddressUse() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                int result, length = 4;

                if (getsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void UdpClient::ExclusiveAddressUse(bool value)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                int val = value ? 1 : 0;

                if (setsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            Task<std::vector<uint8_t>> UdpClient::ReceiveAsync(shared_ptr<IPEndPoint>& ep)
            {
                return Task<vector<uint8_t>>([this, &ep]() {
                    return this->Receive(ep);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size)
            {
                return Task<int>([this, &buffer, size]() {
                    return this->Send(buffer, size);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size, shared_ptr<IPEndPoint> ep)
            {
                return Task<int>([this, &buffer, size, ep]() {
                    return this->Send(buffer, size, ep);
                });
            }

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size, const string& hostname, uint16_t port)
            {
                return Task<int>([this, &buffer, size, &hostname, port]() {
                    return this->Send(buffer, size, hostname, port);
                });
            }

            void UdpClient::Connect(shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(remoteEndPoint);
            }

            void UdpClient::Connect(shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(address, port);
            }

            void UdpClient::Connect(const string& host, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(host, port);
            }

            void UdpClient::Close()
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Close();
            }

            vector<uint8_t> UdpClient::Receive(shared_ptr<IPEndPoint>& ep)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                vector<uint8_t> vec(Available());
                mClient->ReceiveFrom(vec, ep);
                return vec;
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->Send(buffer, 0, bytes);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, shared_ptr<IPEndPoint> ep)
            {
                if (!mClient) {
                    throw null_pointer();
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, ep);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, const string& hostname, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, make_shared<IPEndPoint>(IPAddress::Parse(hostname), port));
            }
        }
    }
}
