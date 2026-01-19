#pragma once
#include "Classes/Base/GameState.h"
#include <vector>
#include <memory>

using namespace sf;

class StateManager
{
public:
    StateManager() = default;
    ~StateManager() = default;

    //Add a new state to the top of the stack
    void PushState(std::unique_ptr<GameState> state);

    //Remove the top state from the stack
    void PopState();

    //Change to a different state (pops current, pushes new)
    void ChangeState(std::unique_ptr<GameState> state);

    //Game loop functions - operate on the top state
    void HandleInput(RenderWindow& window);
    void Update();
    void Render(RenderWindow& window);

    //Check if there are any states
    bool IsEmpty() const { return states.empty(); }

private:
    std::vector<std::unique_ptr<GameState>> states;
};
