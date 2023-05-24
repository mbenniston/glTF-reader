#pragma once
#include <optional>
#include <string>
#include <vector>

namespace glTF
{
	struct AnimationTarget
	{
		std::optional<int> node;
		std::string path;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	enum class InterpolationType
	{
		Linear,
		Step,
		CubicSpline,
	};

	struct AnimationSampler
	{
		int input;
		InterpolationType interpolation;
		int output;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct AnimationChannel
	{
		int sampler;
		AnimationTarget target;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct Animation
	{
		std::vector<AnimationChannel> channels;
		std::vector<AnimationSampler> samplers;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}