#include "Classes/Base/Animator.h"

Animator::Animator()
{

}

void Animator::AddAnimation(Animation anim, std::string name)
{
	animations.insert({ name, anim });
}

void Animator::PlayCurrent()
{
	if (!GetCurrent())
		return;

	GetCurrent()->Play();
}

void Animator::SwitchCurrent(std::string animName)
{
	auto it = animations.find(animName);
	if (it != animations.end())
	{
		currentName = animName;
	}
}

Sprite* Animator::GetCurrentSprite()
{
	Animation* anim = GetCurrent();
	return anim ? &anim->GetSprite() : nullptr;
}

Animation* Animator::GetCurrent()
{
	auto it = animations.find(currentName);
	if (it != animations.end())
	{
		return &it->second;
	}
	return nullptr;
}