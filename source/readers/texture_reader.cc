#include "texture_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Texture>> read_textures(json root_object)
	{
		return json_try_get_vector_map(root_object, "textures", read_texture);
	}

	Texture read_texture(json texture_object)
	{
		Texture texture;
		texture.sampler = json_try_get<int>(texture_object, "sampler");
		texture.source = json_try_get<int>(texture_object, "source");
		texture.name = json_try_get<std::string>(texture_object, "name");
		texture.extensions = json_try_dump(texture_object, "extensions");
		texture.extras = json_try_dump(texture_object, "extras");

		return texture;
	}
}