#include <SFML/Graphics.hpp>
#include "Classes/Derived/PongState.h"
#include "Classes/Base/StateManager.h"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pong");
    window.setFramerateLimit(144);

    //Initialize State manager
    StateManager stateManager;

    //Add a Pong State to the state manager
    stateManager.PushState(std::make_unique<PongState>());


    while (window.isOpen())
    {
        //Handle updates on current state
        stateManager.HandleInput(window);
        stateManager.Update();
        stateManager.Render(window);
    }
}
