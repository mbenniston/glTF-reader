#pragma once
#include <optional>
#include <string>

namespace glTF
{
	struct Buffer
	{
		std::optional<std::string> uri;
		int byteLength;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}