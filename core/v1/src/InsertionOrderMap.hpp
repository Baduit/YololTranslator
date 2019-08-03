#pragma once

#include <vector>
#include <algorithm>
#include <utility>


// not fast, it works fine and i don't have performance issues in the software
// but if in the future i do, it could easily be optimized
template <typename Key, typename Value>
class InsertionOrderMap
{
public:
    InsertionOrderMap() = default;
    virtual ~InsertionOrderMap() = default;

    Value&  operator[](const Key& k)
    {
        auto i = find(k);
        if (i != _container.end())
            return i->second;
        
        push_back(k, {});
        return _container.back().second;
    }

    auto    find(const Key& k)
    {
        for (auto i = _container.begin(); i != _container.end(); ++i)
            if (i->first == k)
                return i;
        return _container.end();
    }

    void push_back(const std::pair<Key, Value>& p)
    {
        _container.push_back(p);
    }

    void push_back(const Key& k, const Value& v)
    {
        _container.push_back(std::make_pair(k, v));
    }

    auto	begin()	{ return _container.begin(); }
    auto	cbegin() const { return _container.cbegin(); }
    auto	end() { return _container.end(); }
    auto	cend() const { return _container.cend(); }

    auto	rbegin()	{ return _container.rbegin(); }
    auto	crbegin() const { return _container.crbegin(); }
    auto	rend() { return _container.rend(); }
    auto	crend() const { return _container.crend(); }

private:
    std::vector<std::pair<Key, Value>>  _container;
};