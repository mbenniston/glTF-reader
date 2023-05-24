#include "accessor_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Accessor>> read_accessors(json root_object)
	{
		return json_try_get_vector_map(root_object, "accessors", read_accessor);
	}

	Accessor read_accessor(json accessor_object)
	{
		Accessor accessor;

		accessor.bufferView = json_require<int>(accessor_object, "bufferView");
		accessor.byteOffset = json_get_or_default<int>(accessor_object, "byteOffset", 0);
		accessor.componentType = number_to_accessor_component_type(json_require<int>(accessor_object, "componentType"));
		accessor.normalized = json_get_or_default<bool>(accessor_object, "normalized", false);
		accessor.count = json_require<int>(accessor_object, "count");
		accessor.type = string_to_accessor_elements_type(json_require<std::string>(accessor_object, "type"));
		accessor.sparse = optional_map(json_try_get<json>(accessor_object, "sparse"), read_accessor_sparse);
		accessor.max = json_try_get_vector<float>(accessor_object, "max");
		accessor.min = json_try_get_vector<float>(accessor_object, "min");
		accessor.name = json_try_get<std::string>(accessor_object, "name");
		accessor.extensions = json_try_dump(accessor_object, "extensions");
		accessor.extras = json_try_dump(accessor_object, "extras");

		return accessor;
	}

	AccessorComponentType number_to_accessor_component_type(int component_type_number)
	{
		switch (component_type_number)
		{
			case static_cast<int>(AccessorComponentType::Byte):
				return AccessorComponentType::Byte;
			case static_cast<int>(AccessorComponentType::UnsignedByte):
				return AccessorComponentType::UnsignedByte;
			case static_cast<int>(AccessorComponentType::Short):
				return AccessorComponentType::Short;
			case static_cast<int>(AccessorComponentType::UnsignedShort):
				return AccessorComponentType::UnsignedShort;
			case static_cast<int>(AccessorComponentType::UnsignedInt):
				return AccessorComponentType::UnsignedInt;
			case static_cast<int>(AccessorComponentType::Float):
				return AccessorComponentType::Float;
		}

		throw GLTFReadException("Invalid accessor component type with number " + std::to_string(component_type_number) + ".");
	}

	AccessorElementsType string_to_accessor_elements_type(const std::string& elements_type_name)
	{
		if (elements_type_name == "SCALAR")
		{
			return AccessorElementsType::Scalar;
		}

		if (elements_type_name == "VEC2")
		{
			return AccessorElementsType::Vector2;
		}

		if (elements_type_name == "VEC3")
		{
			return AccessorElementsType::Vector3;
		}

		if (elements_type_name == "VEC4")
		{
			return AccessorElementsType::Vector4;
		}

		if (elements_type_name == "MAT2")
		{
			return AccessorElementsType::Matrix2;
		}

		if (elements_type_name == "MAT3")
		{
			return AccessorElementsType::Matrix3;
		}

		if (elements_type_name == "MAT4")
		{
			return AccessorElementsType::Matrix4;
		}

		throw GLTFReadException("Could not parse accessor elements type with string: " + elements_type_name + ".");
	}

	AccessorSparse read_accessor_sparse(nlohmann::json accessor_sparse)
	{
		AccessorSparse sparse;
		sparse.count = json_require<int>(accessor_sparse, "count");
		sparse.indices = read_accessor_sparse_indices(json_require<json>(accessor_sparse, "indices"));
		sparse.values = read_accessor_sparse_values(json_require<json>(accessor_sparse, "values"));
		sparse.extensions = json_try_dump(accessor_sparse, "extensions");
		sparse.extras = json_try_dump(accessor_sparse, "extras");

		return sparse;
	}

	AccessorSparseIndices read_accessor_sparse_indices(nlohmann::json accessor_sparse_indices)
	{
		AccessorSparseIndices indices;
		indices.bufferView = json_require<int>(accessor_sparse_indices, "bufferView");
		indices.byteOffset = json_get_or_default<int>(accessor_sparse_indices, "byteOffset", 0);
		indices.componentType = number_to_accessor_indices_component_type(json_require<int>(accessor_sparse_indices, "componentType"));
		indices.extensions = json_try_dump(accessor_sparse_indices, "extensions");
		indices.extras = json_try_dump(accessor_sparse_indices, "extras");
		return indices;
	}

	AccessorSparseValues read_accessor_sparse_values(nlohmann::json accessor_sparse_values)
	{
		AccessorSparseValues values;
		values.bufferView = json_require<int>(accessor_sparse_values, "bufferView");
		values.byteOffset = json_get_or_default<int>(accessor_sparse_values, "byteOffset", 0);
		values.extensions = json_try_dump(accessor_sparse_values, "extensions");
		values.extras = json_try_dump(accessor_sparse_values, "extras");
		return values;
	}

	AccessorSparseIndicesComponentType number_to_accessor_indices_component_type(int indices_type_number)
	{
		switch (indices_type_number)
		{

		case static_cast<int>(AccessorSparseIndicesComponentType::UnsignedByte):
			return AccessorSparseIndicesComponentType::UnsignedByte;
		case static_cast<int>(AccessorSparseIndicesComponentType::UnsignedShort):
			return AccessorSparseIndicesComponentType::UnsignedShort;
		case static_cast<int>(AccessorSparseIndicesComponentType::UnsignedInt):
			return AccessorSparseIndicesComponentType::UnsignedInt;
		}

		throw GLTFReadException("Invalid accessor indices component type with number: " + std::to_string(indices_type_number) + ".");
	}
}
