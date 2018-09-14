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
    Q_PROPERTY(QStringList ColorMode READ getColorModes WRITE setColorModes)

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
        QStringList getColorModes() {return color_modes;}
        void setColorModes(QStringList color_mode) {this->color_modes = color_mode; redrawTree();}

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
        QStringList color_modes;
        std::map<QString, unsigned> color_mode_map;
    };
}
#endif