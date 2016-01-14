rock_library(octomap_envire_plugin
    SOURCES OcTree.cpp
    HEADERS OcTree.hpp
    DEPS_CMAKE Boost octomap
    DEPS_PKGCONFIG class_loader envire_core)

set(target_libs octomap_envire_plugin)

rock_library(envire_types
    SOURCES Dummy.cpp
    DEPS ${target_libs})
