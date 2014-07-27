#pragma once

#include "HashAlgorithm.h"
#include "Stream.h"
#include <cryptopp/sha3.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class LUPUS_API CryptoHash : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoHash<T>>();
                }

                virtual uint32_t BlockSize() const NOEXCEPT override
                {
                    return T::BLOCKSIZE * 8;
                }

                virtual uint32_t HashSize() const NOEXCEPT override
                {
                    return T::DIGESTSIZE * 8;
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& buffer) throw(std::out_of_range) override
                {
                    return ComputeHash(buffer, 0, (uint32_t)buffer.size());
                }

                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream> stream) throw(std::out_of_range) override
                {
                    uint32_t size = (uint32_t)(stream->Length() - stream->Position());
                    std::vector<uint8_t> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount) throw(std::out_of_range) override
                {
                    static const int digestsize = T::DIGESTSIZE;

                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    uint8_t digest[digestsize];

                    mAlgorithm.CalculateDigest(digest, input.data() + inputOffset, inputCount);

                    return std::move(std::vector<uint8_t>(digest, digest + digestsize));
                }

            private:

                T mAlgorithm;
            };

            template <>
            class LUPUS_API CryptoHash<CryptoPP::SHA3_224> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoHash<CryptoPP::SHA3_224>>();
                }

                virtual uint32_t BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual uint32_t HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& buffer) throw(std::out_of_range) override
                {
                    return ComputeHash(buffer, 0, (uint32_t)buffer.size());
                }

                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream> stream) throw(std::out_of_range) override
                {
                    uint32_t size = (uint32_t)(stream->Length() - stream->Position());
                    std::vector<uint8_t> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    std::vector<uint8_t> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_224 mAlgorithm;
            };

            template <>
            class LUPUS_API CryptoHash<CryptoPP::SHA3_256> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoHash<CryptoPP::SHA3_256>>();
                }

                virtual uint32_t BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual uint32_t HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& buffer) throw(std::out_of_range) override
                {
                    return ComputeHash(buffer, 0, (uint32_t)buffer.size());
                }

                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream> stream) throw(std::out_of_range) override
                {
                    uint32_t size = (uint32_t)(stream->Length() - stream->Position());
                    std::vector<uint8_t> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    std::vector<uint8_t> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_256 mAlgorithm;
            };

            template <>
            class LUPUS_API CryptoHash<CryptoPP::SHA3_384> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoHash<CryptoPP::SHA3_384>>();
                }

                virtual uint32_t BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual uint32_t HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& buffer) throw(std::out_of_range) override
                {
                    return ComputeHash(buffer, 0, (uint32_t)buffer.size());
                }

                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream> stream) throw(std::out_of_range) override
                {
                    uint32_t size = (uint32_t)(stream->Length() - stream->Position());
                    std::vector<uint8_t> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    std::vector<uint8_t> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_384 mAlgorithm;
            };

            template <>
            class LUPUS_API CryptoHash<CryptoPP::SHA3_512> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual std::shared_ptr<IClonable> Clone() const NOEXCEPT override
                {
                    return std::make_shared<CryptoHash<CryptoPP::SHA3_512>>();
                }

                virtual uint32_t BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual uint32_t HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& buffer) throw(std::out_of_range) override
                {
                    return ComputeHash(buffer, 0, (uint32_t)buffer.size());
                }

                virtual std::vector<uint8_t> ComputeHash(std::shared_ptr<Stream> stream) throw(std::out_of_range) override
                {
                    uint32_t size = (uint32_t)(stream->Length() - stream->Position());
                    std::vector<uint8_t> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual std::vector<uint8_t> ComputeHash(const std::vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount) throw(std::out_of_range) override
                {
                    if (inputOffset > input.size() || inputCount > input.size() - inputOffset) {
                        throw std::out_of_range("offset and size does not match buffer size");
                    }

                    std::vector<uint8_t> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_512 mAlgorithm;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
