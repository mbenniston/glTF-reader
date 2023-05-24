#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/buffer.h>

namespace glTF
{
	std::optional<std::vector<Buffer>> read_buffers(nlohmann::json root_object);
	Buffer read_buffer(nlohmann::json buffer_object);
}
