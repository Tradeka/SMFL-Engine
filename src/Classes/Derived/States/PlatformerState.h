#pragma once
#include "Classes/Base/GameState.h"
#include "Classes/Base/Tilemap.h"
#include "Classes/Base/GameObject.h"
#include "Classes/Base/Animator.h"

class PlatformerState : public GameState
{
public:
	PlatformerState();
	~PlatformerState() override = default;
	void HandleInput(RenderWindow& window) override;
	void Update() override;
	void Render(RenderWindow& window) override;

private:

	//Player stuff
	GameObject player;
	Animator playerAnim;
	Texture playerIdle;
	Texture playerWalk;
	Texture playerJump;

	//Tilemap
	Texture tilemapSheet;
	Tilemap tilemap;
	

};