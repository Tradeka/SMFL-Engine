#pragma once
#include "Classes/Base/Animation.h"
#include "unordered_map"

class Animator
{
public:
	Animator();
	void AddAnimation(Animation anim);
	void PlayCurrent();
	void SwitchCurrent(String animName);
private:
	//std::unordered_map<String, Animation> animations;
	Animation* current = nullptr;
};
