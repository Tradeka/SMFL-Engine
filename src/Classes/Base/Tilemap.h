#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <unordered_map>

using namespace sf;

//-----------------------------------------------------------------------------------------//
// Tilemap class. Given a sprite sheet it will divide it into individual tile sprites      //
// based on a specified tile size, and store them in an unordered map with integer IDs.    //
// The tilemap can then be drawn using a 2D vector of tile IDs for level design.           //
//-----------------------------------------------------------------------------------------//

class Tilemap : public Drawable, public Transformable
{
public:
	explicit Tilemap(const Texture& spriteSheet, Vector2i tileS, Vector2i mapS);
	void draw(RenderTarget& target, RenderStates states) const override;
	void SetDesignVector(const std::vector<std::vector<int>>& design);

private:
	std::unordered_map<int, Tile> idMap; //Map of tile IDs to allow for a 2D array of tile IDs to be used for level design
	Vector2i tileSize;
	Vector2i mapSize;
	std::vector<std::vector<int>> designVector; //2D vector of tiles for level design

};