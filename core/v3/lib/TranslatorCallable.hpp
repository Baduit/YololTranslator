#pragma once

#include <functional>
#include <string_view>
#include <memory>

namespace YololTranslator
{

// TODO : limit the number of allocation by allocating only a few times

struct TranslatorCallable
{
	struct IProxy
	{
		// Not pure virtual because of fucking gcc false warning saying that it is used but never defined
		virtual std::string_view operator()() const { return ""; };
		virtual ~IProxy() = default;
	};

	template <typename T>
	struct Proxy: public IProxy
	{
		constexpr Proxy(T&& t):
			value(std::move(t))
		{}

		virtual std::string_view operator()() const override
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

	// Can't do it automatically in the dtor or it will be a non trivial dtor and can't put it in the map
	void delete_memory()
	{
		if (impl)
			delete impl;
	}

	virtual std::string_view operator()() const
	{
		return (*impl)();
	}

	IProxy* impl;
};

} // namespace YololTranslator
