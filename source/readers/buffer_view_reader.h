#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/buffer_view.h>

namespace glTF
{
	std::optional<std::vector<BufferView>> read_buffer_views(nlohmann::json root_object);
	BufferView read_buffer_view(nlohmann::json buffer_view_object);

	BufferViewTarget number_to_buffer_view_target(int bufferViewTargetNumber);
}
