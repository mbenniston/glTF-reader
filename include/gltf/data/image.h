#pragma once
#include <string>
#include <optional>

namespace glTF
{
	enum class MimeType
	{
		Jpeg,
		Png
	};

	struct Image
	{
		std::optional<std::string> uri;
		std::optional<MimeType> mimeType;
		std::optional<int> bufferView;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}