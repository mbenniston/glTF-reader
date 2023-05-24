#include "animation_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Animation>> read_animations(json root_object)
	{
		return json_try_get_vector_map(root_object, "animations", read_animation);
	}

	Animation read_animation(json animation_object)
	{
		Animation animation;
		animation.channels = json_require_vector_map<AnimationChannel>(animation_object, "channels", read_animation_channel);
		animation.samplers = json_require_vector_map<AnimationSampler>(animation_object, "samplers", read_animation_sampler);
		animation.name = json_try_get<std::string>(animation_object, "name");
		animation.extensions = json_try_dump(animation_object, "extensions");
		animation.extras = json_try_dump(animation_object, "extras");

		return animation;
	}

	AnimationChannel read_animation_channel(json animation_channel_object)
	{
		AnimationChannel channel;
		channel.sampler = json_require<int>(animation_channel_object, "sampler");
		channel.target = read_animation_target(json_require<json>(animation_channel_object, "target"));
		channel.extensions = json_try_dump(animation_channel_object, "extensions");
		channel.extras = json_try_dump(animation_channel_object, "extras");

		return channel;
	}
	
	AnimationSampler read_animation_sampler(json animation_sampler_object)
	{
		AnimationSampler sampler;
		sampler.input = json_require<int>(animation_sampler_object, "input");
		sampler.interpolation = optional_map<std::string, InterpolationType>(json_try_get<std::string>(animation_sampler_object, "interpolation"),  string_to_interpolation_type)
			.value_or(InterpolationType::Linear);
		sampler.output = json_require<int>(animation_sampler_object, "output");
		sampler.extensions = json_try_dump(animation_sampler_object, "extensions");
		sampler.extras = json_try_dump(animation_sampler_object, "extras");

		return sampler;
	}

	AnimationTarget read_animation_target(json animation_target_object)
	{
		AnimationTarget target;
		target.node = json_try_get<int>(animation_target_object, "node");
		target.path = json_require<std::string>(animation_target_object, "path");
		target.extensions = json_try_dump(animation_target_object, "extensions");
		target.extras = json_try_dump(animation_target_object, "extras");

		return target;
	}

	InterpolationType string_to_interpolation_type(std::string interpolation_string)
	{
		if (interpolation_string == "LINEAR")
		{
			return InterpolationType::Linear;
		}

		if (interpolation_string == "STEP")
		{
			return InterpolationType::Step;
		}

		if (interpolation_string == "CUBICSPLINE")
		{
			return InterpolationType::CubicSpline;
		}

		throw GLTFReadException("Invalid interpolation type in string: " + interpolation_string + ".");
	}
}