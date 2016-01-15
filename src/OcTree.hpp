#pragma once

#include <octomap/AbstractOcTree.h>
#include <envire_core/items/Item.hpp>
#include <envire_core/plugin/Plugin.hpp>
#include <envire_core/serialization/BinaryBufferHelper.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>


namespace envire { namespace type 
{

    typedef boost::shared_ptr< octomap::AbstractOcTree > AbstractOcTreePtr;

    class OcTree : public envire::core::Item< AbstractOcTreePtr >
    {
        ENVIRE_PLUGIN_HEADER(OcTree)
    public:
        OcTree() : envire::core::Item<AbstractOcTreePtr>() {}
        OcTree(const OcTree& octree) : envire::core::Item<AbstractOcTreePtr>() {this->user_data = octree.user_data;}
    };

}}

namespace boost { namespace serialization {

    template<class Archive>
    void load(Archive & ar, envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::vector<uint8_t> buffer;
        ar >> buffer;
        if(!buffer.empty())
        {
            envire::core::BinaryInputBuffer buffer_helper(buffer);
            std::istream istream(&buffer_helper);
            octree.reset(octomap::AbstractOcTree::read(istream));
        }
    }

    template<class Archive>
    void save(Archive & ar, const envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::vector<uint8_t> buffer;
        buffer.reserve(octree->memoryUsage());
        envire::core::BinaryOutputBuffer buffer_helper(&buffer);
        std::ostream ostream(&buffer_helper);
         if(octree.get() != NULL)
            octree->write(ostream);
         ar << buffer;
    }

    template<class Archive>
    void serialize(Archive & ar, envire::type::AbstractOcTreePtr & octree, const unsigned int version)
    {
        split_free(ar, octree, version);
    }

}}
