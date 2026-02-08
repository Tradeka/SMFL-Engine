#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//------------------------------------------------------------------------------------------------//
//Class for individual animations. This will contain a sprite sheet and a Play function           //
//There will be an animation state machine to control which animation is playing for a GameObject //
//------------------------------------------------------------------------------------------------//

class Animation : public sf::Drawable
{
public:

	explicit Animation(const Texture& spriteSheet, Vector2i spriteSize, unsigned int frameCount);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //override draw function from sf::Drawable

	//Utility
	void Play();

	void SetLooping(bool isLooping);

	void SetFrameDuration(float duration);

	Sprite& GetSprite();

private:
	IntRect currentFrame;
	Texture sheet;
	Sprite displayedSprite;
	Clock clock;
	unsigned int frameCount;
	unsigned int currentFrameIndex;
	Vector2i spriteSize;
	bool looping;
	float frameDuration;
};