#pragma once

#include <octomap/AbstractOcTree.h>
#include <envire_core/items/Item.hpp>
#include <envire_core/plugin/Plugin.hpp>
#include <envire_core/serialization/BinaryBufferHelper.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>


namespace envire { namespace octomap
{

    typedef boost::shared_ptr< ::octomap::AbstractOcTree > AbstractOcTreePtr;

    class OcTree : public envire::core::Item< AbstractOcTreePtr >
    {
        ENVIRE_PLUGIN_HEADER(envire::octomap::OcTree)
        virtual const std::type_info* getTypeInfo() const override
        {
          return &typeid(envire::octomap::OcTree);
        }
    };
}}

namespace boost { namespace serialization {

    template<class Archive>
    void load(Archive & ar, envire::octomap::AbstractOcTreePtr & octree, const unsigned int version)
    {
        std::vector<uint8_t> buffer;
        ar >> buffer;
        if(!buffer.empty())
        {
            envire::core::BinaryInputBuffer buffer_helper(buffer);
            std::istream istream(&buffer_helper);
            octree.reset(::octomap::AbstractOcTree::read(istream));
        }
    }

    template<class Archive>
    void save(Archive & ar, const envire::octomap::AbstractOcTreePtr & octree, const unsigned int version)
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
    void serialize(Archive & ar, envire::octomap::AbstractOcTreePtr & octree, const unsigned int version)
    {
        split_free(ar, octree, version);
    }

}}
