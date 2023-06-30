#pragma once
#include <optional>
#include <string>
#include <json_nowarn.hpp>
#include <gltf/gltf_read_exception.h>

namespace glTF
{
	using json = nlohmann::json;

	template<typename T> std::optional<T> json_try_get(json object, const std::string& key)
	{
		if (object.contains(key))
		{
			return object[key].get<T>();
		}

		return std::nullopt;
	}

	template<typename T> T json_get_or_default(json object, const std::string& key, T default_value)
	{
		return json_try_get<T>(object, key).value_or(default_value);
	}

	template<typename T> T json_require(json object, const std::string& key)
	{
		if (!object.contains(key))
		{
			throw GLTFReadException("Required key: \"" + key + "\" not found.");
		}

		return object[key].get<T>();
	}

	template<typename In, typename Return> 
	using Func = Return(*)(In);

	template<typename T, typename ReturnT> std::optional<ReturnT> optional_map(std::optional<T> maybe, Func<T, ReturnT> function)
	{
		if (maybe.has_value())
		{
			return function(maybe.value());
		}
		
		return std::nullopt;
	}

	template<typename T> void optional_map_void(std::optional<T> maybe, Func<T, void> function)
	{
		if (maybe.has_value())
		{
			function(maybe.value());
		}
	}

	template<typename ArrayT, size_t ArraySize> std::optional<std::array<ArrayT, ArraySize>> json_try_get_array(json object, const std::string& key)
	{
		if (object.contains(key))
		{
			json::array_t arrayObject = object[key].get<json::array_t>();

			std::array<ArrayT, ArraySize> outputArray;

			for (size_t i = 0; i < ArraySize; i++)
			{
				outputArray[i] = arrayObject[i].get<ArrayT>();
			}

			return outputArray;
		}

		return std::nullopt;
	}

	template<typename ArrayT> std::optional<std::vector<ArrayT>> json_try_get_vector(json object, const std::string& key)
	{
		if (object.contains(key))
		{
			json::array_t array_object = object[key].get<json::array_t>();

			std::vector<ArrayT> output_vector;
			output_vector.reserve(array_object.size());

			for (const json& element : array_object)
			{
				output_vector.push_back(element.get<ArrayT>());
			}

			return output_vector;
		}

		return std::nullopt;
	}

	template<typename ArrayT> std::vector<ArrayT> json_require_vector(json object, const std::string& key)
	{
		std::optional<std::vector<ArrayT>> output_vector = json_try_get_vector<ArrayT>(object, key);
		if (output_vector.has_value())
		{
			return output_vector.value();
		}

		throw GLTFReadException("Required array with key: \"" + key + "\" not found.");
	}

	template<typename ArrayT> std::optional<std::vector<ArrayT>> json_try_get_vector_map(json object, const std::string& key, Func<json, ArrayT> func)
	{
		if (object.contains(key))
		{
			json::array_t array_object = object[key].get<json::array_t>();

			std::vector<ArrayT> output_vector;
			output_vector.reserve(array_object.size());

			for (const json& element : array_object)
			{
				output_vector.push_back(func(element));
			}

			return output_vector;
		}

		return std::nullopt;
	}

	template<typename ArrayT> std::vector<ArrayT> json_require_vector_map(json object, const std::string& key, Func<json, ArrayT> func)
	{
		std::optional<std::vector<ArrayT>> output_vector = json_try_get_vector_map<ArrayT>(object, key, func);
		if (output_vector.has_value())
		{
			return output_vector.value();
		}

		throw GLTFReadException("Required array with key: \"" + key + "\" not found.");
	}

	inline std::optional<std::string> json_try_dump(json object, const std::string& key)
	{
		const auto dump = [](json object_to_dump) { return object_to_dump.dump(); };

		return optional_map<json, std::string>(json_try_get<json>(object, key), dump);
	}
}
