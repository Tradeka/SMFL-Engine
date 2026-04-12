#pragma once
#include <SFML/Graphics.hpp>
#include "Classes/Base/Animator.h"

using namespace sf;

//-------------------------------------------------------------------------------------------------------------//
// NOTE: GameObject is a base class for all objects in the game that have a visual representation and can move.//
// It encapsulates a sprite and provides functionality for rendering, collision detection, and movement.       //
// All of my functions for this engine will use a capitalized first letter, SFML native functions use camelCase//
// Gameobject can be instantiated directly, but can also be inherited from for more specific object types      //
//-------------------------------------------------------------------------------------------------------------//

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	//Utility
	explicit GameObject(const Texture& texture);
	~GameObject() = default;

	void draw(RenderTarget& target, RenderStates states) const override; //override draw function from sf::Drawable

	FloatRect GetGlobalBounds() const;

	void SetGlobalBounds(const FloatRect& newBounds);

	bool Intersects(const GameObject& other) const;

	float GetAngleTo(const GameObject& other) const; //Get the angle from this GameObject to another GameObject in degrees, where 0 is to the right and positive angles are counterclockwise

	float GetDistanceTo(const GameObject& other) const; //Get the distance from this GameObject to another GameObject

	void DrawDebugBounds(RenderTarget& target) const;

	void SyncSpriteTransform(Sprite& sprite) const; //Utility function to sync the transform of the sprite with the transform of the GameObject, used for animators

	//Setters/Getters
	void SetSprite(const Texture& texture);
	Sprite& GetSprite();

	void SetVelocity(const Vector2f& vel);
	Vector2f& GetVelocity();

	void SetAnimator(Animator* anim);

private:
	Sprite sprite;

	Vector2f velocity{ 0.f, 0.f };

	Animator* animator = nullptr; //pointer to an animator, if the GameObject has one. This is used for animation state machines in derived classes
};

