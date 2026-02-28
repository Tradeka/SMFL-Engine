#include "Tile.h"

Tile::Tile(const sf::IntRect& textureRect, const sf::Texture& texture)
	: sprite(texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
}

const sf::Sprite& Tile::GetSprite() const
{
    return sprite;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}