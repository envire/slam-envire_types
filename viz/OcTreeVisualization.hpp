#ifndef envire_types_OcTreeVisualization_H
#define envire_types_OcTreeVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <envire_octomap/OcTree.hpp>

namespace vizkit3d
{
    class OcTreeVisualization
        : public vizkit3d::Vizkit3DPlugin<envire::type::OcTree>
        , public vizkit3d::VizPluginAddType< boost::shared_ptr<octomap::AbstractOcTree> >
        , boost::noncopyable
    {
    Q_OBJECT

    Q_PROPERTY(bool ShowOccupied READ getShowOccupied WRITE setShowOccupied)
    Q_PROPERTY(bool ShowFreespace READ getShowFreespace WRITE setShowFreespace)
    Q_PROPERTY(int MaxTreeDepth READ getTreeMaxDepth WRITE setTreeMaxDepth)
    Q_PROPERTY(double AlphaOccupiedLevel READ getAlphaOccupiedLevel WRITE setAlphaOccupiedLevel)

    public:
        OcTreeVisualization();
        ~OcTreeVisualization();

        Q_INVOKABLE void updateData(envire::type::OcTree const &sample)
        {vizkit3d::Vizkit3DPlugin<envire::type::OcTree>::updateData(sample);}
        Q_INVOKABLE void updateData(boost::shared_ptr<octomap::AbstractOcTree> const &sample)
        {vizkit3d::Vizkit3DPlugin<envire::type::OcTree>::updateData(sample);}

    public slots:
        bool getShowOccupied() {return show_occupied;}
        void setShowOccupied(bool b) {show_occupied = b; emit propertyChanged("ShowOccupied"); redrawTree();}
        bool getShowFreespace() {return show_freespace;}
        void setShowFreespace(bool b) {show_freespace = b; emit propertyChanged("ShowFreespace"); redrawTree();}
        void setTreeMaxDepth(int max_depth) {this->max_depth = max_depth; emit propertyChanged("MaxTreeDepth"); reloadTree();}
        int getTreeMaxDepth() {return max_depth;}
        bool getAlphaOccupiedLevel() {return alpha_level;}
        void setAlphaOccupiedLevel(double alpha_level) {this->alpha_level = alpha_level; redrawTree();}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern(envire::type::OcTree const& value);
        virtual void updateDataIntern(envire::type::AbstractOcTreePtr const& value);
        void reloadTree() {new_tree = true; setDirty();}
        void redrawTree() {redraw = true; setDirty();}
        
    private:
        envire::type::OcTree tree;
        bool show_occupied;
        bool show_freespace;
        int max_depth;
        double alpha_level;
        bool new_tree;
        bool redraw;
    };
}
#endif
