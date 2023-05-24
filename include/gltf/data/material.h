#pragma once
#include <array>
#include <string>
#include <optional>
#include "texture_info.h"

namespace glTF
{
	struct MaterialPbrMetallicRoughness
	{
		std::array<float, 4> baseColorFactor;
		std::optional<TextureInfo> baseColorTexture;
		float metallicFactor;
		float roughnessFactor;
		std::optional<TextureInfo> metallicRoughnessTexture;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct MaterialNormalTextureInfo
	{
		int index;
		int texCoord;
		float scale;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct MaterialOcculusionTextureInfo
	{
		int index;
		int texCoord;
		float strength;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	enum class AlphaMode
	{
		Opaque,
		Mask,
		Blend
	};

	struct Material
	{
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
		std::optional<MaterialPbrMetallicRoughness> pbrMetallicRoughness;
		std::optional<MaterialNormalTextureInfo> normalTexture;
		std::optional<MaterialOcculusionTextureInfo> occulusionTexture;
		std::optional<TextureInfo> emissiveTexture;
		std::array<float, 3> emissiveFactor;
		AlphaMode alphaMode;
		float alphaCutOff;
		bool doubleSided;
	};
}