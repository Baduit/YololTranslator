#pragma once

#include <array>
#include <string_view>

namespace YololTranslator
{

template <typename Value, std::size_t Size>
struct StaticMapSoA final
{
	// Instanciate it as an aggregate, even if it will be ugly the code instanciating it will be generated

	constexpr const Value*	operator[](std::string_view word) noexcept
	{
		std::size_t i = 0;
		for (auto key: _keys)
		{
			if (key == word)
				return &(_values[i]);
			++i;
		}
		return nullptr;
	}

	std::array<std::string_view, Size>		_keys;
	std::array<Value, Size> 				_values;
};

// SoA (struct of array) instead of AoS (array of struct) to improve the lookup search with better cache locality
// TODO: benchmark SoA against AoS to confirm the hypothesis
template <typename Value, std::size_t Size>
using StaticMap = StaticMapSoA<Value, Size>;

} // namespace YololTranslator
