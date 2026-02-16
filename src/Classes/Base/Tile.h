#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//--------------------------------------------------------------------------------//
// Tile class, contains sprite to be drawn, and tile size for collision detection //
//--------------------------------------------------------------------------------//

class Tile : public Drawable
{
public:

	Tile(const Vector2f& position, const Vector2f& size, const Texture& texture);

	void draw(RenderTarget& target, RenderStates states) const override;

private:
	Sprite sprite;
	Vector2i tileSize;

};