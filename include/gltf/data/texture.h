#pragma once
#include <optional>
#include <string>

namespace glTF
{
	struct Texture
	{
		std::optional<int> sampler;
		std::optional<int> source;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}