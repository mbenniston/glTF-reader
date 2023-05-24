#include "buffer_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Buffer>> read_buffers(json root_object)
	{
		return json_try_get_vector_map(root_object, "buffers", read_buffer);
	}

	Buffer read_buffer(json buffer_object)
	{
		Buffer buffer;
		buffer.uri = json_try_get<std::string>(buffer_object, "uri");
		buffer.byteLength = json_require<int>(buffer_object, "byteLength");
		buffer.name = json_try_get<std::string>(buffer_object, "name");
		buffer.extensions = json_try_dump(buffer_object, "extensions");
		buffer.extras = json_try_dump(buffer_object, "extras");

		return buffer;
	}
}