cmake_minimum_required(VERSION 3.16)

add_library(glTF-reader)
add_library(glTF-reader::glTF-reader ALIAS glTF-reader)

target_sources(glTF-reader
PRIVATE
	"readers/file_reader.cc"
	"readers/accessor_reader.cc"
	"readers/buffer_reader.cc"
	"readers/buffer_view_reader.cc"
	"readers/image_reader.cc"
	"readers/material_reader.cc"
	"readers/mesh_reader.cc"
	"readers/node_reader.cc"
	"readers/sampler_reader.cc"
	"readers/scene_reader.cc"
	"readers/texture_reader.cc"
	"readers/asset_reader.cc" 
	"readers/animation_reader.cc" 
	"readers/skin_reader.cc" 
	"readers/camera_reader.cc")

target_precompile_headers(glTF-reader 
PRIVATE
	<json_nowarn.hpp>
	<string>
	<optional>
	<vector>
	<array>
)

target_compile_features(glTF-reader PUBLIC cxx_std_17)
target_link_libraries(glTF-reader 
PRIVATE		
	glTF-json
	glTF-project-sanitize
	glTF-project-warnings
)

target_include_directories(glTF-reader 
PUBLIC 
	"../include"
)
