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
#pragma once

#include "NetDefinitions.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            //! Sockettyp
            enum class SocketType {
                Unspecified = 0, //!< Typ ist nicht spezifiziert und von daher variabl.
                SeqPacket = SOCK_SEQPACKET, //!< Squenzpaket-Stream Socket
                Stream = SOCK_STREAM, //!< Streaming Socket (TCP).
                Datagram = SOCK_DGRAM, //!< Datagram Socket (UDP).
                Rdm = SOCK_RDM, //!< reliably-delivered message.
                Raw = SOCK_RAW //!< Socket verwendet normale NAT Pakete.
            };

            //! Netzwerkprotokoll
            enum class ProtocolType {
                Unspecified = 0, //!< Protokoll ist nicht spezifiziert und von daher variabl.
                IP = IPPROTO_IP,
                IPv4 = IPPROTO_IPV4,
                IPv6 = IPPROTO_IPV6,
                TCP = IPPROTO_TCP,
                UDP = IPPROTO_UDP,
                ICMP = IPPROTO_ICMP,
                IGMP = IPPROTO_IGMP,
                EGP = IPPROTO_EGP,
                PUP = IPPROTO_PUP,
                IDP = IPPROTO_IDP,
                Routing = IPPROTO_ROUTING,
                Fragment = IPPROTO_FRAGMENT,
                ESP = IPPROTO_ESP,
                AH = IPPROTO_AH,
                ICMPv6 = IPPROTO_ICMPV6,
                None = IPPROTO_NONE,
                PIM = IPPROTO_PIM,
                SCTP = IPPROTO_SCTP,
                Raw = IPPROTO_RAW,
                IPv6HopByHopOptions = IPPROTO_HOPOPTS,
                IPv6DestinationOptions = IPPROTO_DSTOPTS
            };

            //! Adressart
            enum class AddressFamily {
                Unspecified = AF_UNSPEC, //!< Domäne ist nicht spezifiziert und von daher variabl.
                InterNetwork = AF_INET, //!< IPv4
                InterNetworkV6 = AF_INET6, //!< IPv6
                AppleTalk = AF_APPLETALK,
                UNIX = AF_UNIX,
                IPX = AF_IPX
            };

            enum class SocketPollFlags : short {
                Read = LU_POLLIN, //!< Überprüft ob Daten zum lesen vorhanden sind.
                Write = LU_POLLOUT, //!< Überprüft ob Daten zum schreiben vorhanden sind.
                OutOfBand = LU_POLLPRI, //!< Überprüft ob Out-Of-Band Daten vorhanden sind.
                Error = POLLERR,
                HungUp = POLLHUP,
                Invalid = POLLNVAL,
                Timeout
            };

            LupusFlagEnumeration(SocketPollFlags);

            enum class SocketShutdown {
                Receive = LU_SHUTDOWN_READ, //!< Schließt die Leseverbindung.
                Send = LU_SHUTDOWN_WRITE, //!< Schließt die Schreibverbindung.
                Both = LU_SHUTDOWN_BOTH //!< Schließt sowohl Lese- als auch Schreibverbindung.
            };

            enum class SocketFlags {
                None = 0,
                OutOfBand = MSG_OOB,
                Peek = MSG_PEEK,
                DontRoute = MSG_DONTROUTE,
                Truncated = MSG_CTRUNC
            };

            LupusFlagEnumeration(SocketFlags);

            enum SocketError {
#ifdef _MSC_VER
                NotInitialized = WSANOTINITIALISED,
                NetworkDown = WSAENETDOWN,
                SegFault = WSAEFAULT,
                NotConnected = WSAENOTCONN,
                Interrupted = WSAEINTR,
                InProgress = WSAEINPROGRESS,
                NetworkReset = WSAENETRESET,
                NotSocket = WSAENOTSOCK,
                NotSupported = WSAEOPNOTSUPP,
                Shutdown = WSAESHUTDOWN,
                WouldBlock = WSAEWOULDBLOCK,
                MessageSize = WSAEMSGSIZE,
                InvalidArgument = WSAEINVAL,
                ConnectionAborted = WSAECONNABORTED,
                Timeout = WSAETIMEDOUT,
                ConnectionRefused = WSAECONNREFUSED,
                Access = WSAEACCES,
                NoBufferAvailable = WSAENOBUFS,
                RemoteHostUnreachable = WSAEHOSTUNREACH,
                ConnectionReset = WSAECONNRESET
#else
                WouldBlock = EWOULDBLOCK,
                InvalidSocket = EDADF,
                ConnectionRefused = ECONNREFUSED,
                SegFault = EFAULT,
                Interrupted = EINTR,
                InvalidArgument = EINVAL,
                NotConnected = ENOTCONN,
                NotSocket = ENOTSOCK,
                Access = EACCES,
                ConnectionReset = ECONNRESET,
                NoAddressSet = EDESTADDRREQ,
                IsAlreadyConnected = EISCONN,
                MessageSize = EMSGSIZE,
                NoBufferAvailable = ENOBUFS,
                NoMemory = ENOMEM,
                NotSupported = EOPNOTSUPP,
                LocalEndShutdown = EPIPE
#endif
            };
        }
    }
}
