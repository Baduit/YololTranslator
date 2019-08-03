#pragma once

#include <set>

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

		const std::vector<PhonemComposition>&	get_PhonemCompositions() const;

		template <typename It>
		const PhonemComposition&	operator()(It actual, It end) const;

	private:
		std::set<PhonemComposition, details::ReverseLess>	_PhonemCompositions;
};