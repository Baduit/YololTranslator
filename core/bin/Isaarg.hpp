#pragma once

#include <vector>
#include <string_view>
#include <optional>
#include <algorithm>
#include <map>

namespace Isaarg
{

using ArgsVector = std::vector<std::string_view>;
using Flags = std::vector<char>;
using Options = std::map<std::string_view, std::vector<std::string_view>>;

// value == does not begin with a - example test => test
// flag == one character (without counting the -) can be chained but can't use the next value(s), example -A => A, -kA => k and A
// option == one or several character, cannot be chained but can use the next value(s) begin with -- example: --verbose

namespace Utils
{

bool    isFlag(std::string_view str)
{
    if (str.size() >= 2 && str[0] == '-' && str[1] != '-')
        return true;
    return false;
}

bool    isOption(std::string_view str)
{
    if (str.size() >= 3 && str[0] == '-' && str[1] == '-')
        return true;
    return false;
}

bool    isValue(std::string_view str)
{
    if (!isOption(str) && !isFlag(str))
        return true;
    return false;
}

}

// i should maybe add iterators to iterate over raw arguments, but we can already get the vector of string_view
class Args
{
    private:
        void    addFlagsFromStringView(std::string_view str)
        {
            str.remove_prefix(1);
            for (auto c: str)
            {
                if (std::find(_flags.begin(), _flags.end(), c) == _flags.end())
                    _flags.push_back(c);
            }
        }

        // instead of this function, i could have put this in the constructor initial loop,
        // it would be more optimized, but i think it is simpler to read like this
        void    addOptions()
        {
            std::string_view optionToAdd;
            bool isOptionValueToAdd = false;
            std::vector<std::string_view> valuesToAdd;
            for (const auto& s: _argv)
            {
                if (isOptionValueToAdd)
                {
                    if (Utils::isValue(s))
                    {
                        valuesToAdd.push_back(s);
                    }
                    else
                    {
                        _options[optionToAdd] = valuesToAdd;
                        valuesToAdd.clear();
                        isOptionValueToAdd = false;
                    }
                }

                if (Utils::isOption(s))
                {
                    isOptionValueToAdd = true;
                    optionToAdd = s;
                    optionToAdd.remove_prefix(2);
                }
            }

            if (isOptionValueToAdd)
                _options[optionToAdd] = valuesToAdd;
        }

    public:
        Args(int argc, char **argv): _argv(static_cast<std::size_t>(argc))
        {
            for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i)
            {
                _argv[i] = std::string_view(argv[i]);
                if (i != 0 && Utils::isFlag(_argv[i]))
                    addFlagsFromStringView(_argv[i]);
            }
            addOptions();
        }

        int                 argc() const { return static_cast<int>(_argv.size()); }
        const ArgsVector&   argv() const { return _argv; }
        const Flags&        getFlags() const { return _flags; }
        const Options&      getOPtions() const { return _options; }

        std::string_view operator[](std::size_t index)
        {
            return _argv[index];
        }

        std::optional<std::string_view> operator[](std::string_view name)
        {
            return getOptionValue(name);
        }

        bool valueExist(std::string_view value) const
        {
            return std::find(_argv.cbegin(), _argv.cend(), value) != _argv.cend() ? true : false;
        }

        bool flagExist(char name) const
        {
            return std::find(_flags.cbegin(), _flags.cend(), name) != _flags.cend() ? true : false;
        }

        // dp not put the -- at the beginning of the string
        bool optionExist(std::string_view name) const
        {
            return _options.find(name) != _options.cend() ? true : false;
        }

        // dp not put the -- at the beginning of the string
        std::optional<std::string_view> getOptionValue(std::string_view name)
        {
            std::optional<std::string_view> value;

            auto option_values = _options.find(name);
            if (option_values == _options.cend())
                return value;
            if (option_values->second.empty())
                return value;
            value = option_values->second.front();
            return value;
        }

        // dp not put the -- at the beginning of the string
        std::optional<std::vector<std::string_view>> getOptionValues(std::string_view name)
        {
            std::optional<std::vector<std::string_view>> values;

            auto option_values = _options.find(name);
            if (option_values == _options.cend())
                return values;
            return option_values->second;
        }


    private:
        ArgsVector  _argv;
        Flags       _flags;
        Options     _options;
};

}
