#include "buffer_view_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<BufferView>> read_buffer_views(json root_object)
	{
		return json_try_get_vector_map(root_object, "bufferViews", read_buffer_view);
	}

	BufferView read_buffer_view(json buffer_view_object)
	{
		BufferView bufferView;
		bufferView.buffer = json_require<int>(buffer_view_object, "buffer");
		bufferView.byteOffset = json_get_or_default<int>(buffer_view_object, "byteOffset", 0);
		bufferView.byteLength = json_require<int>(buffer_view_object, "byteLength");
		bufferView.byteStride = json_try_get<int>(buffer_view_object, "byteStride");
		bufferView.target = optional_map(json_try_get<int>(buffer_view_object, "target"), number_to_buffer_view_target);
		bufferView.name = json_try_get<std::string>(buffer_view_object, "name");
		bufferView.extensions = json_try_dump(buffer_view_object, "extensions");
		bufferView.extras = json_try_dump(buffer_view_object, "extras");

		return bufferView;
	}

	BufferViewTarget number_to_buffer_view_target(int bufferViewTargetNumber)
	{		
		switch (bufferViewTargetNumber)
		{
		case static_cast<int>(BufferViewTarget::ArrayBuffer):
			return BufferViewTarget::ArrayBuffer;
		case static_cast<int>(BufferViewTarget::ElementArrayBuffer):
			return BufferViewTarget::ElementArrayBuffer;
		}

		throw GLTFReadException("Invalid buffer view target in number: " + std::to_string(bufferViewTargetNumber) + ".");
	}
}