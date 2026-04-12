#include "Classes/Derived/States/PlatformerState.h"
#include <iostream>

//Global Variables (if any)
bool isDashing = false;
bool yoyoReturning = false;

PlatformerState::PlatformerState() :
	playerIdle("Assets/SpriteSheets/player_idle.png"),
	player(playerIdle),
	tilemapSheet("Assets/SpriteSheets/world_tileset.png"),
	tilemap(tilemapSheet, Vector2i(16, 16), Vector2i(40, 12)),
	yoyoTexture("Assets/Textures/Ball.png")
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

	if (yoyoTexture.loadFromFile("Assets/Textures/Ball.png"))
	{
		// Yoyo texture loaded successfully
	}

	player.setPosition({ 100.f, 100.f });
	player.setScale({ 3.f, 3.f });

	tilemap.setScale({ 6.f, 6.f });

	camera.setSize({ 1920.f, 1080.f });

	gameClock.start();
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

	bool isSprinting = false;

	if (playerGrounded)
	{
		isSprinting = Keyboard::isKeyPressed(Keyboard::Key::LShift);
	}
	else
	{
		isSprinting = false; //No sprinting in-air, but you could allow it if you want
	}
	

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
			float groundAcceleration = 0.3f;

			velX += moveInput * groundAcceleration;
			float maxGroundSpeed = speed;
			velX = std::clamp(velX, -maxGroundSpeed, maxGroundSpeed);

			player.SetVelocity({ velX, player.GetVelocity().y });

			if (isSprinting)
				playerAnim.SwitchCurrent("run");
			else
				playerAnim.SwitchCurrent("walk");
		}
		else if(!playerGrounded)
		{
			//Air acceleration
			float velX = player.GetVelocity().x;
			float airAcceleration = 0.03f;

			velX += moveInput * airAcceleration; //Apply air acceleration, with a small deceleration to prevent infinite air acceleration when holding a direction

			player.SetVelocity({ velX, player.GetVelocity().y });
		}
	}
	else
	{
		if (playerGrounded)
		{
			if (moveInput == 0.f) //Decelerate player to a stop when no input is given
			{
				float decel = 0.2f;

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
	
	//DASH
	static Time lastFireTime = Time::Zero;
	static bool dashKeyWasPressed = false;
	float dashSpeed = 5.5f;
	float dashTime = 0.1f; //Duration of the dash in seconds

	Time currentTime = gameClock.getElapsedTime();

	bool canDash = (currentTime - lastFireTime).asSeconds() >= dashTime && !playerGrounded;

	bool dashKeyPressed = Keyboard::isKeyPressed(Keyboard::Key::C);
	bool dashJustPressed = dashKeyPressed && !dashKeyWasPressed;

	Vector2i dashDirection = { (int)moveInput, (int)dashDirInput };

	if (dashJustPressed && canDash)
	{
		isDashing = true;
		if(dashDirection == Vector2i{0,0}) //If no direction is pressed, dash in the direction the player is facing
		{
			dashDirection.x = player.getScale().x > 0 ? 1 : -1; //Dash right if facing right, left if facing left
		}
		else if (dashDirection.x != 0 && dashDirection.y == 0)
		{
			dashSpeed *= 1.3; //Increase speed for horizontal dashes
		}
		
		player.SetVelocity({ dashDirection.x * dashSpeed, dashDirection.y * dashSpeed });
		lastFireTime = currentTime;
		
	}

	if((currentTime - lastFireTime).asSeconds() >= dashTime) //End dash (this is tracked so gravity can be turned off during the dash)
	{
		isDashing = false;
	}

	dashKeyWasPressed = dashKeyPressed;

	//JUMP
	bool jumpBuffered = false;
	float jumpBufferTime = 10.f; //Time window to allow buffered jumps in seconds

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !playerGrounded)
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
		}
	}

	//YOYO THROW (YO)
	static bool fKeyWasPressed = false;
	bool fKeyPressed = Keyboard::isKeyPressed(Keyboard::Key::F);
	bool fJustPressed = fKeyPressed && !fKeyWasPressed;
	
	if (fJustPressed && currentYoyo == nullptr)
	{
		auto yoyo = std::make_shared<GameObject>(yoyoTexture);

		yoyo->setPosition(player.getPosition());
		yoyo->setScale({ 0.25f, 0.25f });

		Vector2f vel = { player.getScale().x * 1.5f, 0.f };
		yoyo->SetVelocity(vel);

		tempObjects.push_back(yoyo);
		currentYoyo = yoyo;

		yoyoFiredTime = currentTime;
	}
	fKeyWasPressed = fKeyPressed;

	if (currentYoyo && (currentTime - yoyoFiredTime).asSeconds() >= 0.5f)
	{
		if (fKeyPressed)
		{
			currentYoyo->SetVelocity({ 0,0 }); //Stop yoyo movement while holding the key
		}
		else
		{
			yoyoReturning = true;
			Vector2f returnDir = player.getPosition() - currentYoyo->getPosition();
			float length = std::sqrt(returnDir.x * returnDir.x + returnDir.y * returnDir.y);
			if (length != 0)
			{
				returnDir /= length; //Normalize the return direction
				currentYoyo->SetVelocity(returnDir * 3.f); //Set velocity towards the player
			}
		}
	}

	if(yoyoReturning && currentYoyo->GetDistanceTo(player) < 10.f) //If the yoyo is close enough to the player, remove it
	{
		tempObjects.erase(
			std::remove(tempObjects.begin(), tempObjects.end(), currentYoyo),
			tempObjects.end()
		);

		currentYoyo = nullptr;
		yoyoReturning = false;
	}
}

