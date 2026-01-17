#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	//Utility
	explicit GameObject(const Texture& texture);
	~GameObject() = default;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Setters/Getters
	void SetSprite(const Texture& texture);
	Sprite& GetSprite();

	void SetVelocity(const Vector2f& vel);
	Vector2f& GetVelocity();

	void SetSize(const sf::Vector2f& sz);
	Vector2f& GetSize();

private:
	Sprite sprite;

	Vector2f velocity{ 0.f, 0.f };

	Vector2f size{ 0.f, 0.f };
};

