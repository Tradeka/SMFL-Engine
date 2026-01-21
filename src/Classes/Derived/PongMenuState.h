#pragma once
#include "Classes/Base/GameState.h"
#include "Classes/Base/StateManager.h"

class PongMenuState : public GameState
{
public:
	PongMenuState(StateManager& mgr);
	~PongMenuState() = default;

	//Overrides
	void HandleInput(RenderWindow& window) override;
	void Update() override;
	void Render(RenderWindow& window) override;

	//Child specific utility functions
	void SwitchSelectedButton();
	void SelectedButtonPressed(RenderWindow& window);
	void StartGame();
	void QuitGame(RenderWindow& window);


private:
	//Font
	Font gameFont;
	//Title and buttons
	std::unique_ptr<Text> titleText;
	std::unique_ptr<Text> buttonTexts[2];

	//State manager reference for transitioning to game state
	StateManager* stateManager;

	//int to keep track of which button is selected
	int selectedButtonIndex;

};
