#pragma once

#include "Collection.h"

using collections::Collection, collections::Element, collections::Iterator;

namespace collections
{
    template <typename _Ty, class _El = Element<_Ty>, class _It = Iterator<_Ty>>
    class Stack : public Collection<_Ty>
    {
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
                item = item->Next;

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

            newElm->SetNext(Top);
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

            if (posElm->Next == nullptr && pos == 0)
                posElm->SetNext(newElm);
            else {
                newElm->SetNext(posElm->Next);
                posElm->SetNext(newElm);
            }
        }

        void Remove(const size_t& pos) override
        {
            p_El posElm = ((*this)[pos]), nextElm = ((*this)[pos + 1]);

            if (posElm == nullptr)
                return;

            if (nextElm == nullptr && posElm == Top)
                Top = posElm->Next;
            else
                nextElm->SetNext(posElm->Next);

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

        _It begin() const { return _It(Top); }
        _It end() const { return _It(nullptr); }
    };
}
