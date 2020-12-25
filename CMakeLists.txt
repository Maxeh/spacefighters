cmake_minimum_required(VERSION 3.11)
project(spacefighters)
add_executable(spacefighters main.cpp src/GameScreen/Asteroid.cpp src/GameScreen/Asteroid.hpp src/GameScreen/Spaceship.cpp src/GameScreen/Spaceship.hpp src/Constants.hpp src/Screen.hpp src/GameScreen/GameScreen.cpp src/GameScreen/GameScreen.hpp src/AssetManager.cpp src/AssetManager.hpp src/ScreenManager.cpp src/ScreenManager.hpp src/GameManager.cpp src/GameManager.hpp src/SplashScreen/SplashScreen.cpp src/SplashScreen/SplashScreen.hpp src/MenuScreen/MenuScreen.cpp src/MenuScreen/MenuScreen.hpp src/SpaceButton.cpp src/SpaceButton.hpp src/GameScreen/Missile.cpp src/GameScreen/Missile.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/Maximilian/Documents/Projects/SFML-2.5.1/lib/cmake/SFML")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(spacefighters sfml-graphics sfml-audio)