#include <boost/test/unit_test.hpp>

#include <envire_core/plugin/ClassLoader.hpp>
#include <envire_core/items/Item.hpp>
#include <octomap/AbstractOcTree.h>

BOOST_AUTO_TEST_CASE(abstract_octree_plugin_test)
{
    BOOST_CHECK(envire::core::ClassLoader::getInstance()->hasEnvireItem("envire::core::Item<boost::shared_ptr<octomap::AbstractOcTree>>"));
    envire::core::ItemBase::Ptr base_plugin;
    BOOST_CHECK(envire::core::ClassLoader::getInstance()->createEnvireItem("envire::core::Item<boost::shared_ptr<octomap::AbstractOcTree>>", base_plugin));
    envire::core::Item<boost::shared_ptr<octomap::AbstractOcTree>>::Ptr map_plugin = boost::dynamic_pointer_cast< envire::core::Item<boost::shared_ptr<octomap::AbstractOcTree>> >(base_plugin);
    BOOST_CHECK(map_plugin != NULL);
    std::string class_name;
    BOOST_CHECK(map_plugin->getClassName(class_name));
    BOOST_CHECK(class_name == "envire::core::Item<boost::shared_ptr<octomap::AbstractOcTree>>");
}