#pragma once
#include <optional>
#include <vector>
#include <string>

namespace glTF
{
	struct Scene
	{
		std::optional<std::string> name;
		std::vector<int> nodes;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}