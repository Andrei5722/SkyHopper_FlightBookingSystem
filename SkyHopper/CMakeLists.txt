cmake_minimum_required(VERSION 3.27)
project(SkyHopper)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(SkyHopper
        .idea/.gitignore
        .idea/modules.xml
        .idea/SkyHopper.iml
        .idea/workspace.xml
        data/cities.txt
        include/Booking.h
        include/City.h
        include/FlightBookingSystem.h
        source/Booking.cpp
        source/City.cpp
        source/FlightBookingSystem.cpp
        source/main.cpp)
