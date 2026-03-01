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
    states.transform *= getTransform();

    // draw tiles
    for (size_t y = 0; y < designVector.size(); y++)
    {
        for (size_t x = 0; x < designVector[y].size(); x++)
        {
            int tileID = designVector[y][x];
            auto it = idMap.find(tileID);
            if (it == idMap.end())
                continue;

            sf::Sprite sprite = it->second.GetSprite();
            sprite.setPosition(
                {(float) x * tileSize.x, (float) y * tileSize.y }
            );

            target.draw(sprite, states);
        }
    }
}

void Tilemap::SetDesignVector(const std::vector<std::vector<int>>& design)
{
	designVector = design;
}

void Tilemap::SetCollisionVector(const std::vector<std::vector<int>>& collision)
{
    collisionVector = collision;

    collisionRects.clear();
    collisionRects.resize(mapSize.y, std::vector<FloatRect>(mapSize.x));

    for (int y = 0; y < mapSize.y; y++)
    {
        for (int x = 0; x < mapSize.x; x++)
        {
            collisionRects[y][x] = FloatRect(
                { (float)x * (float)tileSize.x,
                (float)y * (float)tileSize.y },
                { (float)tileSize.x,
                (float)tileSize.y }
            );
        }
    }
}

bool Tilemap::CheckTileMapCollision(GameObject& obj)
{
    sf::FloatRect objBounds = obj.GetGlobalBounds();

    sf::Vector2f mapPos = getPosition();
    sf::Vector2f mapScale = getScale();

    for (int y = 0; y < mapSize.y; y++)
    {
        for (int x = 0; x < mapSize.x; x++)
        {
            if (collisionVector[y][x] != 1)
                continue;

            sf::Vector2f tilePos(
                mapPos.x + x * tileSize.x * mapScale.x,
                mapPos.y + y * tileSize.y * mapScale.y
            );

            sf::Vector2f tileSizeScaled(
                tileSize.x * mapScale.x,
                tileSize.y * mapScale.y
            );

            sf::FloatRect tileRect(tilePos, tileSizeScaled);

            if (tileRect.findIntersection(objBounds))
                return true;
        }
    }

    return false;
}