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
#include "HashAlgorithm.h"
#include "Internal/CryptoHash.h"
#include <algorithm>
#include <cctype>
#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>
#include <cryptopp/md5.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/tiger.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            vector<uint8_t> HashAlgorithm::TransformFinalBlock(const vector<uint8_t>& input, size_t inputOffset, size_t inputCount)
            {
                return std::move(ComputeHash(input, inputOffset, inputCount));
            }

            size_t HashAlgorithm::TransformBlock(const vector<uint8_t>& input, size_t inputOffset, size_t inputCount, vector<uint8_t>& output, size_t outputOffset)
            {
                vector<uint8_t> buffer = ComputeHash(input, inputOffset, inputCount);
                auto iterator = begin(output) + outputOffset;

                if (buffer.size() > output.size() - outputOffset) {
                    throw out_of_range("Transformed bytes exceeding output vector");
                }


                for_each(begin(buffer), end(buffer), [&iterator](const uint8_t& byte) {
                    *(iterator++) = byte;
                });

                return (size_t)buffer.size();
            }

            HashAlgorithmFactory::HashAlgorithmFactory()
            {
                mPrototypes["sha1"] = make_shared<CryptoHash<CryptoPP::SHA1>>();
                mPrototypes["sha224"] = make_shared<CryptoHash<CryptoPP::SHA224>>();
                mPrototypes["sha256"] = make_shared<CryptoHash<CryptoPP::SHA256>>();
                mPrototypes["sha384"] = make_shared<CryptoHash<CryptoPP::SHA384>>();
                mPrototypes["sha512"] = make_shared<CryptoHash<CryptoPP::SHA512>>();
                mPrototypes["sha3-224"] = make_shared<CryptoHash<CryptoPP::SHA3_224>>();
                mPrototypes["sha3-256"] = make_shared<CryptoHash<CryptoPP::SHA3_256>>();
                mPrototypes["sha3-384"] = make_shared<CryptoHash<CryptoPP::SHA3_384>>();
                mPrototypes["sha3-512"] = make_shared<CryptoHash<CryptoPP::SHA3_512>>();
                mPrototypes["tiger"] = make_shared<CryptoHash<CryptoPP::Tiger>>();
                mPrototypes["whirlpool"] = make_shared<CryptoHash<CryptoPP::Whirlpool>>();
                mPrototypes["ripemd128"] = make_shared<CryptoHash<CryptoPP::RIPEMD128>>();
                mPrototypes["ripemd160"] = make_shared<CryptoHash<CryptoPP::RIPEMD160>>();
                mPrototypes["ripemd256"] = make_shared<CryptoHash<CryptoPP::RIPEMD256>>();
                mPrototypes["ripemd320"] = make_shared<CryptoHash<CryptoPP::RIPEMD320>>();
                mPrototypes["md5"] = make_shared<CryptoHash<CryptoPP::Weak::MD5>>();
            }

            HashAlgorithmFactory& HashAlgorithmFactory::GetInstance()
            {
                static HashAlgorithmFactory instance;
                return instance;
            }

            shared_ptr<HashAlgorithm> HashAlgorithmFactory::Create(const String& hash) const
            {
                auto it = mPrototypes.find(hash.ToLower());

                if (it != end(mPrototypes)) {
                    return it->second->Clone();
                }

                return nullptr;
            }
        }
    }
}
