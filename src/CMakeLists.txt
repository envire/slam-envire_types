rock_library(envire_types
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(envire_types_bin Main.cpp
    DEPS envire_types)

