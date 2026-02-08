#include <SFML/Graphics.hpp>
#include "Classes/Derived/States/PongState.h"
#include "Classes/Derived/States/PongMenuState.h"
#include "Classes/Base/StateManager.h"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pong");
    window.setFramerateLimit(144);

    //Initialize State manager
    StateManager stateManager;

    auto menuState = std::make_unique<PongMenuState>(stateManager);

    //Add a PongMenuState to the state manager
    stateManager.PushState(std::move(menuState));


    while (window.isOpen())
    {
        //Handle updates on current state
        stateManager.HandleInput(window);
        stateManager.Update();
        stateManager.Render(window);
    }
}
