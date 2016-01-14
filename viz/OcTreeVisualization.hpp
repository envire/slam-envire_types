#ifndef envire_types_OcTreeVisualization_H
#define envire_types_OcTreeVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <#include>

namespace vizkit3d
{
    class OcTreeVisualization
        : public vizkit3d::Vizkit3DPlugin<envire::type::OcTree>
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        OcTreeVisualization();
        ~OcTreeVisualization();

    Q_INVOKABLE void updateData(envire::type::OcTree const &sample)
    {vizkit3d::Vizkit3DPlugin<envire::type::OcTree>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(envire::type::OcTree const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
