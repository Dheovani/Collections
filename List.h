#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

template <typename _Ty>
class List
{
	class _El;
	using p_El = std::shared_ptr<_El>;
    using _Args = std::initializer_list<_Ty>;

    p_El First, Last;
    size_t _Size = 0;

public:
    List()
        : First(nullptr), Last(nullptr)
    {
    };

    List(const _Args &args)
    {
        AddItems(args);
    }

    p_El operator[](const size_t& pos)
    {
        if (pos > _Size) {
            return nullptr;
        }

        p_El item = First;

        for (int i = 0; i < pos; ++i)
            item = item->Next;

        return item;
    }

    bool IsEmpty() const { return !First && !Last && !_Size; }

    size_t Size() const { return _Size; }

    void AddItem(const _Ty &value)
    {
        p_El newItem = std::make_shared<_El>(value);

        if (IsEmpty())
            Last = (First = newItem);
        else {
            Last->SetNext(newItem);
            Last = newItem;
        }

        ++_Size;
    }

    void AddItems(const _Args &values)
    {
        for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
            AddItem(*it);
    }

    void ForEach(const std::function<void(const _Ty&)>& callback)
    {
        if (IsEmpty())
            return;

        for (const _Ty& el : *this)
            callback(el);
    }

    class Iterator {
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

    Iterator begin() { return Iterator(First); }
    Iterator end() { return Iterator(nullptr); }

private:
	class _El
	{
        _Ty Value;
        p_El Next;

    public:
        _El() : Next(nullptr) {};

        _El(const _Ty &val) : Value(val), Next(nullptr) {}

		_Ty GetValue() { return Value; }

		void SetValue(const _Ty &value) { this->Value = value; }

        p_El GetNext() { return Next; }

        void SetNext(const p_El &next) { this->Next = next; }

        friend class List<_Ty>;
	};
};