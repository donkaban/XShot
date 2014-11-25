cmake_minimum_required(VERSION 2.8.4)
project(XShot)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
set(SOURCE_FILES
    main.cpp
    stb_image_write.h)

include_directories("/opt/X11/include")
link_directories("/opt/X11/lib")

add_executable(XShot ${SOURCE_FILES} )
target_link_libraries(XShot X11)