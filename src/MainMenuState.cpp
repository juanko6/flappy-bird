#include <MainMenuState.hpp>
#include <iostream>
#include <raylib.h>

MainMenuState::MainMenuState(): entered_key(' '), key_pressed(false)
{
}

void MainMenuState::init()
{
    std::cout << "You are in the Main Menu State" << std::endl;
    std::cout << "Press any key..." << std::endl;
}

void MainMenuState::handleInput()
{

    // Capturar cualquier tecla presionada usando raylib
    int key = GetKeyPressed();
    if (key != 0)
    {
        entered_key = (char)key;
        key_pressed = true;
        
        // Mostrar en consola inmediatamente
        std::cout << "You entered: " << entered_key << std::endl;
    }
    
}

void MainMenuState::update(float deltaTime)
{
    this->handleInput();
}

void MainMenuState::render()
{
    // Renderizar en la ventana de raylib
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Mostrar instrucciones
    DrawText("Press any key", 65, 200, 20, DARKGRAY);
    
    // Mostrar la tecla presionada si hay una
    if (key_pressed)
    {
        char text[50];
        sprintf(text, "You entered: %c", entered_key);
        DrawText(text, 65, 250, 20, RED);
    }

    // Mostrar autor
    DrawText("juanko6", 122, 460, 8, DARKGRAY);
    
    EndDrawing();
}