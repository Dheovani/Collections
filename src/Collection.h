#pragma once

#include <memory>
#include <functional>
#include <initializer_list>

// Collection interface. Only true virtaul methods
// Provides a generic collection type and documentation of the methods
template <typename _Ty>
class Collection
{
protected:
    using _Args = std::initializer_list<_Ty>;

public:
    virtual ~Collection() = default;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    virtual const _Ty Get(const size_t&) const = 0;
    virtual void Sort(bool) = 0;
    virtual void Push(const _Ty&) = 0;
    virtual void PushAll(const _Args&) = 0;
    virtual void Insert(const _Ty&, const size_t&) = 0;
    virtual bool Contains(const _Ty&) const = 0;
    virtual void ForEach(const std::function<void(const _Ty&)>&) const = 0;
};