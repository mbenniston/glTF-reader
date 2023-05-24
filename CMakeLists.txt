cmake_minimum_required(VERSION 3.16)

project(glTF-reader)

include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

add_library(glTF-project-sanitize INTERFACE)
add_library(glTF-project-warnings INTERFACE)
set_project_warnings(glTF-project-warnings)
enable_sanitizers(glTF-project-sanitize)

add_subdirectory(dependencies)
add_subdirectory(source)