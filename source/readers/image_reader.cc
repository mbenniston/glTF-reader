#include "image_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Image>> read_images(json root_object)
	{
		return json_try_get_vector_map(root_object, "images", read_image);
	}

	Image read_image(json image_object)
	{
		Image image;
		image.uri = json_try_get<std::string>(image_object, "uri");
		image.name = json_try_get<std::string>(image_object, "name");
		image.mimeType = optional_map(json_try_get<std::string>(image_object, "mimeType"), string_to_mime_type);
		image.bufferView = json_try_get<int>(image_object, "bufferView");
		image.extensions = json_try_dump(image_object, "extensions");
		image.extras = json_try_dump(image_object, "extras");

		if (image.uri.has_value() && image.bufferView.has_value())
		{
			throw GLTFReadException("Either buffer view or uri can be specified not both.");
		}

		if (image.bufferView.has_value() && !image.mimeType.has_value())
		{
			throw GLTFReadException("If buffer view is specified so should a mime type.");
		}

		return image;
	}

	MimeType string_to_mime_type(std::string mime_type_name)
	{
		if (mime_type_name == "image/jpeg")
		{
			return MimeType::Jpeg;
		}

		if (mime_type_name == "image/png")
		{
			return MimeType::Png;
		}

		throw GLTFReadException("Invalid mime type in string: " + mime_type_name + ".");
	}
}
