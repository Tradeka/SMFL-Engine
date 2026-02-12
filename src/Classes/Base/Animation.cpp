#include "Classes/Base/Animation.h"

Animation::Animation(const Texture& spriteSheet, Vector2i spriteSize, unsigned int frameCount)
	:displayedSprite(spriteSheet)
{
	this->frameCount = frameCount;
	this->spriteSize = spriteSize;

    looping = false;
    frameDuration = 0.167f;

	currentFrame = IntRect({ 0,0 }, {spriteSize.x, spriteSize.y});
	currentFrameIndex = 0;
	displayedSprite = Sprite(spriteSheet, currentFrame);
}

void Animation::Play()
{
    if (clock.getElapsedTime().asSeconds() >= frameDuration)
    {
        currentFrameIndex++;

        if (currentFrameIndex >= frameCount)
        {
            if (looping)
                currentFrameIndex = 0;
            else
                currentFrameIndex = frameCount - 1;
        }

        currentFrame.position.x = currentFrameIndex * spriteSize.x;
        currentFrame.position.y = 0;

        displayedSprite.setTextureRect(currentFrame);
        clock.restart();
    }
}

void Animation::SetFrameDuration(float duration)
{
    frameDuration = duration;
}

void Animation::SetLooping(bool isLooping)
{
    looping = isLooping;
}

void Animation::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(displayedSprite, states);
}

Sprite& Animation::GetSprite()
{
    return displayedSprite;
}

