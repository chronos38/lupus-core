/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

#include "String.h"
#include "Event.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename T>
    class IObserver
    {
    public:
            
        virtual ~IObserver() = default;

        virtual void OnUpdate(const T& value) = 0;
        virtual void OnError(std::exception& error) = 0;
        virtual void OnComplete() = 0;
    };

    template <typename T>
    class Observable
    {
    public:

        virtual ~Observable() = default;

        virtual void Attach(std::shared_ptr<IObserver<T>> observer) NOEXCEPT final
        {
            mObservers.push_back(observer);
        }

        virtual void Detach(std::shared_ptr<IObserver<T>> observer) NOEXCEPT final
        {
            std::remove(std::begin(mObservers), std::end(mObservers), observer);
        }

        virtual void OnUpdate(const T& value) NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnUpdate(value);
            });
        }

        virtual void OnError(std::exception& ex) NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnError(ex);
            });
        }

        virtual void OnComplete() NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [](std::shared_ptr<IObserver<T>> observer) {
                observer->OnComplete();
            });
        }

    private:

        std::vector<std::shared_ptr<IObserver<T>>> mObservers = std::vector<std::shared_ptr<IObserver<T>>>(32);
    };

    template <typename Owner, typename T>
    class ObservableProperty : public NonCopyable
    {
        friend Owner;

    public:

        Event<ObservableProperty<Owner, T>, const T&> ValueChanged;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;
        ~ObservableProperty() = default;

        virtual T Get() const final
        {
            if (mGetter) {
                return mGetter();
            } else {
                throw std::runtime_error("getter is not set");
            }
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw std::runtime_error("setter is not set");
            }

            ValueChanged(this, value);
            return *this;
        }

        virtual operator T() const final
        {
            if (mGetter) {
                return mGetter();
            } else {
                throw std::runtime_error("getter is not set");
            }
        }

        virtual ObservableProperty& operator=(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw std::runtime_error("setter is not set");
            }

            ValueChanged(this, value);
            return *this;
        }

    private:

        std::function<T()> mGetter;
        std::function<void(const T&)> mSetter;
    };

    template <typename T>
    class ObservableProperty < void, T >
    {
    public:

        Event<ObservableProperty<void, T>, const T&> ValueChanged;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;
        ~ObservableProperty() = default;

        virtual const T& Get() const final
        {
            return mValue;
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            mValue = value;
            ValueChanged(this, value);

            return *this;
        }

        virtual operator T() const final
        {
            return mValue;
        }

        virtual ObservableProperty& operator=(const T& value) final
        {
            mValue = value;
            ValueChanged(this, value);

            return *this;
        }

    private:

        T mValue = T();
    };

    class LUPUSCORE_API ObservableObject : public NonCopyable
    {
    public:

        Event<ObservableObject, const String&> PropertyChanged;

        ObservableObject() = default;
        virtual ~ObservableObject() = default;

        virtual void Remove(const String& propertyName) NOEXCEPT final;
        virtual bool HasProperty(const String& propertyName) const NOEXCEPT final;
        virtual Any& operator[](const String& propertyName) NOEXCEPT final;
        virtual const Any& operator[](const String& propertyName) const NOEXCEPT final;

        template <typename T>
        void Add(const String& propertyName, const T& value = T())
        {
            mProperties[propertyName] = Any(value);
            PropertyChanged(this, propertyName);
        }

        template <typename T>
        const T& Get(const String& propertyName) const
        {
            return Any_cast<const T&>(mProperties[propertyName]);
        }

        template <typename T>
        void Set(const String& propertyName, const T& value)
        {
            mProperties[propertyName] = Any(value);
            PropertyChanged(this, propertyName);
        }

    private:

        Collection<String, Any> mProperties;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
