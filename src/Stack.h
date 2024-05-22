#pragma once

#include "Collection.h"

template <typename _Ty>
class Stack : public Collection<_Ty>
{
    class _El;
    using p_El = std::shared_ptr<_El>;

    p_El Top;
    size_t _Size;

public:
    Stack()
        : Top(nullptr), _Size(0)
    {}

    Stack(const Collection<_Ty>::_Args& args)
        : Top(nullptr), _Size(0)
    {
        PushAll(args);
    }

    Stack(const Collection<_Ty>& collection)
        : Top(nullptr), _Size(0)
    {
        collection.ForEach([&](const _Ty& val) {
            Push(val);
        });
    }

    const p_El operator[](const size_t& pos) const
    {
        if (pos > _Size) {
            return nullptr;
        }

        p_El item = Top;

        for (int i = (int)_Size; i > pos; --i)
            item = item->Previous;

        return item;
    }

    bool IsEmpty() const override { return Top == nullptr && _Size == 0; }

    size_t Size() const override { return _Size; }

    void Set(const _Ty& value, const size_t& pos) override
    {
        p_El posElm = ((*this)[pos]);

        if (posElm == nullptr)
            return;

        posElm->SetValue(value);
    }

    const _Ty Get(const size_t& pos) const override
    {
        const p_El el = ((*this)[pos]);
        return el != nullptr ? el->Value : _Ty();
    }

    void Delete(const _Ty& value) override
    {
        for (size_t pos = 0; pos < _Size; ++pos) {
            const p_El elm = ((*this)[pos]);

            if (elm->Value == value) {
                Remove(pos);
                --pos;
            }
        }
    }

    void Push(const _Ty& value) override
    {
        p_El newElm = std::make_shared<_El>(value);

        newElm->SetPrevious(Top);
        Top = newElm;

        ++_Size;
    }

    void PushAll(const Collection<_Ty>::_Args& values) override
    {
        for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
            Push(*it);
    }

    void Insert(const _Ty& value, const size_t& pos) override
    {
        p_El posElm = ((*this)[pos]), newElm = std::make_shared<_El>(value);

        if (posElm == nullptr)
            return;

        if (posElm->Previous == nullptr && pos == 0)
            posElm->SetPrevious(newElm);
        else {
            newElm->SetPrevious(posElm->Previous);
            posElm->SetPrevious(newElm);
        }
    }

    void Remove(const size_t& pos) override
    {
        p_El posElm = ((*this)[pos]), nextElm = ((*this)[pos + 1]);

        if (posElm == nullptr)
            return;

        if (nextElm == nullptr && posElm == Top)
            Top = posElm->Previous;
        else
            nextElm->SetPrevious(posElm->Previous);

        --_Size;
    }

    bool Contains(const _Ty& value) const override
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
        p_El current;

    public:
        Iterator(p_El ptr)
            : current(ptr)
        {}

        Iterator& operator++()
        {
            if (current)
                current = current->Previous;

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

    Iterator begin() const { return Iterator(Top); }
    Iterator end() const { return Iterator(nullptr); }

private:
    class _El
    {
        _Ty Value;
        p_El Previous;

    public:
        _El() : Previous(nullptr) {};

        _El(const _Ty& val) : Value(val), Previous(nullptr) {}

        operator _Ty () const
        {
            return Value;
        }

        bool operator==(const p_El& other) const
        {
            return other->GetPrevious() == Previous && other.GetValue() == Value;
        }

        bool operator==(const _El& other) const
        {
            return other.Previous == Previous && other.Value == Value;
        }

        _Ty GetValue() { return Value; }

        void SetValue(const _Ty& value) { this->Value = value; }

        p_El GetPrevious() { return Previous; }

        void SetPrevious(const p_El& previous) { this->Previous = previous; }

        friend class Stack<_Ty>;
    };
};