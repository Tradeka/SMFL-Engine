#include "SFML/Graphics.hpp"
#include "GameObject.h"

//Constructor/Destructor
GameObject::GameObject(const Texture& texture)
    : sprite(texture)
{
	SetSprite(texture);
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.size / 2.f);
	SetSize({ bounds.size});
}

//Utility
void GameObject::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

//Setters/Getters
void GameObject::SetSprite(const Texture& texture)
{
    sprite.setTexture(texture);
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

void GameObject::SetSize(const sf::Vector2f& sz)
{
    size = sz;
}

Vector2f& GameObject::GetSize()
{
    return size;
}

