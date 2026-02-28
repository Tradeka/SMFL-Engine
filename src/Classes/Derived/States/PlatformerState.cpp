#include "Classes/Derived/States/PlatformerState.h"

PlatformerState::PlatformerState() :
	tilemapSheet("Assets/SpriteSheets/world_tileset.png"),
	tilemap(tilemapSheet, Vector2i(16, 16), Vector2i(20, 12)),
	playerIdle("Assets/SpriteSheets/player_idle.png"),
	player(playerIdle)
{
	if(tilemapSheet.loadFromFile("Assets/SpriteSheets/world_tileset.png"))
	{
		//Initialize tilemap design vector
		std::vector<std::vector<int>> design = {
			{176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176, 176 ,176 ,176 ,176 ,176 ,176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176, 176 ,176 ,176 ,176 ,176 ,176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176, 176 ,176 ,176 ,176 ,176 ,176 ,176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{176, 176, 176 ,176 ,176 ,176 ,176 ,176 ,176 ,176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 },
			{16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 },
			{16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 }
		};
		tilemap.SetDesignVector(design);
	}

	//Initialize player and animations

	//Setup animated object (Example)
	if (playerIdle.loadFromFile("Assets/SpriteSheets/player_idle.png"))  //1. Load the sprite sheet texture
	{
		auto anim = std::make_shared<Animation>(playerIdle, Vector2i{ 32,32 }, 4); //2. Create an animation with the texture, specifying frame size and count
		anim->SetLooping(true); //3. Set the animation to loop (optional)
		playerAnim.AddAnimation(*anim, "idle"); //4. Add the animation to the animator with a name
		playerAnim.SwitchCurrent("idle"); //5. Set the animation to current if you want it to be the default state
	}
	player.SetAnimator(&playerAnim); //6. Give the animated object a pointer to its animator

	if (playerWalk.loadFromFile("Assets/SpriteSheets/player_walk.png")) //7. Load another animation texture (optional)
	{
		auto walkAnim = std::make_shared<Animation>(playerWalk, Vector2i{ 32,32 }, 6);
		walkAnim->SetLooping(true);
		playerAnim.AddAnimation(*walkAnim, "walk");
	}

	if (playerJump.loadFromFile("Assets/SpriteSheets/player_jump.png")) //8. Load another animation texture (optional)
	{
		auto jumpAnim = std::make_shared<Animation>(playerJump, Vector2i{ 32,32 }, 8);
		jumpAnim->SetLooping(false); //Set to not loop for a jump animation
		playerAnim.AddAnimation(*jumpAnim, "jump");
	}

	player.setPosition({ 100.f, 100.f });
	player.setScale({ 3.f, 3.f });

	tilemap.setScale({ 6.f, 6.f });
}

void PlatformerState::HandleInput(RenderWindow& window)
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<Event::Closed>())
		{
			window.close();
		}
	}
}

void PlatformerState::Update()
{
	
}

void PlatformerState::Render(RenderWindow& window)
{
	window.clear();
	window.draw(tilemap);
	window.draw(player);
	window.display();
}