rock_library(envire_octomap
    SOURCES OcTree.cpp
    HEADERS OcTree.hpp
    DEPS_CMAKE Boost octomap
    DEPS_PKGCONFIG class_loader_melodic envire_core)

install_plugin_info(envire_octomap)