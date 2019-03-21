#include <sstream>
#pragma once
/* A collection of utility functions */

std::string WideToNarrow(std::wstring sEntry) //By default boost filesystem uses wide characters, but rest of my code uses 8 bit ASCII
{
	std::ostringstream stm;
	for (auto It : sEntry)
	{
		stm << std::use_facet<std::ctype<wchar_t> >(std::locale()).narrow(It, '?');
	} return stm.str(); //convert to unicode string
}
