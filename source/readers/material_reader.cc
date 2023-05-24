#include "material_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Material>> read_materials(json root_object)
	{
		return json_try_get_vector_map(root_object, "materials", read_material);
	}

	Material read_material(json material_object)
	{
		Material material;

		material.name = json_try_get<std::string>(material_object, "name");
		material.extensions = json_try_dump(material_object, "extensions");
		material.extras = json_try_dump(material_object, "extras");
		material.pbrMetallicRoughness = optional_map(json_try_get<json>(material_object, "pbrMetallicRoughness"), read_pbr_metallic_roughness);
		material.normalTexture = optional_map(json_try_get<json>(material_object, "normalTexture"), read_normal_texture_info);
		material.occulusionTexture = optional_map(json_try_get<json>(material_object, "occulusionTexture"), read_occulusion_texture_info);
		material.emissiveTexture = optional_map(json_try_get<json>(material_object, "emissiveTexture"), read_texture_info);
		material.emissiveFactor = json_try_get_array<float, 3>(material_object, "emissiveFactor")
			.value_or(std::array<float, 3>{0.0f, 0.0f, 0.0f});
		material.alphaMode = optional_map(json_try_get<std::string>(material_object, "alphaMode"), string_to_alpha_mode).value_or(AlphaMode::Opaque);
		material.alphaCutOff = json_get_or_default<float>(material_object, "alphaCutOff", 0.5f);
		material.doubleSided = json_get_or_default<bool>(material_object, "doubleSided", false);

		return material;
	}

	MaterialPbrMetallicRoughness read_pbr_metallic_roughness(json pbr_metallic_roughness_object)
	{
		MaterialPbrMetallicRoughness pbrMetallicRoughness;
		pbrMetallicRoughness.baseColorFactor = json_try_get_array<float, 4>(pbr_metallic_roughness_object, "baseColorFactor")
			.value_or(std::array<float, 4>{1.0f, 1.0f, 1.0f, 1.0f});
		pbrMetallicRoughness.baseColorTexture = optional_map(json_try_get<json>(pbr_metallic_roughness_object, "baseColorTexture"), read_texture_info);
		pbrMetallicRoughness.metallicFactor = json_get_or_default<float>(pbr_metallic_roughness_object, "metallicFactor", 1.0f);
		pbrMetallicRoughness.roughnessFactor = json_get_or_default<float>(pbr_metallic_roughness_object, "roughnessFactor", 1.0f);
		pbrMetallicRoughness.metallicRoughnessTexture = optional_map(json_try_get<json>(pbr_metallic_roughness_object, "metallicRoughnessTexture"), read_texture_info);
		pbrMetallicRoughness.extensions = json_try_dump(pbr_metallic_roughness_object, "extensions");
		pbrMetallicRoughness.extras = json_try_dump(pbr_metallic_roughness_object, "extras");

		return pbrMetallicRoughness;
	}

	MaterialNormalTextureInfo read_normal_texture_info(json normal_texture_info_object)
	{
		MaterialNormalTextureInfo normalTextureInfo;
		normalTextureInfo.index = json_require<int>(normal_texture_info_object, "index");
		normalTextureInfo.texCoord = json_get_or_default<int>(normal_texture_info_object, "texCoord", 0);
		normalTextureInfo.scale = json_get_or_default<float>(normal_texture_info_object, "texCoord", 1);
		normalTextureInfo.extensions = json_try_dump(normal_texture_info_object, "extensions");
		normalTextureInfo.extras = json_try_dump(normal_texture_info_object, "extras");

		return normalTextureInfo;
	}

	MaterialOcculusionTextureInfo read_occulusion_texture_info(json occulusion_texture_info_object)
	{
		MaterialOcculusionTextureInfo occulusionTextureInfo;
		occulusionTextureInfo.index = json_require<int>(occulusion_texture_info_object, "index");
		occulusionTextureInfo.texCoord = json_get_or_default<int>(occulusion_texture_info_object, "texCoord", 0);
		occulusionTextureInfo.strength = json_get_or_default<float>(occulusion_texture_info_object, "strength", 1);
		occulusionTextureInfo.extensions = json_try_dump(occulusion_texture_info_object, "extensions");
		occulusionTextureInfo.extras = json_try_dump(occulusion_texture_info_object, "extras");

		return occulusionTextureInfo;
	}

	TextureInfo read_texture_info(json texture_info_object)
	{
		TextureInfo textureInfo;
		textureInfo.index = json_require<int>(texture_info_object, "index");
		textureInfo.texCoord = json_get_or_default<int>(texture_info_object, "texCoord", 0);
		textureInfo.extensions = json_try_dump(texture_info_object, "extensions");
		textureInfo.extras = json_try_dump(texture_info_object, "extras");

		return textureInfo;
	}

	AlphaMode string_to_alpha_mode(std::string alpha_mode)
	{
		if (alpha_mode == "OPAQUE")
		{
			return AlphaMode::Opaque;
		}

		if (alpha_mode == "MASK")
		{
			return AlphaMode::Mask;
		}

		if (alpha_mode == "BLEND")
		{
			return AlphaMode::Blend;
		}

		throw GLTFReadException("Invalid alpha mode in string: " + alpha_mode + ".");
	}
}
