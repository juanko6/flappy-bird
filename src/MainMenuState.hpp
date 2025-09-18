#pragma once
#include <GameState.hpp>

struct Bird
{
    float x, y;
    float vy, vx;

};

class MainMenuState : public GameState
{
    public:
        MainMenuState();
        ~MainMenuState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        Bird bird; //variable de tipo Bird
        char entered_key; // Variable para almacenar la tecla presionada
        bool key_pressed; // Bandera para indicar si se ha presionado una tecla
};