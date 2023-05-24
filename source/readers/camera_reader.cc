#include "camera_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Camera>> read_cameras(json root_object)
	{
		return json_try_get_vector_map(root_object, "cameras", read_camera);
	}

	Camera read_camera(json camera_object)
	{
		Camera camera;
		camera.orthographic = optional_map(json_try_get<json>(camera_object, "orthographic"), read_camera_orthographic);
		camera.perspective = optional_map(json_try_get<json>(camera_object, "perspective"), read_camera_perspective);
		camera.type = string_to_camera_type(json_require<std::string>(camera_object, "type"));
		camera.name = json_try_get<std::string>(camera_object, "name");
		camera.extensions = json_try_dump(camera_object, "extensions");
		camera.extras = json_try_dump(camera_object, "extras");

		if (camera.orthographic.has_value() && camera.type == CameraType::Perspective)
		{
			throw GLTFReadException("Othrographic defined when perspective is selected.");
		}

		if (camera.perspective.has_value() && camera.type == CameraType::Orthographic)
		{
			throw GLTFReadException("Perspective defined when othrographic is selected.");
		}

		return camera;
	}

	CameraOrthographic read_camera_orthographic(json camera_orthographic_object)
	{
		CameraOrthographic ortho;
		ortho.xmag = json_require<float>(camera_orthographic_object, "xmag");
		ortho.ymag = json_require<float>(camera_orthographic_object, "ymag");
		ortho.zfar = json_require<float>(camera_orthographic_object, "zfar");
		ortho.znear = json_require<float>(camera_orthographic_object, "znear");
		ortho.extensions = json_try_dump(camera_orthographic_object, "extensions");
		ortho.extras = json_try_dump(camera_orthographic_object, "extras");
		return ortho;
	}

	CameraPerspective read_camera_perspective(json camera_perspective)
	{
		CameraPerspective perspective;
		perspective.aspectRatio = json_try_get<float>(camera_perspective, "aspectRatio");
		perspective.yfov = json_require<float>(camera_perspective, "yfov");
		perspective.zfar = json_try_get<float>(camera_perspective, "zfar");
		perspective.znear = json_require<float>(camera_perspective, "znear");
		perspective.extensions = json_try_dump(camera_perspective, "extensions");
		perspective.extras = json_try_dump(camera_perspective, "extras");
		return perspective;
	}

	CameraType string_to_camera_type(std::string camera_type_string)
	{
		if (camera_type_string == "perspective") {
			return CameraType::Perspective;
		}

		if (camera_type_string == "orthographic") {
			return CameraType::Orthographic;
		}

		throw GLTFReadException("Invalid camera type in string: " + camera_type_string + ".");
	}
}