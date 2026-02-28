#include "Classes/Base/Tilemap.h"
#include <iostream>

Tilemap::Tilemap(const Texture& spriteSheet, Vector2i tileS, Vector2i mapS) : tileSize(tileS), mapSize(mapS) 
{
	//Initialize the idMap
    int tilesX = spriteSheet.getSize().x / tileSize.x;
    int tilesY = spriteSheet.getSize().y / tileSize.y;

    int id = 0;
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            sf::IntRect rect(
                { x * tileSize.x,
                y * tileSize.y },
                { tileSize.x,
                tileSize.y }
            );

            idMap.emplace(id++, Tile(rect, spriteSheet));
        }
    }
}

void Tilemap::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform(); // Apply the transform of the tilemap
    for (size_t y = 0; y < designVector.size(); y++)
    {
        for (size_t x = 0; x < designVector[y].size(); x++)
        {
            int tileID = designVector[y][x];

            auto it = idMap.find(tileID);
            if (it == idMap.end())
                continue;

            // Copy the sprite so we can move it
            Sprite sprite = it->second.GetSprite(); // or expose sprite access
            sprite.setPosition(
                { static_cast<float>(x * tileSize.x),
                static_cast<float>(y * tileSize.y) }
            );

            target.draw(sprite, states);
        }
    }
}

void Tilemap::SetDesignVector(const std::vector<std::vector<int>>& design)
{
	designVector = design;
}