void PlatformerState::Update()
{
	if(!isDashing)
		ApplyGravity(player, 0.155f); //Apply gravity to the player

	Vector2f playerSize = player.GetGlobalBounds().size;
	float halfHeight = playerSize.y / 2.f;

	Vector2f belowPlayerPos = {
		player.getPosition().x,
		player.getPosition().y + halfHeight + 1.f //small buffer
	};
	

	bool isColliding = tilemap.CheckTileMapCollision(player);
	bool isAboveTile = tilemap.CheckTileMapOverlap(belowPlayerPos);

	if (isColliding && isAboveTile)
	{
		Vector2f playerSize = player.GetGlobalBounds().size;

		Vector2i tileSize = tilemap.GetTileSize();
		Vector2f mapScale = tilemap.getScale();

		float halfHeight = playerSize.y / 2.f;

		float playerBottom = player.getPosition().y + halfHeight;

		int tileX = static_cast<int>(player.getPosition().x / (tileSize.x * mapScale.x));
		int tileY = static_cast<int>(playerBottom / (tileSize.y * mapScale.y));

		float tileTop = tileY * tileSize.y * mapScale.y;

		if (player.GetVelocity().y >= 0)
		{
			player.setPosition({ player.getPosition().x, tileTop - halfHeight });
			player.SetVelocity({ player.GetVelocity().x, 0.f });
		}
	}
	
	//Ground check cast
	if (tilemap.CheckTileMapOverlap(belowPlayerPos) && player.GetVelocity().y >= 0)
	{
		playerGrounded = true;
	}
	else
	{
		playerGrounded = false;
	}


	camera.setCenter(player.getPosition()); //Set camera to follow player
	player.move(player.GetVelocity()); //Move player based on velocity

	for (auto& obj : tempObjects)
	{
		obj->move(obj->GetVelocity());
	}
}

void PlatformerState::Render(RenderWindow& window)
{
	window.clear(Color(20, 152, 220)); //YOU CAN CHANGE BACKGROUND COLOR LIKE THIS (This matches the sky tiles I'm using)
	window.draw(tilemap);
	window.draw(player);
	for (auto& obj : tempObjects)
	{
		window.draw(*obj);
	}
	window.setView(camera);
	window.display();
}

//Game Specific Utility Functions

void PlatformerState::ApplyGravity(GameObject& obj, float gravity)
{
	obj.SetVelocity({ obj.GetVelocity().x, obj.GetVelocity().y + gravity }); //Add gravity to the object's velocity
}