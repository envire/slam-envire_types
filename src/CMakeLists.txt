rock_library(OcTree_envire_plugin
    SOURCES OcTree.cpp
    HEADERS OcTree.hpp
    DEPS_CMAKE Boost octomap
    DEPS_PKGCONFIG class_loader envire_core)

rock_library(PointCloud_envire_plugin
    SOURCES PointCloud.cpp
    HEADERS PointCloud.hpp
    DEPS_CMAKE Boost
    DEPS_PKGCONFIG pcl_common-1.7 class_loader envire_core)



set(target_libs OcTree_envire_plugin PointCloud_envire_plugin)

rock_library(envire_types
    SOURCES Dummy.cpp
    DEPS ${target_libs})
