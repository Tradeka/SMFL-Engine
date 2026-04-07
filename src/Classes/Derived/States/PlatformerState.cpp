#include "Classes/Derived/States/PlatformerState.h"
#include <iostream>

PlatformerState::PlatformerState() :
	playerIdle("Assets/SpriteSheets/player_idle.png"),
	player(playerIdle),
	tilemapSheet("Assets/SpriteSheets/world_tileset.png"),
	tilemap(tilemapSheet, Vector2i(16, 16), Vector2i(40, 12))
{
	if(tilemapSheet.loadFromFile("Assets/SpriteSheets/world_tileset.png"))
	{
		std::vector<std::vector<int>> design = {
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176,   0,   0,   0, 176, 176,   0,   0,   0, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{ 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176},
			{   0,   0,   0,   0,   0,   0,   0, 176, 176, 176, 176, 176, 176, 176,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
			{  16,  16,  16,  16,  16,  16,  16, 150, 150, 150, 150, 150, 150, 150,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16},
			{  16,  16,  16,  16,  16,  16,  16, 166, 166, 166, 166, 166, 166, 166,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16},
			{  16,  16,  16,  16,  16,  16,  16, 166, 166, 166, 166, 166, 166, 166,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16},
			{  16,  16,  16,  16,  16,  16,  16, 166, 166, 166, 166, 166, 166, 166,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16}
		};
		tilemap.SetDesignVector(design);

		std::vector<std::vector<int>> collision = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
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

	if(playerRun.loadFromFile("Assets/SpriteSheets/player_run.png"))
	{
		auto runAnim = std::make_shared<Animation>(playerRun, Vector2i{ 32,32 }, 6);
		runAnim->SetLooping(true);
		playerAnim.AddAnimation(*runAnim, "run");
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

	float moveInput = 0.f;
	float dashDirInput = 0.f;

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		moveInput -= 1.f;

	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		moveInput += 1.f;

	if(Keyboard::isKeyPressed(Keyboard::Key::W))
		dashDirInput -= 1.f;

	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		dashDirInput += 1.f;

	bool isSprinting = Keyboard::isKeyPressed(Keyboard::Key::LShift);

	//Speeds
	float walkSpeed = 3.f;
	float sprintSpeed = 5.f;

	//Choose speed
	float speed = isSprinting ? sprintSpeed : walkSpeed;

	//Apply movement
	if (moveInput != 0.f)
	{
		player.setScale({ moveInput < 0 ? -3.f : 3.f, 3.f });

		if (playerGrounded)
		{
			//Ground acceleration
			float velX = player.GetVelocity().x;
			float groundAcceleration = 0.5f;

			velX += moveInput * groundAcceleration;
			float maxGroundSpeed = speed;
			velX = std::clamp(velX, -maxGroundSpeed, maxGroundSpeed);

			player.SetVelocity({ velX, player.GetVelocity().y });

			if (isSprinting)
				playerAnim.SwitchCurrent("run");
			else
				playerAnim.SwitchCurrent("walk");
		}
		else
		{
			//Air acceleration
			float velX = player.GetVelocity().x;
			float airAcceleration = 0.2f;

			velX += moveInput * airAcceleration;

			float maxAirSpeed = speed;
			velX = std::clamp(velX, -maxAirSpeed, maxAirSpeed);

			player.SetVelocity({ velX, player.GetVelocity().y });
		}
	}
	else
	{
		if (playerGrounded)
		{
			if (moveInput == 0.f) //Decelerate player to a stop when no input is given
			{
				float decel = 0.25f;

				if(player.GetVelocity().x > 0.f)
				{
					decel = std::min(decel, player.GetVelocity().x);
				}
				else if(player.GetVelocity().x < 0.f)
				{
					decel = std::max(-decel, player.GetVelocity().x);
				}
				else
				{
					decel = 0.f;
				}
				float velX = player.GetVelocity().x - decel;
				player.SetVelocity({ velX, player.GetVelocity().y });
				playerAnim.SwitchCurrent("idle");
			}
		}
	}

	//JUMP
	bool jumpBuffered = false;

	if(Keyboard::isKeyPressed(Keyboard::Key::Space) && !playerGrounded)
	{
		jumpBuffered = true; //If space is pressed in-air, buffer jump input
	}

	if (playerGrounded)
	{
		if (jumpBuffered || Keyboard::isKeyPressed(Keyboard::Key::Space)) //Jump if space is pressed or if jump was buffered while in-air
		{
			jumpBuffered = false; //reset jump buffer
			playerAnim.SwitchCurrent("jump"); //Switch to jump animation
			player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y - 10.f }); //Apply an instant upward velocity for jumping)
			playerGrounded = false; //Set grounded to false when jumping, will be set to true again when colliding with tilemap
		}
	}
	
	//DASH
	bool canDash = true; 
	float dashSpeed = 7.f;
	Vector2i dashDirection = { static_cast<int>(moveInput), static_cast<int>(dashDirInput)};

	if(Keyboard::isKeyPressed(Keyboard::Key::C) && canDash && !playerGrounded)
	{
		canDash = false; //Set canDash to false to prevent multiple dashes
		player.SetVelocity({ dashDirection.x * dashSpeed, dashDirection.y * dashSpeed }); //Set velocity in the direction of input for dashing
	}
}

void PlatformerState::Update()
{
	if (!playerGrounded)
	{
		ApplyGravity(player, 0.19f); //Apply gravity to the player
	}

	if(tilemap.CheckTileMapCollision(player) && player.GetVelocity().y > 0) //Check for collisions with the tilemap
	{
		Vector2f playerSize = player.GetGlobalBounds().size;

		Vector2i tileSize = tilemap.GetTileSize();
		Vector2f mapScale = tilemap.getScale();

		float halfHeight = playerSize.y / 2.f;

		// Bottom of player (since position is center now)
		float playerBottom = player.getPosition().y + halfHeight;

		// Compute tile under player's bottom center
		int tileX = static_cast<int>(player.getPosition().x / (tileSize.x * mapScale.x));
		int tileY = static_cast<int>(playerBottom / (tileSize.y * mapScale.y));

		float tileTop = tileY * tileSize.y * mapScale.y;

		// Snap so bottom of player sits on tile
		player.setPosition({ player.getPosition().x, tileTop - halfHeight});

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
	window.clear(Color(20, 152, 220)); //YOU CAN CHANGE BACKGROUND COLOR LIKE THIS (This matches the sky tiles I'm using)
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