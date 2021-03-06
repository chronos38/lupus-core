/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "UdpClient.h"
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
                if (!ep) {
                    throw null_pointer("ep");
                }

                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(ep);
            }

            UdpClient::UdpClient(uint16_t port, AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Datagram, ProtocolType::UDP);
                mClient->Bind(make_shared<IPEndPoint>(IPAddress::Loopback(), port));
            }

            UdpClient::UdpClient(const String& hostname, uint16_t port)
            {
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP);
                mClient->Connect(GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Datagram, ProtocolType::UDP));
            }

            size_t UdpClient::Available() const
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                return mClient->Available();
            }

            shared_ptr<Socket> UdpClient::Client() const
            {
                return mClient;
            }

            void UdpClient::Client(shared_ptr<Socket> client)
            {
                mClient = client;
            }

            bool UdpClient::ExclusiveAddressUse() const
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
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
                    throw invalid_operation("UdpClient is in an invalid state");
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

            Task<int> UdpClient::SendAsync(const vector<uint8_t>& buffer, size_t size, const String& hostname, uint16_t port)
            {
                return Task<int>([this, &buffer, size, &hostname, port]() {
                    return this->Send(buffer, size, hostname, port);
                });
            }

            void UdpClient::Connect(shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                mClient->Connect(remoteEndPoint);
            }

            void UdpClient::Connect(shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                mClient->Connect(address, port);
            }

            void UdpClient::Connect(const String& host, uint16_t port)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                mClient->Connect(host, port);
            }

            void UdpClient::Close()
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                mClient->Close();
            }

            vector<uint8_t> UdpClient::Receive(shared_ptr<IPEndPoint>& ep)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                vector<uint8_t> vec(Available());
                mClient->ReceiveFrom(vec, ep);
                return vec;
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                }

                return mClient->Send(buffer, 0, bytes);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, shared_ptr<IPEndPoint> ep)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, ep);
            }

            int UdpClient::Send(const vector<uint8_t>& buffer, size_t bytes, const String& hostname, uint16_t port)
            {
                if (!mClient) {
                    throw invalid_operation("UdpClient is in an invalid state");
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, make_shared<IPEndPoint>(IPAddress::Parse(hostname), port));
            }
        }
    }
}
