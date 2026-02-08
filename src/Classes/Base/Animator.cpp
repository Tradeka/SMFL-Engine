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
	current->Play();
}

void Animator::SwitchCurrent(std::string animName)
{
	current = &animations.find(animName)->second;
}