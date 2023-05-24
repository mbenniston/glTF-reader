#include "skin_reader.h"
#include "../json_utils.h"

namespace glTF
{
    std::optional<std::vector<Skin>> read_skins(json root_object)
    {
		return json_try_get_vector_map(root_object, "skins", read_skin);
    }

    Skin read_skin(json skin_object)
    {
        Skin skin;
		skin.inverseBindMatrices = json_try_get<int>(skin_object, "inverseBindMatrices");
		skin.skeleton = json_try_get<int>(skin_object, "skeleton");
		skin.joints = json_require_vector<int>(skin_object, "joints");
		skin.name = json_try_get<std::string>(skin_object, "name");
		skin.extensions = json_try_dump(skin_object, "extensions");
		skin.extras = json_try_dump(skin_object, "extras");

		return skin;
    }
}
