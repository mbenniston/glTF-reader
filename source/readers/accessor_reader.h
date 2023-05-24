#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/accessor.h>

namespace glTF
{
	std::optional<std::vector<Accessor>> read_accessors(nlohmann::json root_object);
	Accessor read_accessor(nlohmann::json accessor_object);

	AccessorComponentType number_to_accessor_component_type(int component_type_number);
	AccessorElementsType string_to_accessor_elements_type(const std::string& elements_type_name);
	AccessorSparse read_accessor_sparse(nlohmann::json accessor_sparse);
	AccessorSparseIndices read_accessor_sparse_indices(nlohmann::json accessor_sparse_indices);
	AccessorSparseValues read_accessor_sparse_values(nlohmann::json accessor_sparse_values);
	AccessorSparseIndicesComponentType number_to_accessor_indices_component_type(int indices_type_number);
}