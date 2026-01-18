#include "SFML/Graphics.hpp"
#include "GameObject.h"

//Constructor/Destructor
GameObject::GameObject(const Texture& texture)
    : sprite(texture)
{
	SetSprite(texture);
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
}

//Utility
void GameObject::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

FloatRect GameObject::GetGlobalBounds() const //VERY IMPORTANT: This is necessary to get the transformed bounds of the sprite for accurate collision detection
{                                             //otherwise, only the untransformed local bounds would be returned and that causes janky collisions
    return getTransform().transformRect(sprite.getGlobalBounds());
}

bool GameObject::Intersects(const GameObject& other) const //Clean AABB collision detection using SFML's built-in function
{
    return (bool)GetGlobalBounds().findIntersection(other.GetGlobalBounds());
}

//Setters/Getters
void GameObject::SetSprite(const Texture& texture)
{
    sprite.setTexture(texture);
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
}

Sprite& GameObject::GetSprite()
{
    return sprite;
}

void GameObject::SetVelocity(const Vector2f& vel)
{
    velocity = vel;
}

Vector2f& GameObject::GetVelocity()
{
    return velocity;
}

