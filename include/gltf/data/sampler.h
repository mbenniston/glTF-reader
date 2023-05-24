#pragma once
#include <optional>
#include <string>

namespace glTF
{
	enum class MagFilter : int
	{
		Nearest = 9728,
		Linear = 9729
	};

	enum class MinFilter : int
	{
		Nearest = 9728,
		Linear = 9729,
		NearestMipmapNearest = 9984,
		LinearMipmapNearest = 9985,
		NearestMipmapLinear = 9986,
		LinearMipmapLinear = 9987
	};

	enum class Wrap : int
	{
		ClampToEdge = 33071,
		MirroredRepeat = 33648,
		Repeat = 10497
	};

	struct Sampler
	{
		std::optional<MagFilter> magFilter;
		std::optional<MinFilter> minFilter;
		Wrap wrapS = Wrap::Repeat;
		Wrap wrapT = Wrap::Repeat;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}