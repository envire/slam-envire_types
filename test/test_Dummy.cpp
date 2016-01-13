#include <boost/test/unit_test.hpp>
#include <envire_types/Dummy.hpp>

using namespace envire_types;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    envire_types::DummyClass dummy;
    dummy.welcome();
}
