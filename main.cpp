#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <SFML/Window.hpp>
#include "src/Constants.hpp"
#include "src/GameManager.hpp"

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    GameManager gameManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Spacefighters");
    return EXIT_SUCCESS;
}