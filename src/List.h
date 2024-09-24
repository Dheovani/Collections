#pragma once

#include "Collection.h"

using collections::Collection, collections::Element, collections::Iterator;

namespace collections
{
    template <typename _Ty, class _El = Element<_Ty>, class _It = Iterator<_Ty>>
    class List : public Collection<_Ty>
    {
        using p_El = std::shared_ptr<_El>;

        p_El First, Last;
        size_t _Size;

    public:
        List()
            : First(nullptr), Last(nullptr), _Size(0)
        {};

        List(const Collection<_Ty>::_Args& args)
            : First(nullptr), Last(nullptr), _Size(0)
        {
            PushAll(args);
        }

        List(const Collection<_Ty>& collection)
            : First(nullptr), Last(nullptr), _Size(0)
        {
            collection.ForEach([&](const _Ty& val) {
                this->Push(val);
                });
        }

        const p_El operator[](const size_t& pos) const
        {
            if (pos > _Size) {
                return nullptr;
            }

            p_El item = First;

            for (int i = 0; i < pos; ++i)
                item = item->Next;

            return item;
        }

        bool IsEmpty() const override { return !First && !Last && !_Size; }

        size_t Size() const override { return _Size; }

        virtual void Set(const _Ty& value, const size_t& pos) override
        {
            p_El posElm = ((*this)[pos]);

            if (posElm == nullptr)
                return;

            posElm->SetValue(value);
        }

        const _Ty Get(const size_t& pos) const override
        {
            const p_El el = ((*this)[pos]);
            return el != nullptr ? el->GetValue() : _Ty();
        }

        void Delete(const _Ty& value) override
        {
            for (size_t pos = 0; pos < _Size; ++pos) {
                const p_El elm = ((*this)[pos]);

                if (elm->GetValue() == value) {
                    Remove(pos);
                    --pos;
                }
            }
        }

        virtual void Push(const _Ty& value) override
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

        virtual void PushAll(const Collection<_Ty>::_Args& values) override
        {
            for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
                Push(*it);
        }

        virtual void Insert(const _Ty& value, const size_t& pos) override
        {
            p_El posElm = ((*this)[pos]),
                prevElm = ((*this)[pos - 1]),
                newItem = std::make_shared<_El>(value);

            if (posElm == nullptr)
                return;

            newItem->SetNext(posElm);
            prevElm->SetNext(newItem);
        }

        void Remove(const size_t& pos) override
        {
            p_El posElm = ((*this)[pos]), prevElm = ((*this)[pos - 1]);

            if (posElm == nullptr)
                return;

            if (prevElm == nullptr && posElm == First && pos == 0)
                First = posElm->GetNext();
            else if (prevElm)
                prevElm->SetNext(posElm->GetNext());

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

        _It begin() const { return _It(First); }
        _It end() const { return _It(nullptr); }
    };
}
