#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//------------------------------------------------------------------------------------------------//
//Class for individual animations. This will contain a sprite sheet and a Play function           //
//There will be an animation state machine to control which animation is playing for a GameObject //
//------------------------------------------------------------------------------------------------//

class Animation
{
public:

	explicit Animation(const Texture& spriteSheet, Vector2i spriteSize);

	//Utility
	void Play(bool looping, float framerate);

private:
	IntRect currentFrame;
	Texture sheet;
	Sprite displayedSprite;
	Clock clock;
};