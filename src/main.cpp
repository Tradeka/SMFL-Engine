#include <SFML/Graphics.hpp>
#include "Classes/Derived/States/PongState.h"
#include "Classes/Derived/States/PongMenuState.h"
#include "Classes/Derived/States/PlatformerState.h"
#include "Classes/Base/StateManager.h"


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pong");
    window.setFramerateLimit(144);

    //Initialize State manager
    StateManager stateManager;

    /*GAMES*/

    //PONG
    //auto menuState = std::make_unique<PongMenuState>(stateManager);
    //stateManager.PushState(std::move(menuState));

	//PLATFORMER
	auto platformerState = std::make_unique<PlatformerState>();
	stateManager.PushState(std::move(platformerState));

    while (window.isOpen())
    {
        //Handle updates on current state
        stateManager.HandleInput(window);
        stateManager.Update();
        stateManager.Render(window);
    }
}
