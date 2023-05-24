#pragma once
#include <stdexcept>

namespace glTF
{
	class GLTFReadException : public std::runtime_error
	{
	public:
		GLTFReadException(const std::string& message) : std::runtime_error(message)
		{
		}
	};
}