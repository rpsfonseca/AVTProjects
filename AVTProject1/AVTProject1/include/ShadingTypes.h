#pragma once

#include <string>

namespace AVTEngine
{
	struct Uniform
	{
		std::string  name;
		int          size;
		unsigned int location;
	};
}