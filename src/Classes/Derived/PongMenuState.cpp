#include "Classes/Derived/PongMenuState.h"
#include "Classes/Derived/PongState.h"
#include <iostream>


//Constructor
PongMenuState::PongMenuState(StateManager& mgr)
{
	//Initialize statemanager ref
	stateManager = &mgr;

	//Load font
	if (!gameFont.openFromFile("Assets/Fonts/ByteBounce.ttf"))
	{
		std::cerr << "Failed to load font: Assets/Fonts/ByteBounce.ttf" << std::endl;
	}

	//Set up text objects
	titleText = std::make_unique<Text>(gameFont);
	titleText->setFont(gameFont);
	titleText->setString("Pong");
	titleText->setCharacterSize(250);
	titleText->setPosition({730.f, 250.f});

	buttonTexts[0] = std::make_unique<Text>(gameFont);
	buttonTexts[0]->setFont(gameFont);
	buttonTexts[0]->setString("Play Game");
	buttonTexts[0]->setCharacterSize(100);
	buttonTexts[0]->setPosition({ 755.f, 500.f});
	buttonTexts[0]->setFillColor(Color::Yellow); //Set this one to yellow on initialization because this is the default selected button

	buttonTexts[1] = std::make_unique<Text>(gameFont);
	buttonTexts[1]->setFont(gameFont);
	buttonTexts[1]->setString("Quit");
	buttonTexts[1]->setCharacterSize(100);
	buttonTexts[1]->setPosition({ 865.f, 580.f });

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

		if (event->is<Event::KeyPressed>())
		{
			const auto& keyEvent = event->getIf<Event::KeyPressed>();

			if (keyEvent->code == Keyboard::Key::W || keyEvent->code == Keyboard::Key::Up)
			{
				selectedButtonIndex = (selectedButtonIndex - 1 + 2) % 2; // Wrap around
				SwitchSelectedButton();
			}
			else if (keyEvent->code == Keyboard::Key::S || keyEvent->code == Keyboard::Key::Down)
			{
				selectedButtonIndex = (selectedButtonIndex + 1) % 2; // Wrap around
				SwitchSelectedButton();
			}
			else if (keyEvent->code == Keyboard::Key::Enter)
			{
				SelectedButtonPressed(window);
			}
		}
	}
}

void PongMenuState::Update()
{

}

void PongMenuState::Render(RenderWindow& window)
{
	window.clear();
	window.draw(*titleText);
	window.draw(*buttonTexts[0]);
	window.draw(*buttonTexts[1]);
	window.display();
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
	stateManager->PushState(std::make_unique<PongState>());
}

void PongMenuState::QuitGame(RenderWindow& window)
{
	window.close();
}