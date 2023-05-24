#include "sampler_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Sampler>> read_samplers(json root_object)
	{
		return json_try_get_vector_map(root_object, "samplers", read_sampler);
	}

	Sampler read_sampler(json sampler_object)
	{
		Sampler sampler;
		sampler.minFilter = optional_map(json_try_get<int>(sampler_object, "minFilter"), number_to_min_filter);
		sampler.magFilter = optional_map(json_try_get<int>(sampler_object, "magFilter"), number_to_mag_filter);
		sampler.wrapS = optional_map(json_try_get<int>(sampler_object, "wrapS"), number_to_wrap).value_or(Wrap::Repeat);
		sampler.wrapT = optional_map(json_try_get<int>(sampler_object, "wrapT"), number_to_wrap).value_or(Wrap::Repeat);
		sampler.name = json_try_get<std::string>(sampler_object, "name");
		sampler.extensions = json_try_dump(sampler_object, "extensions");
		sampler.extras = json_try_dump(sampler_object, "extras");

		return sampler;
	}

	MagFilter number_to_mag_filter(int min_filter)
	{
		switch (min_filter)
		{
		case static_cast<int>(MagFilter::Nearest):
			return MagFilter::Nearest;
		case static_cast<int>(MagFilter::Linear):
			return MagFilter::Linear;
		}

		throw GLTFReadException("Invalid min filter in number: " + std::to_string(min_filter) + ".");
	}

	MinFilter number_to_min_filter(int mag_filter)
	{
		switch (mag_filter)
		{
		case static_cast<int>(MinFilter::Nearest):
			return MinFilter::Nearest;
		case static_cast<int>(MinFilter::Linear):
			return MinFilter::Linear;
		case static_cast<int>(MinFilter::NearestMipmapNearest):
			return MinFilter::NearestMipmapNearest;
		case static_cast<int>(MinFilter::LinearMipmapNearest):
			return MinFilter::LinearMipmapNearest;
		case static_cast<int>(MinFilter::NearestMipmapLinear):
			return MinFilter::NearestMipmapLinear;
		case static_cast<int>(MinFilter::LinearMipmapLinear):
			return MinFilter::LinearMipmapLinear;
		}

		throw GLTFReadException("Invalid mag filter in number: " + std::to_string(mag_filter) + ".");
	}

	Wrap number_to_wrap(int wrap)
	{
		switch (wrap)
		{
		case static_cast<int>(Wrap::ClampToEdge):
			return Wrap::ClampToEdge;
		case static_cast<int>(Wrap::MirroredRepeat):
			return Wrap::MirroredRepeat;
		case static_cast<int>(Wrap::Repeat):
			return Wrap::Repeat;
		}

		throw GLTFReadException("Invalid wrap mode in number: " + std::to_string(wrap) + ".");
	}
}
