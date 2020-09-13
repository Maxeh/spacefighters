cmake_minimum_required(VERSION 3.11)
project(spacefighters)
add_executable(spacefighters main.cpp src/GameScreen/Asteroid.cpp src/GameScreen/Asteroid.hpp src/GameScreen/Spaceship.cpp src/GameScreen/Spaceship.hpp src/Constants.hpp src/Screen.hpp src/GameScreen/GameScreen.cpp src/GameScreen/GameScreen.hpp src/AssetManager.cpp src/AssetManager.hpp src/ScreenManager.cpp src/ScreenManager.hpp src/GameManager.cpp src/GameManager.hpp src/SplashScreen/SplashScreen.cpp src/SplashScreen/SplashScreen.hpp src/MenuScreen/MenuScreen.cpp src/MenuScreen/MenuScreen.hpp src/SpaceButton.cpp src/SpaceButton.hpp)

#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "~/Github/spacefighters/SFML-2.5.1-Compiled/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
target_link_libraries(spacefighters sfml-graphics sfml-audio)