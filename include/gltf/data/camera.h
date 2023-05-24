#pragma once
#include <optional>
#include <string>

namespace glTF
{
	struct CameraOrthographic
	{
		float xmag;
		float ymag;
		float zfar;
		float znear;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	struct CameraPerspective
	{
		std::optional<float> aspectRatio;
		float yfov;
		std::optional<float> zfar;
		float znear;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};

	enum class CameraType
	{
		Perspective,
		Orthographic
	};

	struct Camera
	{
		std::optional<CameraOrthographic> orthographic;
		std::optional<CameraPerspective> perspective;
		CameraType type;
		std::optional<std::string> name;
		std::optional<std::string> extensions;
		std::optional<std::string> extras;
	};
}