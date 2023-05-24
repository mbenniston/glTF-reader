#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/sampler.h>

namespace glTF
{
	std::optional<std::vector<Sampler>> read_samplers(nlohmann::json root_object);
	Sampler read_sampler(nlohmann::json sampler_object);

	MinFilter number_to_min_filter(int min_filter);
	MagFilter number_to_mag_filter(int mag_filter);
	Wrap number_to_wrap(int wrap);
}
