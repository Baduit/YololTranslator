#pragma once

#include <PhonemList.hpp>
#include <PhonemTranslation.hpp>

#ifdef STUB_GENERATED
	#include <generated/PhonemToStringGeneratedStub.hpp>
#else
	// TODO
#endif

namespace YololTranslator
{

class PhonemListToString
{
	public:
		constexpr PhonemListToString():
			_map(generated::load_phonem_to_string_map())
		{}

	std::string	operator()(const PhonemList& phonem_list)
	{
		return "bbb";
	}

	private:
		StaticMap<Phonem, PhonemTranslation, generated::PHONEM_TO_STRING_SIZE> _map;
};

} // namespace YololTranslator
