cmake_minimum_required(VERSION 3.12)

project( state-machine
         LANGUAGES CXX
         DESCRIPTION "State-Machine"
         HOMEPAGE_URL "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
)
add_executable( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/state-machine.cpp" )