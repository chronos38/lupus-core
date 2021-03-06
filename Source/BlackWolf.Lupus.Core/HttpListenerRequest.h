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

#include "String.h"
#include "Task.h"
#include <vector>
#include <memory>
#include <cstdint>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Stream;
    class InputStream;
    class Uri;
    class Version;

    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                class X509Certificate;
            }
        }
    }

    namespace Text {
        class Encoding;
    }

    namespace Net {
        namespace Sockets {
            class IPEndPoint;
        }

        class Cookie;

        class LUPUSCORE_API HttpListenerRequest : public NonCopyable
        {
        public:

            HttpListenerRequest() = delete;
            HttpListenerRequest(
                const std::vector<uint8_t>& buffer,
                std::shared_ptr<Sockets::IPEndPoint> localEP,
                std::shared_ptr<Sockets::IPEndPoint> remoteEP,
                bool authenticated = false,
                bool secure = false);
            virtual ~HttpListenerRequest() = default;

            virtual const std::vector<String>& AcceptTypes() const NOEXCEPT;
            virtual std::shared_ptr<Text::Encoding> ContentEncoding() const NOEXCEPT;
            virtual int64_t ContentLength() const NOEXCEPT;
            virtual String ContentType() const NOEXCEPT;
            virtual const NameCollection<std::shared_ptr<Cookie>>& Cookies() const NOEXCEPT;
            virtual bool HasEntityBody() const NOEXCEPT;
            virtual const NameValueCollection& Headers() const NOEXCEPT;
            virtual String HttpMethod() const NOEXCEPT;
            virtual std::shared_ptr<Stream> InputStream() const NOEXCEPT;
            virtual bool IsAuthenticated() const NOEXCEPT;
            virtual bool IsLocal() const NOEXCEPT;
            virtual bool IsSecureConnection() const NOEXCEPT;
            virtual bool KeepAlive() const NOEXCEPT;
            virtual String LocalAddress() const NOEXCEPT;
            virtual std::shared_ptr<Sockets::IPEndPoint> LocalEndPoint() const NOEXCEPT;
            virtual std::shared_ptr<Version> ProtocolVersion() const NOEXCEPT;
            virtual const NameValueCollection& QueryString() const NOEXCEPT;
            virtual String RawHeader() const NOEXCEPT;
            virtual String RemoteAddress() const NOEXCEPT;
            virtual std::shared_ptr<Sockets::IPEndPoint> RemoteEndPoint() const NOEXCEPT;
            virtual std::shared_ptr<Uri> Url() const NOEXCEPT;
            virtual String UserAgent() const NOEXCEPT;
            virtual const std::vector<String>& UserLanguages() const NOEXCEPT;

            virtual String ToString() const NOEXCEPT;

            /**
             * \warning Not implemented.
             */
            virtual Task<std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate>> GetClientCertificateAsync() const NOEXCEPT;

            /**
             * \warning Not implemented.
             */
            virtual std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> GetClientCertificate() const NOEXCEPT;

        private:

            std::shared_ptr<Lupus::Stream> mStream;
            std::shared_ptr<Sockets::IPEndPoint> mLocalEP;
            std::shared_ptr<Sockets::IPEndPoint> mRemoteEP;
            std::shared_ptr<Uri> mUrl;
            std::shared_ptr<Version> mVersion;
            std::shared_ptr<Text::Encoding> mEncoding;
            NameCollection<std::shared_ptr<Cookie>> mCookies;
            NameValueCollection mHeaders;
            NameValueCollection mQuery;
            std::vector<String> mAcceptedTypes;
            std::vector<String> mLanguages;
            String mContentType;
            String mMethod;
            String mUserAgent;
            String mRawHeader;
            bool mAuthenticated = false;
            bool mSecure = false;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
