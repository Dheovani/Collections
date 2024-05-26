#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

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