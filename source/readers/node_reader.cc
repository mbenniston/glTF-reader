#include "node_reader.h"
#include "../json_utils.h"

namespace glTF
{
	static constexpr std::array<float, 16> IDENTITY_MATRIX = std::array<float, 16>{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	static constexpr std::array<float, 4> IDENTITY_ROTATION = std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f};
	static constexpr std::array<float, 3> IDENTITY_SCALE = std::array<float, 3>{1.0f,1.0f, 1.0f};
	static constexpr std::array<float, 3> IDENTITY_TRANSLATION = std::array<float, 3>{0.0f, 0.0f, 0.0f};

	std::optional<std::vector<Node>> read_nodes(json root_object)
	{
		return json_try_get_vector_map(root_object, "nodes", read_node);
	}

	Node read_node(json node_object)
	{
		Node node;
		node.camera = json_try_get<int>(node_object, "camera");
		node.children = json_try_get_vector<int>(node_object, "children");
		node.skin = json_try_get<int>(node_object, "skin");
		node.matrix = json_try_get_array<float, 16>(node_object, "matrix").value_or(IDENTITY_MATRIX);
		node.mesh = json_try_get<int>(node_object, "mesh");
		node.rotation = json_try_get_array<float, 4>(node_object, "rotation").value_or(IDENTITY_ROTATION);
		node.scale = json_try_get_array<float, 3>(node_object, "scale").value_or(IDENTITY_SCALE);
		node.translation = json_try_get_array<float, 3>(node_object, "translation").value_or(IDENTITY_TRANSLATION);
		node.weights = json_try_get_vector<float>(node_object, "weights");
		node.name = json_try_get<std::string>(node_object, "name");
		node.extensions = json_try_dump(node_object, "extensions");
		node.extras = json_try_dump(node_object, "extras");

		return node;
	}
}
