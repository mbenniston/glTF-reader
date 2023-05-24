#pragma once
#include <vector>
#include <optional>
#include <string>

namespace glTF
{
	struct Attribute
	{
		std::string name;
		int accessorIndex;
	};

	struct MorphTarget
	{
		std::string name;
		int accessorIndex;
	};

	enum class TopologyType
	{
		Points = 0,
		Lines = 1,
		LineLoop = 2,
		LineStrip = 3,
		Triangles = 4,
		TrianglesStrip = 5,
		TrianglesFan = 6
	};

	struct Primitive
	{
		std::vector<Attribute> attributes;
		std::optional<int> indices;
		std::optional<int> material;
		TopologyType mode;
		std::optional<std::vector<MorphTarget>> targets;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct Mesh
	{
		std::vector<Primitive> primitives;
		std::optional<std::vector<float>> weights;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}