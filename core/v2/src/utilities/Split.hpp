#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <optional>
#include <iterator>
#include <initializer_list>

struct Token
{
	enum class Type
	{
		DELIMiTER,
		WORD
	}; 

	Token(std::string_view str, Type t): value(str), type(t) {}
	Token(const Token&) = default;
	Token& operator=(const Token&) = default;
	Token(Token&&) = default;
	Token& operator=(Token&&) = default;

	std::string_view	operator*() const { return value; };

	std::string_view 	value;
	Type				type;
};

namespace Details
{

using namespace std::string_view_literals;

inline bool	start_with(std::string_view str, std::string_view substr)
{
	if (str.size() < substr.size())
		return false;
	
	for (std::size_t i = 0; i < substr.size(); ++i)
	{
		if (str[i] != substr[i])
			return false;
	}

	return true;
}

template <template <typename> typename InputContainer = std::vector, typename StrView = std::string_view>
std::optional<std::string_view>	get_delim(std::string_view str, const InputContainer<StrView>& delims)
{
	for (std::string_view d: delims)
	{
		if (start_with(str, d))
			return d;
	}

	return {};
}

}

template <template <typename> typename InputContainer = std::vector, typename StrView = std::string_view, template <typename> typename OutputContainer = std::vector>
OutputContainer<std::string_view>	split(std::string_view str, InputContainer<StrView> delims)
{
	if (str.empty())
		return {};

	std::sort(delims.begin(), delims.end(), [](std::string_view a, std::string_view b) { return a > b; });

	OutputContainer<std::string_view> result;
	auto inserter = std::back_inserter(result);

	std::size_t i = 0;
	std::size_t word_begin = 0;
	while (i < str.size())
	{
		auto d = Details::get_delim<InputContainer, StrView>(str.substr(i), delims);
		if (d)
		{
			auto word = str.substr(word_begin, i - word_begin);
			if (!word.empty())
				inserter = word;
			i += d->size();
			word_begin = i;
		}
		else
		{
			++i;
		}
	}

	if (word_begin != i)
		inserter = str.substr(word_begin, i - word_begin);
	
	return result;
}


template <template <typename> typename InputContainer = std::vector, typename StrView = std::string_view, template <typename> typename OutputContainer = std::vector>
OutputContainer<Token>	tokenize(std::string_view str, InputContainer<StrView> delims)
{
	if (str.empty())
		return {};
	
	std::sort(delims.begin(), delims.end(), [](std::string_view a, std::string_view b) { return a > b; });

	OutputContainer<Token> result;
	auto inserter = std::back_inserter(result);

	std::size_t i = 0;
	std::size_t word_begin = 0;
	while (i < str.size())
	{
		auto d = Details::get_delim<InputContainer, StrView>(str.substr(i), delims);
		if (d)
		{
			auto word = str.substr(word_begin, i - word_begin);
			if (!word.empty())
				inserter = Token(word,  Token::Type::WORD);
			i += d->size();
			word_begin = i;
			inserter = Token(*d, Token::Type::DELIMiTER);
		}
		else
		{
			++i;
		}
	}

	if (word_begin != i)
		inserter = Token(str.substr(word_begin, i - word_begin), Token::Type::WORD);
	
	return result;
}
