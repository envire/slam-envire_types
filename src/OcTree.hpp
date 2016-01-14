#pragma once

#include <octomap/AbstractOcTree.h>
#include <envire_core/items/Item.hpp>
#include <envire_core/plugin/Plugin.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/string.hpp>

namespace envire { namespace type 
{

    typedef boost::shared_ptr< octomap::AbstractOcTree > AbstractOcTreePtr;

    class OcTree : public envire::core::Item< AbstractOcTreePtr >
    {
        ENVIRE_PLUGIN_HEADER(OcTree, AbstractOcTreePtr)
    public:
        OcTree() : envire::core::Item<AbstractOcTreePtr>() {}
        OcTree(const OcTree& octree) : envire::core::Item<AbstractOcTreePtr>() {this->user_data = octree.user_data;}
    };

}}

namespace boost { namespace serialization {

    template<class Archive>
    void load(Archive & ar, envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::stringstream stream;
        ar >> stream;
        if(!stream.str().empty())
            octree.reset(octomap::AbstractOcTree::read(stream));
    }

    template<class Archive>
    void save(Archive & ar, const envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
         std::stringstream stream;
         if(octree.get() != NULL)
            octree->write(stream);
         ar << stream;
    }

    template<class Archive>
    void serialize(Archive & ar, envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
        split_free(ar, octree, version);
    }



    template<class Archive>
    void load(Archive & ar, std::stringstream & stream, const unsigned int version)
    {
        std::string s;
        ar >> s;
        stream.clear();
        stream << s;
    }

    template<class Archive>
    void save(Archive & ar, const std::stringstream & stream, const unsigned int version)
    {
        std::string s = stream.str();
        ar << s;
    }

    template<class Archive>
    void serialize(Archive & ar, std::stringstream & stream, const unsigned int version)
    {
        split_free(ar, stream, version);
    }

}}
