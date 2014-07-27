#include "Stream.h"

#include <thread>

using namespace std;

namespace Lupus {
    void Stream::CopyToAsync(shared_ptr<Stream> destination, function<void(exception_ptr, Stream*)> callback)
    {
        thread([this, destination, callback]() {
            try {
                this->CopyTo(destination);
                callback(nullptr, this);
            } catch (...) {
                callback(current_exception(), this);
            }
        }).detach();
    }
    void Stream::FlushAsync(function<void(exception_ptr, Stream*)> callback)
    {
        thread([this, callback]() {
            try {
                this->Flush();
                callback(nullptr, this);
            } catch (...) {
                callback(current_exception(), this);
            }
        }).detach();
    }

    void Stream::ReadAsync(vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, Stream*, int32_t)> callback)
    {
        thread([this, &buffer, offset, size, callback]() {
            try {
                callback(nullptr, this, this->Read(buffer, offset, size));
            } catch (...) {
                callback(current_exception(), this, -1);
            }
        }).detach();
    }

    void Stream::WriteAsync(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, Stream*, int32_t)> callback)
    {
        thread([this, &buffer, offset, size, callback]() {
            try {
                callback(nullptr, this, this->Write(buffer, offset, size));
            } catch (...) {
                callback(current_exception(), this, -1);
            }
        }).detach();
    }

    void Stream::CopyTo(shared_ptr<Stream> destination)
    {
        if (!destination) {
            throw null_pointer();
        }

        int64_t pos = Position();
        int64_t len = Length();
        int64_t dpos = destination->Position();
        int64_t dlen = destination->Length();
        int64_t size = len - pos;
        int64_t dsize = dlen - dpos;

        if (pos < 0 || len <= 0 || size <= 0 || dpos < 0 || dlen <= 0 || dsize <= 0) {
            return;
        } else if (size > dsize) {
            destination->Length(destination->Length() + size - dsize);
        }

        vector<uint8_t> buffer((uint32_t)size);
        Read(buffer, 0, (uint32_t)size);
        destination->Write(buffer, 0, (uint32_t)size);
    }

    void Stream::Flush()
    {
        throw not_supported();
    }

    void Stream::Length(int64_t length)
    {
        throw not_supported();
    }

    void Stream::Position(int64_t)
    {
        throw not_supported();
    }

    int64_t Stream::Seek(int64_t offset, SeekOrigin origin)
    {
        throw not_supported();
    }
}