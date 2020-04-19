#include <SFML/Window.hpp>
#include "src/Constants.hpp"
#include "src/GameManager.hpp"

int main()
{
    srand(time(nullptr));
    GameManager gameManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Spacefighters");
    return EXIT_SUCCESS;
}