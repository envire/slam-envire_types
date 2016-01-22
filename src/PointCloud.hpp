#pragma once

#include <envire_core/items/Item.hpp>
#include <envire_core/plugin/Plugin.hpp>
#include <pcl/PCLPointCloud2.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>


namespace envire { namespace type
{
    class PointCloud : public envire::core::Item< pcl::PCLPointCloud2 >
    {
        ENVIRE_PLUGIN_HEADER(PointCloud)
    };
}}


namespace boost { namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, pcl::PCLPointCloud2 & pointcloud, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("header", pointcloud.header);
        ar & boost::serialization::make_nvp("height", pointcloud.height);
        ar & boost::serialization::make_nvp("width", pointcloud.width);
        ar & boost::serialization::make_nvp("fields", pointcloud.fields);
        ar & boost::serialization::make_nvp("is_bigendian", pointcloud.is_bigendian);
        ar & boost::serialization::make_nvp("point_step", pointcloud.point_step);
        ar & boost::serialization::make_nvp("row_step", pointcloud.row_step);
        ar & boost::serialization::make_nvp("data", pointcloud.data);
        ar & boost::serialization::make_nvp("is_dense", pointcloud.is_dense);
    }

    template<class Archive>
    void serialize(Archive & ar, pcl::PCLHeader & header, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("seq", header.seq);
        ar & boost::serialization::make_nvp("stamp", header.stamp);
        ar & boost::serialization::make_nvp("frame_id", header.frame_id);
    }

    template<class Archive>
    void serialize(Archive & ar, pcl::PCLPointField & field, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("name", field.name);
        ar & boost::serialization::make_nvp("offset", field.offset);
        ar & boost::serialization::make_nvp("datatype", field.datatype);
        ar & boost::serialization::make_nvp("count", field.count);
    }

}}