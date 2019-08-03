#pragma once

#include <string>
#include <cstring>
#include <algorithm>

namespace StringFunction
{
bool replaceAll(std::string &s, const std::string &search, const std::string &replace)
{
    bool result = false;
    
    for(size_t pos = 0; ; pos += replace.length())
    {
        pos = s.find(search, pos);
        if(pos == std::string::npos)
            break;
        s.erase(pos, search.length());
        s.insert(pos, replace);
        result = true;
    }

    return result;
}

bool replaceEnd(std::string &s, const std::string &search, const std::string &replace)
{
    std::string end;
    std::string tmp = s;
    std::string cmp = search;
    std::reverse(cmp.begin(), cmp.end());

    for (auto i = tmp.size() - 1; i > 0; --i)
    {
        end += tmp[i];
        tmp.pop_back();
        if (end == cmp)
        {
            tmp += replace;
            s = tmp;
            return true;
        }
    }
    return false;
}

void toLower(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](char c){ return std::tolower(c); });
}
}