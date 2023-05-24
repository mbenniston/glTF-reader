#pragma once
#include <optional>
#include <string>

namespace glTF
{
	struct Asset
	{
		std::optional<std::string> copyright;
		std::optional<std::string> generator;
		std::string version;
		std::optional<std::string> minVersion;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}