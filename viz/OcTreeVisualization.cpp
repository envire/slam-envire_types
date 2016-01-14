#include <iostream>
#include "OcTreeVisualization.hpp"

using namespace vizkit3d;

struct OcTreeVisualization::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    envire::type::OcTree data;
};


OcTreeVisualization::OcTreeVisualization()
    : p(new Data)
{
}

OcTreeVisualization::~OcTreeVisualization()
{
    delete p;
}

osg::ref_ptr<osg::Node> OcTreeVisualization::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void OcTreeVisualization::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void OcTreeVisualization::updateDataIntern(envire::type::OcTree const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(OcTreeVisualization)

