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

using Dictionnary = std::map<std::string, std::string>;

// string functions
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

void replaceEnd(std::string &s, const std::string &search, const std::string &replace)
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
            break;
        }
    }
}

void toLower(std::string &s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](char c){ return std::tolower(c); });
}

// translators
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

class SoundTranslator: public Translator
{
public:
    SoundTranslator() = default;
    SoundTranslator(const std::string& filename)
    { fillFromFile(filename); }

    std::string operator()(const std::string& word) override
    {
        std::string result = word;

        for (auto& i: _dico)
            replaceAll(result, i.first, i.second);

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
            replaceEnd(result, i.first, i.second);

        return result;
    }
};



int main(int argc, char **argv)
{
    std::string dirPath = "dico/";

    std::vector<TranslatorPtr> translators;
    translators.push_back(std::make_unique<WordTranslator>(dirPath + "word_dico.txt"));
    translators.push_back(std::make_unique<SoundTranslator>(dirPath + "sound_dico.txt"));
    translators.push_back(std::make_unique<TerminaisonTranslator>(dirPath + "terminaison_dico.txt"));

    for (int i = 1; i < argc; ++i)
    {
        std::string word = argv[i];
        toLower(word);
        for (auto& i: translators)
            word = (*i)(word);
        std::cout << word << " ";
    }
    std::cout << std::endl;
}