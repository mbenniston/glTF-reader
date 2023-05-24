#pragma once
#include <optional>
#include <string>

namespace glTF
{
	struct TextureInfo
	{
		int index;
		int texCoord;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}