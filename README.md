# glTF-reader

A C++ library that reads in glTF files and deserializes them into more strongly typed structures.

Features:

- Reading of glTF and glb files
- 1 to 1 data mirroring of glTF files

Supported readable data:

- [accessors](/include/gltf/data/accessor.h)
- [animations](/include/gltf/data/animation.h)
- [buffers](/include/gltf/data/buffer.h)
- [bufferViews](/include/gltf/data/buffer_view.h)
- [cameras](/include/gltf/data/camera.h)
- [images](/include/gltf/data/image.h)
- [materials](/include/gltf/data/material.h)
- [meshes](/include/gltf/data/meshe.h)
- [nodes](/include/gltf/data/node.h)
- [samplers](/include/gltf/data/sampler.h)
- [scene](/include/gltf/data/scen.h)
- [scenes](/include/gltf/data/scene.h)
- [skins](/include/gltf/data/skin.h)
- [textures](/include/gltf/data/texture.h)
- meta data (extras, extensions)

Missing Features:

- Binary file detection (reading first few bytes could be a solution)
- Unit tests, would require significant effort to check every edge case of every field.
- CMake exports
- Optional file validation

Supporting documents:

- [glTF specification](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html)

## Usage

Including the library:

```cmake
add_subdirectory(glTF-reader)
...
target_link_libraries(your-target glTF-reader::glTF-reader)
```

Loading gltf files:

```cpp
#include <gltf/gltf.h>
...
glTF::File my_gltf_file = glTF::read_from_stream(my_json_stream);
```
