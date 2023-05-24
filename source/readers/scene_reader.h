#pragma once
#include <json_nowarn.hpp>
#include <gltf/data/scene.h>

namespace glTF
{
	std::optional<std::vector<Scene>> read_scenes(nlohmann::json root_object);
	Scene read_scene(nlohmann::json scene_object);

	std::optional<int> read_default_scene(nlohmann::json root_object);
}