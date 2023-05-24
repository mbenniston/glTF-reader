#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/node.h>

namespace glTF
{
	std::optional<std::vector<Node>> read_nodes(nlohmann::json root_object);
	Node read_node(nlohmann::json node_object);
}
