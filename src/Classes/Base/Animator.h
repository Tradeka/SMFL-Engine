#pragma once
#include "Classes/Base/Animation.h"
#include "unordered_map"

//------------------------------------------------------------------------------------------------//
//Class for managing multiple animations for a GameObject. This will contain a map of animations  //
//and a pointer to the current animation. It will have functions to add animations, switch the    //
//current animation, and play the current animation.                                              //
//------------------------------------------------------------------------------------------------//

class Animator
{
public:
	Animator();
	void AddAnimation(Animation anim, std::string name);
	void PlayCurrent();
	void SwitchCurrent(std::string animName);
	Sprite* GetCurrentSprite();
	Animation* GetCurrent();
private:
	std::unordered_map<std::string, Animation> animations;
	std::string currentName;
};
