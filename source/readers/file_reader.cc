#include <gltf/file_reader.h>

#include <fstream>	
#include <string>
#include <sstream>
#include <array>

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
	static const std::uint32_t GLTF_MAGIC_VALUE = 0x46546C67;
	static const std::uint32_t JSON_TYPE_VALUE = 0x4E4F534A;
	static const std::uint32_t BIN_TYPE_VALUE = 0x004E4942;

	File read_from_stream(std::istream& stream)
	{
		glTF::File file;
	
		try
		{
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
		}
		catch (const json::exception& json_exception)
		{
			throw GLTFReadException(std::string("Failed to parse json: ") + json_exception.what());
		}

		return file;
	}

	static std::uint32_t read_uint32(std::istream& stream)
	{
        std::array<std::uint8_t, 4> buffer;
        std::uint32_t value = 0;

        stream.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    
        value |= std::uint32_t{buffer[0]};
        value |= std::uint32_t{buffer[1]} << 8;
        value |= std::uint32_t{buffer[2]} << 16;
        value |= std::uint32_t{buffer[3]} << 24;
        
		return value;
	}

	static File read_json_chunk(std::istream& stream, std::uint32_t length)
	{
		std::vector<char> data;
		data.resize(length);
		stream.read(data.data(), length);

		std::stringstream json_stream(std::string(data.begin(), data.end()));
		return read_from_stream(json_stream);
	}

	static BinaryBuffer read_binary_chunk(std::istream& stream, std::uint32_t length)
	{
		BinaryBuffer buffer;
		buffer.bytes.resize(length);
		stream.read(reinterpret_cast<char*>(buffer.bytes.data()), length);

		return buffer;
	}

	File read_from_stream_binary(std::istream& stream)
	{
		std::uint32_t magic = read_uint32(stream);
		if (magic != GLTF_MAGIC_VALUE)
		{
			throw GLTFReadException("Magic value doesn't match gltf file");
		}

		std::uint32_t version = read_uint32(stream);
		if (version != 2)
		{
			throw GLTFReadException("Only glTF version 2 is supported");
		}

		std::uint32_t length = read_uint32(stream);
		(void)length;

		std::optional<File> file;
		std::vector<BinaryBuffer> binary_buffers;

		while (stream)
		{
			// read chunk header
			std::uint32_t chunk_length = read_uint32(stream);
			std::uint32_t chunk_type = read_uint32(stream);

			// read chunk depending on type
			if (chunk_type == BIN_TYPE_VALUE)
			{
				binary_buffers.emplace_back(read_binary_chunk(stream, chunk_length));
			}
			else if (chunk_type == JSON_TYPE_VALUE && !file.has_value())
			{
				file = read_json_chunk(stream, chunk_length);
			}
			else
			{
				stream.seekg(chunk_length, std::ios::cur);
			}
		}

		if (!file.has_value())
		{
			throw GLTFReadException("No JSON chunks were read");
		}

		file->binaryBuffers = std::move(binary_buffers);

		return file.value();
	}

	static bool ends_with(const std::string& source, const std::string& postfix)
	{
		std::size_t postfix_size = postfix.size();
		std::size_t source_index_start = source.size() - postfix_size;

		if (source.size() < postfix_size)
		{
			return false;
		}

		for (std::size_t i = 0; i < postfix_size; i++)
		{
			std::size_t source_index = source_index_start + i;

			if (source.at(source_index) != postfix.at(i))
			{
				return false;
			}
		}

		return true;
	}

	File read_from_path_binary(const std::string& path)
	{
		std::fstream file_stream(path, std::ios::in | std::ios::binary);

		if (!file_stream)
		{
			throw GLTFReadException("File with path: " + path + " not found");
		}

		return read_from_stream_binary(file_stream);
	}

	File read_from_path_json(const std::string& path)
	{
		std::fstream file_stream(path);

		if (!file_stream)
		{
			throw GLTFReadException("File with path: " + path + " not found");
		}

		return read_from_stream(file_stream);
	}

	File read_from_path(const std::string& path)
	{
		if (ends_with(path, "glb"))
		{
			return read_from_path_binary(path);
		}

		return read_from_path_json(path);
	}
}

