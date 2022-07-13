//
// Copyright (c) 2015, Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "OcTreeVisualization.hpp"

#include <octovis/OcTreeDrawer.h>
#include <octomap/AbstractOcTree.h>

using namespace vizkit3d;

class OcTreeDrawable : public osg::Drawable
{
    friend OcTreeVisualization;
public:
    OcTreeDrawable() {}

    OcTreeDrawable(const OcTreeDrawable& drawable,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY) : Drawable(drawable, copyop)
    {
        setOctree(drawable.tree);
    }

    void setOctree(const boost::shared_ptr<octomap::AbstractOcTree>& octree)
    {
        tree = octree;
        if(tree.get() == NULL)
            drawer.clear();
        else
            drawer.setOcTree(*octree);
        setDirty();
    }

    void setDirty()
    {
        dirtyDisplayList();
        dirtyBound();
    }

    virtual osg::Object* cloneType() const {return new OcTreeDrawable();}

    virtual osg::Object* clone(const osg::CopyOp& copyop) const {return new OcTreeDrawable(*this, copyop);}

    virtual void drawImplementation(osg::RenderInfo&) const {drawer.draw();}

    virtual osg::BoundingBox computeBoundingBox() const
    {
        osg::BoundingBox bbox;
        if(tree.get() != NULL)
        {
            double minX, minY, minZ, maxX, maxY, maxZ;
            minX = minY = minZ = maxX = maxY = maxZ = 0.0;

            tree->getMetricMin(minX, minY, minZ);
            tree->getMetricMax(maxX, maxY, maxZ);

            bbox.expandBy(osg::Vec3(minX, minY, minZ));
            bbox.expandBy(osg::Vec3(maxX, maxY, maxZ));
        }
        return bbox;
    }

protected:
    boost::shared_ptr<octomap::AbstractOcTree> tree;
    octomap::OcTreeDrawer drawer;
};


OcTreeVisualization::OcTreeVisualization()
{
    show_occupied = true;
    show_freespace = false;
    max_depth = 16;
    alpha_level = 0.8;
    new_tree = false;
    redraw = false;
    color_modes.append("FLAT");
    color_modes.append("PRINTOUT");
    color_modes.append("COLOR_HEIGHT");
    color_modes.append("GRAY_HEIGHT");
    color_modes.append("SEMANTIC");
    for(QStringList::iterator it = color_modes.begin(); it != color_modes.end(); it++)
    {
        color_mode_map[*it] = color_modes.indexOf(*it);
    }
}

OcTreeVisualization::~OcTreeVisualization()
{
}

osg::ref_ptr<osg::Node> OcTreeVisualization::createMainNode()
{
    osg::Geode* geode = new osg::Geode;

    OcTreeDrawable* octree_drawable = new OcTreeDrawable();
    geode->addDrawable(octree_drawable);

    return geode;
}

void OcTreeVisualization::updateMainNode ( osg::Node* node )
{
    if(new_tree || redraw)
    {
        osg::Geode* geode = dynamic_cast<osg::Geode*>(node);
        OcTreeDrawable* drawable = dynamic_cast<OcTreeDrawable*>(geode->getDrawable(0));

        if(drawable)
        {
            drawable->drawer.enableOcTreeCells(show_occupied);
            drawable->drawer.enableFreespace(show_freespace);
            drawable->drawer.setAlphaOccupied(alpha_level);
            drawable->drawer.setMax_tree_depth(max_depth);
            drawable->drawer.setColorMode(static_cast<octomap::SceneObject::ColorMode>(color_mode_map[color_modes.front()]));

            if(new_tree)
            {
                drawable->setOctree(tree);
                new_tree = false;
            }
            else if(redraw)
            {
                drawable->setDirty();
                redraw = false;
            }
        }
    }
}

void OcTreeVisualization::updateDataIntern(boost::shared_ptr<octomap::AbstractOcTree> const& value)
{
    tree = value;
    reloadTree();
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(OcTreeVisualization)
