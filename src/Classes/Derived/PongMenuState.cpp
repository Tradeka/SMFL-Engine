#include "Classes/Derived/PongMenuState.h"
#include "Classes/Derived/PongState.h"


//Constructor
PongMenuState::PongMenuState()
{
	//Set up text objects
	titleText = std::make_unique<Text>();
	titleText->setString("Pong");
	titleText->setCharacterSize(250);
	titleText->setPosition({540.f - (titleText->getCharacterSize() * 4), 250.f});

	buttonTexts[0] = std::make_unique<Text>();
	buttonTexts[0]->setString("Play Game");
	buttonTexts[0]->setCharacterSize(100);
	buttonTexts[0]->setPosition({ 540.f - (buttonTexts[0]->getCharacterSize() * 9), 500.f});
	buttonTexts[0]->setFillColor(Color::Yellow); //Set this one to yellow on initialization because this is the default selected button

	buttonTexts[1] = std::make_unique<Text>();
	buttonTexts[1]->setString("Quit");
	buttonTexts[1]->setCharacterSize(100);
	buttonTexts[1]->setPosition({ 540.f - (buttonTexts[1]->getCharacterSize() * 4), 530.f });

	//Initialize selected index
	selectedButtonIndex = 0;
}

//Overrides
void PongMenuState::HandleInput(RenderWindow& window)
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
		{
			window.close();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		selectedButtonIndex--;
		SwitchSelectedButton();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		selectedButtonIndex++;
		SwitchSelectedButton();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{
		SelectedButtonPressed(window);
	}
}

void PongMenuState::Update()
{

}

void PongMenuState::Render(RenderWindow& window)
{
	window.draw(*titleText);
	window.draw(*buttonTexts[0]);
	window.draw(*buttonTexts[1]);
}

//Utility
void PongMenuState::SwitchSelectedButton()
{
	switch (selectedButtonIndex)
	{
	case 0:
		buttonTexts[0]->setFillColor(Color::Yellow);
		buttonTexts[1]->setFillColor(Color::White);
		break;
	case 1:
		buttonTexts[0]->setFillColor(Color::White);
		buttonTexts[1]->setFillColor(Color::Yellow);
		break;
	}
}

void PongMenuState::SelectedButtonPressed(RenderWindow& window)
{
	switch (selectedButtonIndex)
	{
	case 0:
		StartGame();
		break;
	case 1:
		QuitGame(window);
		break;
	}
}

void PongMenuState::StartGame()
{
	stateManager.PushState(std::make_unique<PongState>());
}

void PongMenuState::QuitGame(RenderWindow& window)
{
	window.close();
}

//Setter
void PongMenuState::SetStateManager(StateManager mgr)
{
	stateManager = mgr;
}