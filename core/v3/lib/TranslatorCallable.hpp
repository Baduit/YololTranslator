#pragma once

#include <functional>
#include <string_view>
#include <memory>

namespace YololTranslator
{

//using TranslatorCallable = std::function<std::string_view()>;

struct TranslatorCallable
{
	struct IProxy
	{
		// Not pure virtual because of fucking gcc false warning saying that it is used but never defined
		constexpr virtual std::string_view operator()() const { return ""; };
	};

	template <typename T>
	struct Proxy: public IProxy
	{
		constexpr Proxy(T&& t):
			value(std::move(t))
		{}

		constexpr virtual std::string_view operator()() const override
		{
			return value();
		}

		T value;
	};

	template <typename T>
	constexpr TranslatorCallable(T&& t)
	{
		impl = new Proxy<T>(std::forward<T>(t));
	}

	TranslatorCallable(const TranslatorCallable&) = delete;
	TranslatorCallable& operator=(const TranslatorCallable&) = delete;
	TranslatorCallable(TranslatorCallable&&) = default;
	TranslatorCallable& operator=(TranslatorCallable&&) = default;

	constexpr virtual std::string_view operator()() const
	{
		return (*impl)();
	}

	IProxy* impl;
};

} // namespace YololTranslator
