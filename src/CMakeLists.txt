rock_library(envire_octomap
    SOURCES OcTree.cpp
    HEADERS OcTree.hpp
    DEPS_CMAKE Boost octomap
    DEPS_PKGCONFIG class_loader envire_core)
