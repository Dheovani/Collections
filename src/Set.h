#pragma once

#include "List.h"
#include "Sorter.h"

template <typename _Ty>
class Set : public List<_Ty>
{
public:
    Set() : List<_Ty>()
    {}

    Set(const Collection<_Ty>::_Args& args)
        : List<_Ty>()
    {
        PushAll(args);
    }

    Set(const Collection<_Ty> &collection)
        : List<_Ty>()
    {
        collection.ForEach([&](const _Ty& val) {
            Push(val);
        });
    }

    void _Set(const _Ty& value, const size_t& pos) override
    {
        if (List<_Ty>::Contains(value))
            return;

        List<_Ty>::_Set(value, pos);
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