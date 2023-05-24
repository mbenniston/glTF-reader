#pragma once
#include <istream>
#include "data/file.h"

namespace glTF
{
	File read_from_stream(std::istream& stream);
}