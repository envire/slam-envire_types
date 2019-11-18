# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 2.6)
set(ROCK_USE_CXX11 TRUE)
find_package(Rock)
find_package(PluginManager)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
rock_init(envire_octomap 0.1)
rock_standard_layout()
