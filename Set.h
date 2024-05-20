#pragma once

#include "Collection.h"

template <typename _Ty>
class Set : public Collection<_Ty>
{
    class _El;
    using p_El = std::shared_ptr<_El>;

    p_El First, Last;
    size_t _Size = 0;

public:
    Set()
        : First(nullptr), Last(nullptr), _Size(0)
    {
    };

    Set(const Collection<_Ty>::_Args& args)
        : First(nullptr), Last(nullptr), _Size(0)
    {
        AddItems(args);
    }

    Set(const Collection<_Ty> &collection)
        : First(nullptr), Last(nullptr), _Size(0)
    {
        collection.ForEach([&](const _Ty& val) {
            this->AddItem(val);
        });
    }

    const p_El operator[](const size_t& pos) const
    {
        p_El item = First;

        for (size_t i = 0; i < pos; ++i) {
            if (item == nullptr) {
                return nullptr;
            }
            item = item->Next;
        }

        return item;
    }

    bool IsEmpty() const override { return !First && !Last && !_Size; }

    size_t Size() const override { return _Size; }

    void AddItem(const _Ty& value) override
    {
        if (Contains(value))
            return;

        p_El newItem = std::make_shared<_El>(value);

        if (IsEmpty())
            Last = (First = newItem);
        else {
            Last->SetNext(newItem);
            Last = newItem;
        }

        ++_Size;
    }

    void AddItems(const Collection<_Ty>::_Args& values) override
    {
        for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
            AddItem(*it);
    }

    bool Contains(const _Ty& value) const
    {
        for (const _Ty& el : *this) {
            if (el == value)
                return true;
        }

        return false;
    }

    void ForEach(const std::function<void(const _Ty&)>& callback) const override
    {
        if (IsEmpty())
            return;

        for (const _Ty& el : *this)
            callback(el);
    }

    class Iterator
    {
    private:
        p_El current;

    public:
        Iterator(p_El ptr)
            : current(ptr)
        {
        }

        Iterator& operator++()
        {
            if (current)
                current = current->GetNext();

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

    Iterator begin() const { return Iterator(First); }
    Iterator end() const { return Iterator(nullptr); }

private:
    class _El
    {
        _Ty Value;
        p_El Next;

    public:
        _El() : Next(nullptr) {};

        _El(const _Ty& val) : Value(val), Next(nullptr) {}

        operator _Ty () const
        {
            return Value;
        }

        _Ty GetValue() { return Value; }

        void SetValue(const _Ty& value) { this->Value = value; }

        p_El GetNext() { return Next; }

        void SetNext(const p_El& next) { this->Next = next; }

        friend class Set<_Ty>;
    };
};