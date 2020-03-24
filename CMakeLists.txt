cmake_minimum_required(VERSION 3.11)
project(spacefighters)
add_executable(spacefighters main.cpp src/View.cpp src/View.hpp src/Controller.cpp src/Controller.hpp src/Model.cpp src/Model.hpp src/Asteroid.cpp src/Asteroid.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/Maximilian/Documents/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
target_link_libraries(spacefighters sfml-graphics sfml-audio)