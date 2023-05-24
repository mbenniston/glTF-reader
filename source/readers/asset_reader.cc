#include "asset_reader.h"
#include "../json_utils.h"

namespace glTF
{
	Asset read_asset(json file_object)
	{
		json asset_object = json_require<json>(file_object, "asset");
		Asset asset;
		asset.copyright = json_try_get<std::string>(asset_object, "copyright");
		asset.generator = json_try_get<std::string>(asset_object, "generator");
		asset.version = json_require<std::string>(asset_object, "version");
		asset.minVersion = json_try_get<std::string>(asset_object, "minVersion");
		asset.extensions = json_try_dump(asset_object, "extensions");
		asset.extras = json_try_dump(asset_object, "extras");

		return asset;
	}
}
