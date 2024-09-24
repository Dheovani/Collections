#pragma once

#include "List.h"

using collections::List, collections::Element, collections::Iterator;

namespace collections
{
    template <typename _Ty, class _El = Element<_Ty>, class _It = Iterator<_Ty>>
    class UniqList : public List<_Ty, _El, _It>
    {
    public:
        UniqList() : List<_Ty>()
        {}

        UniqList(const Collection<_Ty>::_Args& args) : List<_Ty>()
        {
            PushAll(args);
        }

        UniqList(const Collection<_Ty>& collection) : List<_Ty>()
        {
            collection.ForEach([&](const _Ty& val) { Push(val); });
        }

        void Set(const _Ty& value, const size_t& pos) override
        {
            if (List<_Ty>::Contains(value))
                return;

            List<_Ty>::Set(value, pos);
        }

        void Push(const _Ty& value) override
        {
            if (List<_Ty>::Contains(value))
                return;

            List<_Ty>::Push(value);
        }

        void PushAll(const Collection<_Ty>::_Args& values) override
        {
            for (auto it = std::rend(values) - 1; it >= std::rbegin(values); --it)
                Push(*it);
        }

        void Insert(const _Ty& value, const size_t& pos) override
        {
            if (List<_Ty>::Contains(value))
                return;

            List<_Ty>::Insert(value, pos);
        }
    };
}
