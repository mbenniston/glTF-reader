#pragma once
#include <optional>
#include <vector>
#include <array>

namespace glTF
{
	struct Node
	{
		std::optional<int> camera;
		std::optional<std::vector<int>> children;
		std::optional<int> skin;
		std::array<float, 16> matrix;
		std::optional<int> mesh;
		std::array<float, 4> rotation;
		std::array<float, 3> scale;
		std::array<float, 3> translation;
		std::optional<std::vector<float>> weights;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}