#pragma once
#include <json_nowarn.hpp>
#include <gltf/data/texture.h>

namespace glTF
{
	std::optional<std::vector<Texture>> read_textures(nlohmann::json root_object);
	Texture read_texture(nlohmann::json texture_object);
}