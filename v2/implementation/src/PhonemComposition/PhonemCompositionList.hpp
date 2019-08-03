#pragma once

#include <vector>

#include "PhonemComposition.hpp"

namespace details
{
struct ReverseLess
{
	template <typename T>
	bool operator()(const T& a, const T& b)
	{
		return !(a < b);
	}
};

}

class PhonemCompositionList
{
	public:
		PhonemCompositionList(std::string_view filename);

		PhonemCompositionList(const PhonemCompositionList&) = delete;
		PhonemCompositionList& operator=(const PhonemCompositionList&) = delete;

		PhonemCompositionList(PhonemCompositionList&&) = default;
		PhonemCompositionList& operator=(PhonemCompositionList&&) = default;

		void	load_from_file(std::string_view filename);

		const std::vector<PhonemComposition>&	get_phonem_compositions() const;

		// Return a pointer because optional on reference need a lot of boiler plate
		// And i prefer to keep exception for exceptional behavior, not possible normal behavior
		template <typename It>
		const PhonemComposition*	operator()(It actual, It end) const
		{
			for (const auto& pc: _phonem_compositions)
			{
				auto it_pc = pc.get_phonems().cbegin();
				auto it_word = actual;
				while (it_pc != pc.get_phonems().cend() && it_word != end)
				{
					if (it_word->get_code() != *it_pc)
						break;

					++it_pc;
					++it_word;
				}
		
				if (it_pc == pc.get_phonems().cend())
					return &pc;
			}
			return nullptr;
		}

	private:
		std::vector<PhonemComposition>	_phonem_compositions;
};