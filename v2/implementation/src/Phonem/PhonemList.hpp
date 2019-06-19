#pragma once

#include "Phonem.hpp"

class PhonemList
{
	public:
		PhonemList() = default;

		PhonemList(std::string_view filename);

		PhonemList(const PhonemList&) = delete;
		PhonemList& operator=(const PhonemList&) = delete;

		PhonemList(PhonemList&&) = default;
		PhonemList& operator=(PhonemList&&) = default;

		void	load_from_file(std::string_view filename);

		const std::vector<Phonem>&	get_phonems() const;

		const Phonem&	operator[] (std::string_view code) const;

	private:
		std::vector<Phonem>	_phonems;
};