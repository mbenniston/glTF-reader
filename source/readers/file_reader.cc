#include <gltf/file_reader.h>

#include <iostream>	
#include <string>

#include "../json_utils.h"

#include "asset_reader.h"
#include "accessor_reader.h"
#include "buffer_reader.h"
#include "buffer_view_reader.h"
#include "image_reader.h"
#include "material_reader.h"
#include "mesh_reader.h"
#include "node_reader.h"
#include "sampler_reader.h"
#include "scene_reader.h"
#include "texture_reader.h"
#include "animation_reader.h"
#include "skin_reader.h"
#include "camera_reader.h"

namespace glTF
{
	File read_from_stream(std::istream& stream)
	{
		glTF::File file;
		json root_object = json::parse(stream);

		if (root_object.contains("extensionsUsed"))
		{
			file.extensionsUsed = json_try_get_vector<std::string>(root_object, "extensionsUsed");
		}

		if (root_object.contains("extensionsRequired"))
		{
			file.extensionsRequired = json_try_get_vector<std::string>(root_object, "extensionsRequired");
		}

		file.accessors = read_accessors(root_object);
		file.animations = read_animations(root_object);
		file.asset = read_asset(root_object);
		file.buffers = read_buffers(root_object);
		file.bufferViews = read_buffer_views(root_object);
		file.cameras = read_cameras(root_object);
		file.images = read_images(root_object);
		file.materials = read_materials(root_object);
		file.meshes = read_meshes(root_object);
		file.nodes = read_nodes(root_object);
		file.samplers = read_samplers(root_object);
		file.textures = read_textures(root_object);
		file.scene = read_default_scene(root_object);
		file.scenes = read_scenes(root_object);
		file.skins = read_skins(root_object);
		file.extensions = json_try_dump(root_object, "extensions");
		file.extras = json_try_dump(root_object, "extras");

		return file;
	}
}

