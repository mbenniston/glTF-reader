#pragma once
#include <vector>
#include <json_nowarn.hpp>
#include <gltf/data/camera.h>

namespace glTF
{
	std::optional<std::vector<Camera>> read_cameras(nlohmann::json root_object);
	Camera read_camera(nlohmann::json camera_object);

	CameraOrthographic read_camera_orthographic(nlohmann::json camera_orthographic_object);
	CameraPerspective read_camera_perspective(nlohmann::json camera_perspective);
	CameraType string_to_camera_type(std::string camera_type_string);
}
