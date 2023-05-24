#pragma once
#include <optional>
#include <vector>
#include <string>

namespace glTF
{
	struct Skin
	{
		std::optional<int> inverseBindMatrices;
		std::optional<int> skeleton;
		std::vector<int> joints;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}