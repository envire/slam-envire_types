#ifndef envire_octomap_OcTreeVisualization_H
#define envire_octomap_OcTreeVisualization_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>

namespace octomap
{
    class AbstractOcTree;
}

namespace vizkit3d
{
    class OcTreeVisualization
        : public vizkit3d::Vizkit3DPlugin< boost::shared_ptr<octomap::AbstractOcTree> >
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

        Q_INVOKABLE void updateData(boost::shared_ptr<octomap::AbstractOcTree> const &sample)
        {vizkit3d::Vizkit3DPlugin< boost::shared_ptr<octomap::AbstractOcTree> >::updateData(sample);}

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
        virtual void updateDataIntern(boost::shared_ptr<octomap::AbstractOcTree> const& value);
        void reloadTree() {new_tree = true; setDirty();}
        void redrawTree() {redraw = true; setDirty();}
        
    private:
        boost::shared_ptr<octomap::AbstractOcTree> tree;
        bool show_occupied;
        bool show_freespace;
        int max_depth;
        double alpha_level;
        bool new_tree;
        bool redraw;
    };
}
#endif