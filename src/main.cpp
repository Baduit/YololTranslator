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
            StringFunction::replaceEnd(result, i.first, i.second);

        return result;
    }
};

class AccentTranslator: public Translator
{
public:
    AccentTranslator() = default;
    AccentTranslator(const std::string& filename)
    { fillFromFile(filename); }

    std::string operator()(const std::string& word) override
    {
        std::string result = word;

        for (auto& i: _dico)
            StringFunction::replaceAll(result, i.first, i.second);

        return result;
    }
};

class TranslatorManager
{
public:
    TranslatorManager() = default;
    TranslatorManager(const std::string& dirPath) : _dirPath(dirPath)
    {}

    template <typename TranslatorType>
    void addTranslator(const std::string& name)
    { _translators.push_back(std::make_unique<TranslatorType>(_dirPath + name + ".dico")); }

    const std::string& getDirPath() const
    { return _dirPath; }

    void setDirPath(const std::string& dirPath)
    { _dirPath = dirPath; }

    // for iterating over the translators
    auto begin()
    { return _translators.begin(); }

    auto cbegin() const
    { return _translators.cbegin(); }

    auto end()
    { return _translators.end(); }

    auto cend() const
    { return _translators.cend(); }

private:
    std::string                 _dirPath = "dico/";
    std::vector<TranslatorPtr>  _translators;
};

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        std::cout << "Mettez en argument la phrase à traduire." << std::endl;
        return 1;
    }

    TranslatorManager translators;
    translators.addTranslator<WordTranslator>("word");
    translators.addTranslator<SoundTranslator>("sound");
    translators.addTranslator<TerminaisonTranslator>("terminaison");
    translators.addTranslator<AccentTranslator>("accent");

    std::string word;
    std::stringstream sentenceParser(argv[1]);

    while (sentenceParser >> word)
    {
        StringFunction::toLower(word);
        for (auto& i: translators)
            word = (*i)(word);
        std::cout << word << " ";
    }
    std::cout << std::endl;
}