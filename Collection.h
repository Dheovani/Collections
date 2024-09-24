#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

namespace collections
{
    // Collection interface. Only true virtaul methods
    // Provides a generic collection type and documentation of the methods
    template <typename _Ty>
    class Collection
    {
    protected:
        using _Args = std::initializer_list<_Ty>;

    public:
        virtual ~Collection() = default;
        virtual bool IsEmpty() const = 0;
        virtual size_t Size() const = 0;
        virtual void Set(const _Ty&, const size_t&) = 0;
        virtual const _Ty Get(const size_t&) const = 0;
        virtual void Delete(const _Ty&) = 0;
        virtual void Push(const _Ty&) = 0;
        virtual void PushAll(const _Args&) = 0;
        virtual void Insert(const _Ty&, const size_t&) = 0;
        virtual void Remove(const size_t&) = 0;
        virtual bool Contains(const _Ty&) const = 0;
        virtual void ForEach(const std::function<void(const _Ty&)>&) const = 0;
    };

    // Default element struct, responsible for storing the value
    template <typename _Ty>
    struct Element
    {
        using p_El = std::shared_ptr<Element<_Ty>>;

        _Ty Value;
        p_El Next;

        Element() : Next(nullptr) {};

        Element(const _Ty& val) : Value(val), Next(nullptr) {}

        operator _Ty () const
        {
            return Value;
        }

        bool operator==(const p_El& other) const
        {
            return other->GetNext() == Next && other.GetValue() == Value;
        }

        bool operator==(const Element& other) const
        {
            return other.Next == Next && other.Value == Value;
        }

        _Ty GetValue() { return Value; }

        void SetValue(const _Ty& value) { this->Value = value; }

        p_El GetNext() { return Next; }

        void SetNext(const p_El& next) { this->Next = next; }
    };

    // Default iterator
    template <typename _Ty>
    struct Iterator
    {
        using p_El = std::shared_ptr<Element<_Ty>>;

        p_El current;

        Iterator(p_El ptr) : current(ptr) {}

        Iterator& operator++()
        {
            if (current)
                current = current->Next;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);

            return temp;
        }

        _Ty& operator*()
        {
            return current->Value;
        }

        _Ty* operator->()
        {
            return &(current->Value);
        }

        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
    };
}