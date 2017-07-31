#pragma once

#include <vector>

#include "Translator.hpp"

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