#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// Abstract base class for all game states
class GameState
{
public:
    virtual ~GameState() = default;

    //Core game loop functions
    virtual void HandleInput(RenderWindow& window) = 0;
    virtual void Update() = 0;
    virtual void Render(RenderWindow& window) = 0;

    //state management hooks
    virtual void OnEnter() {}
    virtual void OnExit() {}
};
