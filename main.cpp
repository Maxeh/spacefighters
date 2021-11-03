#include <SFML/Window.hpp>
#include "src/Constants.hpp"
#include "src/GameManager.hpp"

int main()
{
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    GameManager gameManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Spacefighters");
    return EXIT_SUCCESS;
}