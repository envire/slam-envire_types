rock_find_qt4(QtXml)

rock_vizkit_plugin(octomap-viz
    OcTreeVisualization.cpp
    DEPS envire_octomap
    DEPS_CMAKE QGLViewer octovis
    MOC OcTreeVisualization.hpp
    HEADERS OcTreeVisualization.hpp)
