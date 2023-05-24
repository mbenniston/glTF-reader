#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/material.h>

namespace glTF
{
	std::optional<std::vector<Material>> read_materials(nlohmann::json root_object);
	Material read_material(nlohmann::json material_object);

	MaterialPbrMetallicRoughness read_pbr_metallic_roughness(nlohmann::json pbr_metallic_roughness_object);
	MaterialNormalTextureInfo read_normal_texture_info(nlohmann::json normal_texture_info_object);
	MaterialOcculusionTextureInfo read_occulusion_texture_info(nlohmann::json occulusion_texture_info_object);
	TextureInfo read_texture_info(nlohmann::json texture_info_object);
	AlphaMode string_to_alpha_mode(std::string alpha_mode);
}
