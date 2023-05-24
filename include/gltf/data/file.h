#pragma once
#include <optional>
#include <string>
#include <vector>

#include "asset.h"
#include "buffer.h"
#include "buffer_view.h"
#include "accessor.h"
#include "mesh.h"
#include "node.h"
#include "scene.h"
#include "sampler.h"
#include "texture.h"
#include "image.h"
#include "material.h"
#include "animation.h"
#include "camera.h"
#include "skin.h"

namespace glTF
{
	struct File
	{
		std::optional<std::vector<std::string>> extensionsUsed;
		std::optional<std::vector<std::string>> extensionsRequired;
		std::optional<std::vector<Accessor>> accessors;
		std::optional<std::vector<Animation>> animations;
		Asset asset;
		std::optional<std::vector<Buffer>> buffers;
		std::optional<std::vector<BufferView>> bufferViews;
		std::optional<std::vector<Camera>> cameras;
		std::optional<std::vector<Image>> images;
		std::optional<std::vector<Material>> materials;
		std::optional<std::vector<Mesh>> meshes;
		std::optional<std::vector<Node>> nodes;
		std::optional<std::vector<Sampler>> samplers;
		std::optional<int> scene;
		std::optional<std::vector<Scene>> scenes;
		std::optional<std::vector<Skin>> skins;
		std::optional<std::vector<Texture>> textures;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}