#include "scene_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Scene>> read_scenes(json root_object)
	{
		return json_try_get_vector_map(root_object, "scenes", read_scene);
	}

	Scene read_scene(json scene_object)
	{
		Scene scene;
		scene.nodes = json_require_vector<int>(scene_object, "nodes");
		scene.name = json_try_get<std::string>(scene_object, "name");
		scene.extensions = json_try_dump(scene_object, "extensions");
		scene.extras = json_try_dump(scene_object, "extras");

		return scene;
	}

	std::optional<int> read_default_scene(json root_object)
	{
		return json_try_get<int>(root_object, "scene");
	}
}
