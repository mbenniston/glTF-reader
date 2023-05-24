#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/asset.h>

namespace glTF
{
	Asset read_asset(nlohmann::json file_object);
}
