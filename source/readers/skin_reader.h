#pragma once
#include <json_nowarn.hpp>
#include <gltf/data/skin.h>

namespace glTF
{
	std::optional<std::vector<Skin>> read_skins(nlohmann::json root_object);
	Skin read_skin(nlohmann::json skin_object);
}