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

	//Game Specific Utility
	void ApplyGravity(GameObject& obj, float gravity);

private:

	//Player stuff
	GameObject player;
	Animator playerAnim;
	Texture playerIdle;
	Texture playerWalk;
	Texture playerJump;
	Texture playerRun;

	//Tilemap
	Texture tilemapSheet;
	Tilemap tilemap;

	//Other
	bool playerGrounded = false; //Variable to track if the player is on the ground, allowing them to jump again after jumping

	//Camera
	View camera;
	

};