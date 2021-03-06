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
#include "NetworkStream.h"
#include "Socket.h"

#include <thread>

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Sockets {
            NetworkStream::NetworkStream(shared_ptr<Sockets::Socket> socket)
            {
                if (!socket) {
                    throw null_pointer("socket");
                }

                mSocket = socket;
            }

            size_t NetworkStream::DataAvailable() const
            {
                return mSocket->Available();
            }
            
            shared_ptr<Socket> NetworkStream::Socket() const
            {
                return mSocket;
            }

            Task<int> NetworkStream::ReadAsync(vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                return Task<int>([&buffer, offset, size](shared_ptr<Sockets::Socket> socket) {
                    return socket->Receive(buffer, offset, size);
                }, mSocket);
            }
            
            Task<int> NetworkStream::WriteAsync(const vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                return Task<int>([&buffer, offset, size](shared_ptr<Sockets::Socket> socket) {
                    return socket->Send(buffer, offset, size);
                }, mSocket);
            }

            bool NetworkStream::CanRead() const
            {
                return mRead;
            }

            bool NetworkStream::CanWrite() const
            {
                return mWrite;
            }

            bool NetworkStream::CanSeek() const
            {
                return false;
            }

            void NetworkStream::Close()
            {
                mSocket->Close();
            }
            
            void NetworkStream::Close(size_t timeout)
            {
                mSocket->Close(timeout);
            }

            int64_t NetworkStream::Position() const
            {
                return 0;
            }

            int64_t NetworkStream::Length() const
            {
                return (int64_t)mSocket->Available();
            }
            
            int NetworkStream::Read(vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                if (!mRead) {
                    throw io_error("network stream is not readable");
                }

                return mSocket->Receive(buffer, offset, size);
            }
            
            int NetworkStream::ReadByte()
            {
                if (!mRead) {
                    throw io_error("network stream is not readable");
                }

                vector<uint8_t> vec(1);
                
                if (mSocket->Receive(vec, 0, 1) != 1) {
                    return -1;
                }

                return vec[0];
            }
            
            int NetworkStream::Write(const vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                if (!mWrite) {
                    throw io_error("network stream is not writable");
                }

                return mSocket->Send(buffer, offset, size);
            }
            
            void NetworkStream::WriteByte(uint8_t byte)
            {
                if (!mWrite) {
                    throw io_error("network stream is not writable");
                }

                vector<uint8_t> vec(1, byte);
                mSocket->Send(vec, 0, 1);
            }

            bool NetworkStream::Readable() const
            {
                return mRead;
            }

            void NetworkStream::Readable(bool b)
            {
                mRead = b;
            }

            bool NetworkStream::Writable() const
            {
                return mWrite;
            }

            void NetworkStream::Writable(bool b)
            {
                mWrite = b;
            }
        }
    }
}
