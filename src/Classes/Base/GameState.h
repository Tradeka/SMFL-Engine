#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Classes/Base/GameObject.h"

//----------------------------------------------------------------------//
//Abstract base class for different game states                         //
//This class will never be instantiated directly                        //
//Contains pure virtual functions for updating and drawing to the screen//
//----------------------------------------------------------------------//

class GameState
{
private:
	std::vector<GameObject*> gameObjects; //Container for all game objects in the state
public:
	virtual ~GameState() = default;
	//Pure virtual functions to be implemented by derived classes
	virtual void Update() = 0;
	virtual void DrawObjects(RenderWindow& window) = 0;
	//Function to add a game object to the state
	void AddGameObject(GameObject* obj)
	{
		gameObjects.push_back(obj);
	}
	//Function to get all game objects in the state
	const std::vector<GameObject*>& GetGameObjects() const
	{
		return gameObjects;
	}
};
