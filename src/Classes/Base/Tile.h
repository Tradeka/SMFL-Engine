#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//--------------------------------------------------------------------------------//
// Tile class, contains sprite to be drawn, and tile size for collision detection //
//--------------------------------------------------------------------------------//

class Tile : public Drawable, public Transformable
{
public:
    Tile(const sf::IntRect& textureRect, const sf::Texture& texture);

    const sf::Sprite& GetSprite() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetCollidable(bool collidable) { isCollidable = collidable; }
	bool IsCollidable() const { return isCollidable; }

private:
    sf::Sprite sprite;
    bool isCollidable; 
};