
#include "declarations.hpp"
#include <string>
namespace banita
{
	std::vector<String> String_Utilities::string_splitter(const String & _toSplit, const char _delimitier)
	{
		std::vector<String> tempVector;

		String tempstring = _toSplit;

		String::size_type i = 0;
		String::size_type j = tempstring.find(_delimitier);

		if (j == String::npos)
		{
			tempVector.push_back(tempstring.substr(i, tempstring.length()));
			return tempVector;
		}
			
		
		while (j != String::npos)
		{
			tempVector.push_back(tempstring.substr(i, j - i));
			i = ++j;
			j = tempstring.find(_delimitier, j);

			if (j == String::npos)
				tempVector.push_back(tempstring.substr(i, tempstring.length()));
		}

	

		return tempVector;
	}

}