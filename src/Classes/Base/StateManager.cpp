#include "Classes/Base/StateManager.h"

void StateManager::PushState(std::unique_ptr<GameState> state)
{
    //Call OnExit on the current top state (if it exists)
    if (!states.empty())
    {
        states.back()->OnExit();
    }

    //Add the new state and call OnEnter
    states.push_back(std::move(state));
    states.back()->OnEnter();
}

void StateManager::PopState()
{
    if (!states.empty())
    {
        //Call OnExit on the current state
        states.back()->OnExit();

        //Remove it from the stack
        states.pop_back();

        //Call OnEnter on the new top state (if it exists)
        if (!states.empty())
        {
            states.back()->OnEnter();
        }
    }
}

void StateManager::ChangeState(std::unique_ptr<GameState> state)
{
    if (!states.empty())
    {
        states.back()->OnExit();
        states.pop_back();
    }

    states.push_back(std::move(state));
    states.back()->OnEnter();
}

void StateManager::HandleInput(RenderWindow& window)
{
    if (!states.empty())
    {
        states.back()->HandleInput(window);
    }
}

void StateManager::Update()
{
    if (!states.empty())
    {
        states.back()->Update();
    }
}

void StateManager::Render(RenderWindow& window)
{
    if (!states.empty())
    {
        states.back()->Render(window);
    }
}