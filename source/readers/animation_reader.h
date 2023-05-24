#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/animation.h>

namespace glTF
{
	std::optional<std::vector<Animation>> read_animations(nlohmann::json root_object);
	Animation read_animation(nlohmann::json animation_object);
	AnimationChannel read_animation_channel(nlohmann::json animation_channel_object);
	AnimationSampler read_animation_sampler(nlohmann::json animation_sampler_object);
	AnimationTarget read_animation_target(nlohmann::json animation_target_object);
	InterpolationType string_to_interpolation_type(std::string interpolation_string);
}
