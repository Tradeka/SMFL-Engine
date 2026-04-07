#include "SFML/Graphics.hpp"
#include "Classes/Base/GameObject.h"

//Constructor/Destructor
GameObject::GameObject(const Texture& texture)
    : sprite(texture)
{
	SetSprite(texture);
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
}

//Utility
void GameObject::draw(RenderTarget& target, RenderStates states) const
{
    if (animator)
    {
        if (Sprite* sprite = animator->GetCurrentSprite())
        {
			SyncSpriteTransform(*sprite); //Sync the sprite transform with GameObject transform before drawing
            target.draw(*sprite);
            animator->PlayCurrent();
        }
        return;
    }
    else
    {
		states.transform *= getTransform(); //Apply GameObject transform to render states
        auto sprite = this->sprite; //Make a copy of the sprite to modify its transform without affecting the original
        SyncSpriteTransform(sprite);
        target.draw(sprite);
    }
   
}


sf::FloatRect GameObject::GetGlobalBounds() const
{
    const sf::Sprite* s = &sprite;

    if (animator)
    {
        if (sf::Sprite* animSprite = animator->GetCurrentSprite())
            s = animSprite;
    }

    sf::FloatRect local = s->getLocalBounds();
    sf::Vector2f origin = s->getOrigin();

    // Adjust position instead of left/top
    local.position -= origin;

    return getTransform().transformRect(local);
}


bool GameObject::Intersects(const GameObject& other) const //Clean AABB collision detection using SFML's built-in function
{
    return (bool)GetGlobalBounds().findIntersection(other.GetGlobalBounds());
}

void GameObject::DrawDebugBounds(sf::RenderTarget& target) const
{
    sf::FloatRect bounds = GetGlobalBounds();

    sf::RectangleShape rect;
    rect.setPosition(bounds.position);
    rect.setSize(bounds.size);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2.f);

    target.draw(rect);
}

void GameObject::SyncSpriteTransform(Sprite& sprite) const
{
    sprite.setPosition(getPosition());
    sprite.setScale(getScale());
    sprite.setRotation(getRotation());
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

void GameObject::SetAnimator(Animator* anim)
{
    animator = anim;
}

