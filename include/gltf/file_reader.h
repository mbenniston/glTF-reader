#pragma once
#include <istream>
#include "data/file.h"

namespace glTF
{
	File read_from_stream(std::istream& stream);
	File read_from_stream_binary(std::istream& stream);

	File read_from_path(const std::string& path);
	File read_from_path_json(const std::string& path);
	File read_from_path_binary(const std::string& path);
}