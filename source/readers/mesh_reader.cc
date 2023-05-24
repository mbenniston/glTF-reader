#include "mesh_reader.h"
#include "../json_utils.h"

namespace glTF
{
	std::optional<std::vector<Mesh>> read_meshes(json root_object)
	{
		return json_try_get_vector_map(root_object, "meshes", read_mesh);
	}

	Mesh read_mesh(json mesh_object)
	{
		Mesh mesh;
		mesh.primitives = json_require_vector_map(mesh_object, "primitives", read_primitive);
		mesh.weights = json_try_get_vector<float>(mesh_object, "weights");
		mesh.name = json_try_get<std::string>(mesh_object, "name");
		mesh.extensions = json_try_dump(mesh_object, "extensions");
		mesh.extras = json_try_dump(mesh_object, "extras");

		return mesh;
	}

	Primitive read_primitive(json primitive_object)
	{
		Primitive primitive;

		json attribute_list = primitive_object["attributes"];
		primitive.attributes.reserve(attribute_list.size());

		for (const auto& attribute_object : attribute_list.items())
		{
			Attribute attribute;
			attribute.name = attribute_object.key();
			attribute.accessorIndex = attribute_object.value().get<int>();

			primitive.attributes.emplace_back(std::move(attribute));
		}

		primitive.indices = json_try_get<int>(primitive_object, "indices");
		primitive.material = json_try_get<int>(primitive_object, "material");
		primitive.mode = optional_map(json_try_get<int>(primitive_object, "mode"), number_to_toplogy_type).value_or(TopologyType::Triangles);
		
		if (primitive_object.contains("targets"))
		{
			json target_objects = primitive_object["targets"];
			std::vector<MorphTarget> targets;
			targets.reserve(target_objects.size());

			for (const auto& target_object : target_objects.items())
			{
				MorphTarget target;
				target.name = target_object.key();
				target.accessorIndex = target_object.value().get<int>();

				targets.emplace_back(std::move(target));
			}

			primitive.targets.emplace(std::move(targets));
		}
		
		primitive.extensions = json_try_dump(primitive_object, "extensions");
		primitive.extras = json_try_dump(primitive_object, "extras");

		return primitive;
	}

	TopologyType number_to_toplogy_type(int toplogy_type)
	{
		switch (toplogy_type)
		{
		case 0:
			return TopologyType::Points;
		case 1:
			return TopologyType::Lines;
		case 2:
			return TopologyType::LineLoop;
		case 3:
			return TopologyType::LineStrip;
		case 4:
			return TopologyType::Triangles;
		case 5:
			return TopologyType::TrianglesStrip;
		case 6:
			return TopologyType::TrianglesFan;
		}

		throw GLTFReadException("Invalid mode in number: " + std::to_string(toplogy_type) + ".");
	}
}