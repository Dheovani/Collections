#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

template <typename _Ty>
class Tree
{
	class _El;
    using p_El = std::shared_ptr<_El>;
    using _Args = std::initializer_list<_Ty>;

    p_El Root;
    size_t _Size;

public:
    Tree()
        : Root(nullptr), _Size(0)
    {}

    Tree(const _Args& args)
        : Root(nullptr), _Size(0)
    {
        PushAll(args);
    }

    Tree(const Collection<_Ty>& collection)
        : Root(nullptr), _Size(0)
    {
        collection.ForEach([&](const _Ty& val) {
            Push(val);
        });
    }

    bool IsEmpty() const { return Root == nullptr && _Size == 0; }

    size_t Size() const { return _Size; }

    void Push(const _Ty& value)
    {
        p_El el = std::make_shared<_El>(value), father = Root;
        ++_Size;

        while (father != nullptr) {
            if (value < father->Value) {
                if (father->Lchild == nullptr) {
                    el->SetFather(father);
                    father->SetLchild(el);
                    Balance(father);

                    return;
                }
                else father = father->Lchild;
            }
            else {
                if (father->Rchild == nullptr) {
                    el->SetFather(father);
                    father->SetRchild(el);
                    Balance(father);

                    return;
                }
                else father = father->Rchild;
            }
        }

        Root = el;
    }

    void PushAll(const _Args& values)
    {
        for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
            Push(*it);
    }

    bool Contains(const _Ty& value) const
    {
        bool contains = false;

        ForEach([&contains, value](const _Ty& v2) {
            if (v2 == value) {
                contains = true;
            }
        });

        return contains;
    }

    void ForEach(const p_El& root, const std::function<void(const _Ty&)>& callback) const
    {
        if (root != nullptr) {
            callback(root->Value);

            ForEach(root->Lchild, callback);
            ForEach(root->Rchild, callback);
        }
    }

    void ForEach(const std::function<void(const _Ty&)>& callback) const
    {
        ForEach(Root, callback);
    }

private:
    class _El
    {
        p_El Father, Lchild, Rchild;
        _Ty Value;

    public:
        _El() : Father(nullptr), Lchild(nullptr), Rchild(nullptr) {}

        _El(const _Ty& val)
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

        bool operator==(const _El& other) const
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

        friend class Tree<_Ty>;
    };

    int GetHeight(p_El el) const
    {
        int left = 0, right = 0;

        if (el->Lchild != nullptr)
            left = GetHeight(el->Lchild) + 1;

        if (el->Rchild != nullptr)
            right = GetHeight(el->Rchild) + 1;

        return left > right ? left : right;
    }
    
    int BalanceFactor(p_El el) const
    {
        int left = 0, right = 0;

        if (el->Lchild != nullptr)
            left = GetHeight(el->Lchild) + 1;

        if (el->Rchild != nullptr)
            right = GetHeight(el->Rchild) + 1;

        return left - right;
    }

    p_El SimpleRightRotation(p_El el)
    {
        p_El father = el->Father, left = el->Lchild;

        el->SetLchild(left->Rchild);
        el->SetFather(left);

        left->SetRchild(el);
        left->SetFather(father);

        if (left->Father == nullptr)
            Root = left;
        else {
            if (father->Lchild == el)
                father->SetLchild(left);
            else
                father->SetRchild(left);
        }

        return left;
    }

    p_El SimpleLeftRotation(p_El el)
    {
        p_El father = el->Father, right = el->Rchild;

        el->SetRchild(right->Lchild);
        el->SetFather(right);

        right->SetLchild(el);
        right->SetFather(father);

        if (right->Father == nullptr)
            Root = right;
        else {
            if (father->Lchild == el)
                father->SetLchild(right);
            else
                father->SetRchild(right);
        }

        return right;
    }
    
    p_El DoubleLeftRotation(p_El el)
    {
        el->SetRchild(SimpleRightRotation(el->Rchild));
        return SimpleLeftRotation(el);
    }

    p_El DoubleRightRotation(p_El el)
    {
        el->SetLchild(SimpleLeftRotation(el->Lchild));
        return SimpleRightRotation(el);
    }

    void Balance(p_El el)
    {
        while (el != nullptr) {
            const int factor = BalanceFactor(el);

            if (factor > 1) {
                if (BalanceFactor(el->Lchild) > 0)
                    SimpleRightRotation(el);
                else
                    DoubleRightRotation(el);
            }
            else if (factor < -1) {
                if (BalanceFactor(el->Rchild) < 0)
                    SimpleLeftRotation(el);
                else
                    DoubleLeftRotation(el);
            }

            el = el->Father;
        }
    }
};