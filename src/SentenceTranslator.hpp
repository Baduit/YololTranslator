#pragma once

#include "TranslatorManager.hpp"

class SentenceTranslator
{
public:
    SentenceTranslator(const std::string& wordDicoPath, const std::string& sentenceDicoPath) :
        _wordTranslators(wordDicoPath), _sentenceTranslators(sentenceDicoPath)
    {}

    std::string translate(const std::string& str)
    {
        std::string sentence = sentenceTranslating(str);
        return wordTranslating(sentence);
    }

protected:
    std::string sentenceTranslating(const std::string& str)
    {
        std::string sentence = str;
        StringFunction::toLower(sentence);
        for (auto& i: _sentenceTranslators)
            sentence = (i)(sentence);
        return sentence;
    }

    std::string wordTranslating(const std::string& str)
    {
        std::stringstream result;
        
        std::string word;
        std::stringstream sentenceParser(str);
        while (sentenceParser >> word)
        {
            for (auto& i: _wordTranslators)
                word = (i)(word);
            result << word << " ";
        }
        return result.str();
    }
protected:
    TranslatorManager _wordTranslators;
    TranslatorManager _sentenceTranslators;
};

class GoodToBad: public SentenceTranslator
{
public:
    GoodToBad(const std::string& dico_dir) : SentenceTranslator(dico_dir, dico_dir)
    {
        // several words filters
        _sentenceTranslators.addTranslator<CharacteresTranslator>("punctuation");
        _sentenceTranslators.addTranslator<CharacteresTranslator>("special_char");

        // word by word filters
        _wordTranslators.addTranslator<WordTranslator>("word");
        _wordTranslators.addTranslator<CharacteresTranslator>("sound");
        _wordTranslators.addTranslator<TerminaisonTranslator>("terminaison");
        _wordTranslators.addTranslator<CharacteresTranslator>("accent");
        _wordTranslators.addTranslator<CharacteresTranslator>("double_letter");
    }
};