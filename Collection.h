#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

template <typename _Ty>
class Collection
{
    using _Args = std::initializer_list<_Ty>;

public:
    virtual ~Collection() = default;

    virtual bool IsEmpty() const = 0;

    virtual size_t Size() const = 0;

    virtual void AddItem(const _Ty& value) = 0;

    virtual void AddItems(const _Args& values) = 0;

    virtual bool Contains(const _Ty& value) const = 0;

    virtual void ForEach(const std::function<void(const _Ty&)>& callback) const = 0;
};