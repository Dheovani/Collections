#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

namespace collections
{
    template <typename _Ty>
    class Tree
    {
    protected:
        using _Args = std::initializer_list<_Ty>;

    public:
        virtual bool IsEmpty() const = 0;
        virtual size_t Size() const = 0;
        virtual void Add(const _Ty&) = 0;
        virtual void AddAll(const _Args&) = 0;
        virtual void Remove(const _Ty&) = 0;
        virtual bool Contains(const _Ty&) const = 0;
        virtual void ForEach(const std::function<void(const _Ty&)>&) const = 0;
    };

    template <typename _Ty>
    struct TreeElement
    {
        using p_El = std::shared_ptr<TreeElement>;

        p_El Father, Lchild, Rchild;
        _Ty Value;

        TreeElement()
            : Father(nullptr), Lchild(nullptr), Rchild(nullptr) {}

        TreeElement(const _Ty& val)
            : Value(val), Father(nullptr), Lchild(nullptr), Rchild(nullptr) {}

        operator _Ty () const
        {
            return Value;
        }

        bool operator==(const p_El& other) const
        {
            return other->GetValue() == Value
                && other->GetFather() == Father
                && other->GetLchild() == Lchild
                && other->GetRchild() == Rchild;
        }

        bool operator==(const TreeElement& other) const
        {
            return other.GetValue() == Value
                && other.GetFather() == Father
                && other.GetLchild() == Lchild
                && other.GetRchild() == Rchild;
        }

        _Ty GetValue() { return Value; }

        void SetValue(const _Ty& value) { this->Value = value; }

        p_El GetFather() { return Father; }

        void SetFather(const p_El& father) { this->Father = father; }

        p_El GetLchild() { return Lchild; }

        void SetLchild(const p_El& child) { this->Lchild = child; }

        p_El GetRchild() { return Rchild; }

        void SetRchild(const p_El& child) { this->Rchild = child; }
    };
}
