#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>
#include <cstring>

#include "StringFunction.hpp"

using Dictionnary = std::map<std::string, std::string>;

class Translator
{
public:
    void fillFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            std::stringstream ss(line);
            std::string key;
            std::string value;

            ss >> key;
            ss >> value;
            fill(key, value);
        }
    }

    void fill(const std::string& s, const std::string ss)
    {
        auto i = _dico.find(s);
        if (i != _dico.end())
            std::clog << "Warning:" << s << " is already in the directionay with the value: " << i->second << " override with : " << ss << "." << std::endl;
        _dico[s] = ss;
    }

    virtual std::string operator()(const std::string& word) = 0;
protected:
    Dictionnary _dico;
};

using TranslatorPtr = std::unique_ptr<Translator>;

class WordTranslator: public Translator
{
public:
    WordTranslator() = default;
    WordTranslator(const std::string& filename)
    { fillFromFile(filename); }

    std::string operator()(const std::string& word) override
    {
        auto i = _dico.find(word);
        if (i != _dico.end())
            return i->second;
        else
            return word;
    }
};

class CharacteresTranslator: public Translator
{
public:
    CharacteresTranslator() = default;
    CharacteresTranslator(const std::string& filename)
    { fillFromFile(filename); }

    std::string operator()(const std::string& word) override
    {
        std::string result = word;

        for (auto& i: _dico)
            StringFunction::replaceAll(result, i.first, i.second);

        return result;
    }
};

class TerminaisonTranslator: public Translator
{
public:
    TerminaisonTranslator() = default;
    TerminaisonTranslator(const std::string& filename)
    { fillFromFile(filename); }

    std::string operator()(const std::string& word) override
    {
        std::string result = word;

        for (auto& i: _dico)
            if (StringFunction::replaceEnd(result, i.first, i.second))
                break;

        return result;
    }
};