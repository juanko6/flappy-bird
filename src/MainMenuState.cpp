#include <MainMenuState.hpp>
#include "StateMachine.hpp"
#include <iostream>
#include <raylib.h>

MainMenuState::MainMenuState()
{
    entered_key = 0;
    key_pressed = false;
}

void MainMenuState::init()
{
    std::cout << "You are in the Main Menu State" << std::endl;
    std::cout << "Press any key..." << std::endl;

    // Inicializar el pájaro en posición
    bird.x = 144.0f;
    bird.y = 256.0f;
    bird.vy = 0.0f;
    bird.vx = 0.0f;
}

void MainMenuState::handleInput()
{
    const float acceleration = 250.0f;

    // Detectar tecla ESPACIO para impulso del pájaro
    if (IsKeyPressed(KEY_UP))
    {
        bird.vy = -300.0f; // HACIA ARRIBA
        std::cout << "Bird flies up!" << std::endl;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        bird.vx -= acceleration * GetFrameTime();
        std::cout << "Bird flies left!" << std::endl;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        bird.vx += acceleration * GetFrameTime();
        std::cout << "Bird flies right!" << std::endl;
    }
    else {
        // Desaceleración gradual cuando no se presionan teclas
        float friction = 100.0f; // Coeficiente de fricción

        if (bird.vx > 0) {
            bird.vx -= friction * GetFrameTime();
            if (bird.vx < 0) bird.vx = 0; // Evitar que cambie de dirección
        }
        else if (bird.vx < 0) {
            bird.vx += friction * GetFrameTime();
            if (bird.vx > 0) bird.vx = 0; // Evitar que cambie de dirección
        }
    }

    // limite velocidad horizontal
    float max_speed = 500.0f;
    if (bird.vx > max_speed) bird.vx = max_speed;
    if (bird.vx < -max_speed) bird.vx = -max_speed;

    // Salir con ESC
    if (IsKeyPressed(KEY_ESCAPE))
    {
        state_machine->remove_state(true);
    }
}

void MainMenuState::update(float deltaTime)
{
    this->handleInput();

    // FÍSICA DEL PÁJARO
    const float gravity = 800.0f; // Gravedad constante

    // Aplicar gravedad a la velocidad
    bird.vy += gravity * deltaTime;

    // Actualizar posición con la velocidad
    bird.y += bird.vy * deltaTime;

    // Actualizar posición horizontal
    bird.x += bird.vx * deltaTime;

    // Opcional: Límites de pantalla
    if (bird.y > 433)
    { // Si sale por abajo
        bird.y = 433;
        bird.vy = 0;
    }
    if (bird.y < 0)
    { // Si sale por arriba
        bird.y = 0;
        bird.vy = 0;
    }
    if (bird.x < 0)
    { // Si sale por la izquierda
        bird.x = 0;
        bird.vx = 0;
    }
    if (bird.x > 288)
    { // Si sale por la derecha
        bird.x = 288;
        bird.vx = 0;
    }
}

void MainMenuState::render()
{
    // Renderizar en la ventana de raylib
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dibujar pajaro
    DrawCircle(bird.x, bird.y, 17, RED);

    //dibujar tierra
    DrawRectangle(0, 450, 288, 62, BROWN);

    // Instrucciones para el jugador
    DrawText("Press SPACE to fly!", 50, 50, 20, DARKGRAY);
    DrawText("Press ESC to exit", 50, 80, 16, GRAY);

    // Mostrar autor
    DrawText("juanko6", 122, 460, 8, DARKGRAY);

    EndDrawing();
}