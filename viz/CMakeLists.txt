rock_find_qt4(QtXml)

rock_vizkit_plugin(octomap-viz
    OcTreeVisualization.cpp
    DEPS OcTree_envire_plugin
    DEPS_CMAKE QGLViewer octovis
    MOC OcTreeVisualization.hpp
    HEADERS OcTreeVisualization.hpp)