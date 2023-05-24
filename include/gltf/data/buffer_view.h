#pragma once
#include <string>
#include <optional>

namespace glTF
{
	enum class BufferViewTarget : int
	{
		ArrayBuffer = 34962,
		ElementArrayBuffer = 34963
	};

	struct BufferView
	{
		int buffer;
		int byteOffset;
		int byteLength;
		std::optional<int> byteStride;
		std::optional<BufferViewTarget> target;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}