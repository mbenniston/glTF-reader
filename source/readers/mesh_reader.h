#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/mesh.h>

namespace glTF
{
	std::optional<std::vector<Mesh>> read_meshes(nlohmann::json root_object);
	Mesh read_mesh(nlohmann::json mesh_object);

	Primitive read_primitive(nlohmann::json primitive_object);
	TopologyType number_to_toplogy_type(int toplogy_type);
}
