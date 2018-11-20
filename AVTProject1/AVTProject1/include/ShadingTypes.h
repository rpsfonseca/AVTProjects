#pragma once

#include <string>

namespace AVTEngine
{
	class Texture;

	struct Uniform
	{
		std::string  name;
		int          size;
		unsigned int location;
	};

	struct UniformValueSampler
	{
		unsigned int unit;
		Texture     *texture;

		UniformValueSampler() {}
	};

	struct VertexAttribute
	{
		std::string  name;
		int          size;
		unsigned int location;
	};
}