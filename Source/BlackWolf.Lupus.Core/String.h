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

#include "Utility.h"
#include "IClonable.h"
#include <vector>
#include <functional>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
#ifdef _UNICODE
    typedef wchar_t Char;
    typedef char32_t Char32;
#else
    typedef char16_t Char;
    typedef char32_t Char32;
#endif

    LUPUSCORE_API Char ToChar(char);
    LUPUSCORE_API Char ToChar(wchar_t);

    enum class StringSplitOption {
        None,
        RemoveEmptyEntries
    };

    enum class StringCaseSensitivity {
        CaseSensitive,
        CaseInsensitive
    };

    class LUPUSCORE_API String
    {
    public:

        typedef Char* iterator;
        typedef const Char* const_iterator;

        inline iterator begin() { return &this->operator[](0); }
        inline const_iterator begin() const { return &this->operator[](0); }
        inline const_iterator cbegin() const { return &this->operator[](0); }
        inline iterator end() { return &this->operator[](this->Length()); }
        inline const_iterator end() const { return &this->operator[](this->Length()); }
        inline const_iterator cend() const { return &this->operator[](this->Length()); }

        String();
        String(Char ch, size_t count = 1) NOEXCEPT;
        String(const char* str) throw(std::runtime_error);
        String(const Char* str) NOEXCEPT;
        String(const Char* str, size_t offset, size_t size) throw(std::out_of_range);
        String(const std::string& str) NOEXCEPT;
        String(const std::string& str, size_t offset, size_t size) throw(std::out_of_range);
        String(const String& str) NOEXCEPT;
        String(const String& str, size_t offset, size_t size) throw(std::out_of_range);
        String(String&&) NOEXCEPT;
        virtual ~String();

        Char& operator[](size_t index) throw(std::out_of_range);
        const Char& operator[](size_t index) const throw(std::out_of_range);
        virtual String Clone() const NOEXCEPT;
        virtual const Char* Data() const NOEXCEPT;
        virtual const Char* Data(size_t startIndex) const throw(std::out_of_range);
        virtual bool IsEmpty() const NOEXCEPT;
        virtual size_t Length() const NOEXCEPT;

        virtual String Append(Char ch) const NOEXCEPT;
        virtual String Append(String str) const NOEXCEPT;
        virtual String Append(String str, size_t offset, size_t size) const throw(std::out_of_range);
        virtual int Compare(String str, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const NOEXCEPT;
        virtual int Compare(String str, size_t offset, size_t size, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const throw(std::out_of_range);
        virtual int Compare(size_t offset, size_t size, String cmpString, size_t cmpOffset, size_t cmpSize, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const throw(std::out_of_range);
        virtual bool Contains(String str) const NOEXCEPT;
        virtual void CopyTo(size_t srcIndex, std::vector<Char>& dst, size_t dstIndex, size_t count) const throw(std::out_of_range);
        virtual bool EndsWith(String str) const NOEXCEPT;
        virtual bool EndsWith(String str, size_t offset, size_t size) const throw(std::out_of_range);
        virtual int IndexOf(Char ch) const NOEXCEPT;
        virtual int IndexOf(String str) const NOEXCEPT;
        virtual int IndexOf(Char ch, size_t offset) const throw(std::out_of_range);
        virtual int IndexOf(String str, size_t offset) const throw(std::out_of_range);
        virtual int IndexOf(Char ch, size_t offset, size_t count) const throw(std::out_of_range);
        virtual int IndexOf(String str, size_t offset, size_t count) const throw(std::out_of_range);
        virtual int IndexOfAny(const std::vector<Char>& chars) const NOEXCEPT;
        virtual int IndexOfAny(const std::vector<Char>& chars, size_t offset) const throw(std::out_of_range);
        virtual int IndexOfAny(const std::vector<Char>& chars, size_t offset, size_t count) const throw(std::out_of_range);
        virtual String Insert(size_t startIndex, Char ch) const throw(std::out_of_range);
        virtual String Insert(size_t startIndex, String str) const throw(std::out_of_range);
        virtual String Insert(size_t startIndex, String str, size_t offset, size_t count) const throw(std::out_of_range);
        virtual int LastIndexOf(Char ch) const NOEXCEPT;
        virtual int LastIndexOf(String str) const NOEXCEPT;
        virtual int LastIndexOf(Char ch, size_t offset) const throw(std::out_of_range);
        virtual int LastIndexOf(String str, size_t offset) const throw(std::out_of_range);
        virtual int LastIndexOf(Char ch, size_t offset, size_t count) const throw(std::out_of_range);
        virtual int LastIndexOf(String str, size_t offset, size_t count) const throw(std::out_of_range);
        virtual int LastIndexOfAny(const std::vector<Char>& chars) const NOEXCEPT;
        virtual int LastIndexOfAny(const std::vector<Char>& chars, size_t offset) const throw(std::out_of_range);
        virtual int LastIndexOfAny(const std::vector<Char>& chars, size_t offset, size_t count) const throw(std::out_of_range);
        virtual String Remove(size_t startIndex) const throw(std::out_of_range);
        virtual String Remove(size_t startIndex, size_t count) const throw(std::out_of_range);
        virtual String Replace(Char oldCh, Char newCh) const NOEXCEPT;
        virtual String Replace(String oldStr, String newStr) const throw(std::out_of_range);
        virtual String Reverse() const NOEXCEPT;
        virtual String Reverse(size_t startIndex, size_t count) const throw(std::out_of_range);
        virtual std::vector<String> Split(const std::vector<Char>& delimiter, StringSplitOption = StringSplitOption::None) const throw(format_error);
        virtual std::vector<String> Split(const std::vector<Char>& delimiter, size_t count, StringSplitOption = StringSplitOption::None) const throw(format_error);
        virtual std::vector<String> Split(const String& delimiter, StringSplitOption = StringSplitOption::None) const throw(format_error);
        virtual std::vector<String> Split(const String& delimiter, size_t count, StringSplitOption = StringSplitOption::None) const throw(format_error);
        virtual bool StartsWith(String str) const NOEXCEPT;
        virtual bool StartsWith(String str, size_t offset, size_t size) const throw(std::out_of_range);
        virtual String Substring(size_t startIndex) const throw(std::out_of_range);
        virtual String Substring(size_t startIndex, size_t count) const throw(std::out_of_range);
        virtual String ToLower() const NOEXCEPT;
        virtual String ToUpper() const NOEXCEPT;
        virtual std::string ToUTF8() const NOEXCEPT;
        virtual std::u16string ToUTF16() const NOEXCEPT;
        virtual std::u32string ToUTF32() const throw(std::runtime_error);
        virtual String Trim() const NOEXCEPT;

        bool operator==(String str) const NOEXCEPT;
        bool operator!=(String str) const NOEXCEPT;
        bool operator<(String str) const NOEXCEPT;
        bool operator>(String str) const NOEXCEPT;
        bool operator<=(String str) const NOEXCEPT;
        bool operator>=(String str) const NOEXCEPT;
        String operator+(Char ch) const NOEXCEPT;
        String operator+(const String& str) const NOEXCEPT;
        String& operator=(Char ch) NOEXCEPT;
        String& operator=(const String& str) NOEXCEPT;
        String& operator=(String&&);
        String& operator+=(Char ch) NOEXCEPT;
        String& operator+=(const String& str) NOEXCEPT;

        static String FromUTF8(const std::string& str);
        static String FromUTF16(const std::u16string& str);
        static String FromUTF32(const std::u32string& str);

    protected:

        size_t AddRef();
        size_t ReleaseRef();
        size_t RefCount() const;

        static const size_t Capacity;
        static size_t ComputeCapacity(size_t length);

    private:

        explicit String(void*);

        void* mString = nullptr;
        size_t* mCount = nullptr;
#ifdef _DEBUG
        std::string mDebugString;
#endif
    };

    template <typename CharT>
    inline String operator==(CharT lhs, const String& rhs)
    {
        return String(lhs) == rhs;
    }

    template <typename CharT>
    inline String operator==(const CharT* lhs, const String& rhs)
    {
        return String(lhs) == rhs;
    }

    template <typename CharT>
    inline String operator!=(CharT lhs, const String& rhs)
    {
        return String(lhs) != rhs;
    }

    template <typename CharT>
    inline String operator!=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) != rhs;
    }

    template <typename CharT>
    inline String operator<(const CharT* lhs, const String& rhs)
    {
        return String(lhs) < rhs;
    }

    template <typename CharT>
    inline String operator>(const CharT* lhs, const String& rhs)
    {
        return String(lhs) > rhs;
    }

    template <typename CharT>
    inline String operator<=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) <= rhs;
    }

    template <typename CharT>
    inline String operator>=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) >= rhs;
    }

    template <typename CharT>
    inline String operator+(CharT lhs, const String& rhs)
    {
        return String(lhs) + rhs;
    }

    template <typename CharT>
    inline String operator+(const CharT* lhs, const String& rhs)
    {
        return String(lhs) + rhs;
    }
}

namespace std {
    template <>
    struct hash < Lupus::String >
    {
        typedef Lupus::String argument_type;
        typedef std::size_t result_type;

        hash() = default;
        hash(const hash&) = default;
        ~hash() = default;

        result_type operator()(const Lupus::String& str) const
        {
            return hash<string>()(str.ToUTF8());
        }
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
