#include "Classes/Derived/States/PlatformerState.h"
#include <iostream>

PlatformerState::PlatformerState() :
	playerIdle("Assets/SpriteSheets/player_idle.png"),
	player(playerIdle),
	tilemapSheet("Assets/SpriteSheets/world_tileset.png"),
	tilemap(tilemapSheet, Vector2i(16, 16), Vector2i(20, 12))
{
	if(tilemapSheet.loadFromFile("Assets/SpriteSheets/world_tileset.png"))
	{
		std::vector<std::vector<int>> design = {
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176,   0,   0,   0, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{   0,   0,   0,   0,   0,   0,   0, 176, 176,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
			{  16,  16,  16,  16,  16,  16,  16, 176, 176,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16},
			{  16,  16,  16,  16,  16,  16,  16, 176, 176,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16},
			{  16,  16,  16,  16,  16,  16,  16, 176, 176,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16}
		};
		tilemap.SetDesignVector(design);

		std::vector<std::vector<int>> collision = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		tilemap.SetCollisionVector(collision);
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

	camera.setSize({ 1920.f, 1080.f });
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

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		player.setScale({ -3.f, 3.f }); //Flip sprite when moving left
		player.SetVelocity({ -2.f, player.GetVelocity().y }); //Move left

		if (playerGrounded) //Only switch to walk animation if player is on the ground, prevents walking animation from playing in the air
			playerAnim.SwitchCurrent("walk"); //Switch to walk animation
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		player.setScale({ 3.f, 3.f }); //Normal scale when moving right
		player.SetVelocity({ 2.f, player.GetVelocity().y }); //Move right

		if(playerGrounded)
			playerAnim.SwitchCurrent("walk"); //Switch to walk animation
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Key::A) && !Keyboard::isKeyPressed(Keyboard::Key::D) && !Keyboard::isKeyPressed(Keyboard::Key::Space))
	{
		player.SetVelocity({ 0.f, player.GetVelocity().y }); //Stop horizontal movement when no left/right input
		if (playerGrounded)
			playerAnim.SwitchCurrent("idle"); //Switch to idle animation when not moving left or right
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && playerGrounded)
	{
		playerAnim.SwitchCurrent("jump"); //Switch to jump animation
		player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y - 10.f }); //Apply an instant upward velocity for jumping)
		playerGrounded = false; //Set grounded to false when jumping, will be set to true again when colliding with tilemap
	}
}

void PlatformerState::Update()
{
	if (!playerGrounded)
	{
		ApplyGravity(player, 0.2f); //Apply gravity to the player
	}

	if(tilemap.CheckTileMapCollision(player)) //Check for collisions with the tilemap
	{
		Vector2f playerPos = player.getPosition();
		Vector2f playerSize = player.GetGlobalBounds().size; 

		Vector2i tileSize = tilemap.GetTileSize(); 
		Vector2f mapScale = tilemap.getScale();    

		//Compute the tile the player's bottom center is over
		int tileX = static_cast<int>((playerPos.x + playerSize.x / 2.f) / (tileSize.x * mapScale.x));
		int tileY = static_cast<int>((playerPos.y + playerSize.y) / (tileSize.y * mapScale.y));

		float tileTop = tileY * tileSize.y * mapScale.y;
		player.setPosition({ playerPos.x, tileTop - playerSize.y });
		player.SetVelocity({ player.GetVelocity().x, 0.f });
		playerGrounded = true;
	}
	else
	{
		playerGrounded = false; //Set grounded to false if not colliding with tilemap
	}

	camera.setCenter(player.getPosition()); //Set camera to follow player
	player.move(player.GetVelocity()); //Move player based on velocity
}

void PlatformerState::Render(RenderWindow& window)
{
	window.clear();
	window.draw(tilemap);
	window.draw(player);
	window.setView(camera);
	window.display();
}

//Game Specific Utility Functions

void PlatformerState::ApplyGravity(GameObject& obj, float gravity)
{
	obj.SetVelocity({ obj.GetVelocity().x, obj.GetVelocity().y + gravity }); //Add gravity to the object's velocity
}