#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//-------------------------------------------------------------------------------------------------------------//
// NOTE: GameObject is a base class for all objects in the game that have a visual representation and can move.//
// It encapsulates a sprite and provides functionality for rendering, collision detection, and movement.       //
// All of my functions for this engine will use a capitalized first letter, SFML native functions use camelCase//
//-------------------------------------------------------------------------------------------------------------//

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	//Utility
	explicit GameObject(const Texture& texture);
	~GameObject() = default;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //override draw function from sf::Drawable

	sf::FloatRect GetGlobalBounds() const;

	bool Intersects(const GameObject& other) const;

	//Setters/Getters
	void SetSprite(const Texture& texture);
	Sprite& GetSprite();

	void SetVelocity(const Vector2f& vel);
	Vector2f& GetVelocity();

private:
	Sprite sprite;

	Vector2f velocity{ 0.f, 0.f };
};

