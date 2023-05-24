#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/image.h>

namespace glTF
{
	std::optional<std::vector<Image>> read_images(nlohmann::json root_object);
	Image read_image(nlohmann::json image_object);

	MimeType string_to_mime_type(std::string mimeTypeName);
}
