#include "PongState.h"
#include <iostream>
#include <algorithm>

PongState::PongState()
    : ballTexture("Assets/Textures/ball.png"),
    paddleTexture("Assets/Textures/paddle.png"),
    gateTexture("Assets/Textures/gate.png"),
    ball(ballTexture),           
    paddle1(paddleTexture),
    paddle2(paddleTexture),
    gate(gateTexture),
    gate2(gateTexture),
    gate3(gateTexture),
    player1Score(0),
    player2Score(0),
    baseBallSpeed(5.f),
    gen(rd()),
    distrib_float(0.f, 1.f),
    paddleHitBuffer("Assets/Sounds/paddleBounce.wav"),
    paddleHitSound(paddleHitBuffer),
	scoreSoundBuffer("Assets/Sounds/scoreSound.wav"),
	scoreSound(scoreSoundBuffer)
{
    //Ball setup
    ball.setPosition({ 960.f, 540.f });
    ball.scale({ 0.4f, 0.4f });

    //Paddle 1 setup
    paddle1.scale({ 1.f, 1.8f });
    paddle1.setPosition({ paddle1.GetGlobalBounds().size.x / 2.f, 540.f });

    //Paddle 2 setup
    paddle2.scale({ 1.f, 1.8f });
    paddle2.setPosition({ 1920.f - paddle2.GetGlobalBounds().size.x / 2.f, 540.f });

    //Gate setup
    gate.setPosition({ 960.f - gate.GetGlobalBounds().size.x / 2.f, 540.f - gate.GetGlobalBounds().size.y / 2.f - 25.f });
    gate.scale({ 0.75f, 1.f });

    gate2.setPosition({ 960.f - gate2.GetGlobalBounds().size.x / 2.f, 540.f - 25.f });
    gate2.setScale({ 0.75f, 1.f });

    gate3.setPosition({ 960.f - gate3.GetGlobalBounds().size.x / 2.f, 1080.f - gate3.GetGlobalBounds().size.y / 3.f - 25.f });
    gate3.scale({ 0.75f, 1.f });

    //Font and text setup
    if (!gameFont.openFromFile("Assets/Fonts/ByteBounce.ttf"))
    {
        std::cerr << "Failed to load font: Assets/Fonts/ByteBounce.ttf" << std::endl;
    }

    player1ScoreText = std::make_unique<Text>(gameFont);
    player2ScoreText = std::make_unique<Text>(gameFont);

    player1ScoreText->setFont(gameFont);
    player2ScoreText->setFont(gameFont);
    player1ScoreText->setPosition({ 1920.f / 4.f, 50.f });
    player2ScoreText->setPosition({ 1920.f / 4.f * 3.f, 50.f });
    player1ScoreText->setCharacterSize(100);
    player2ScoreText->setCharacterSize(100);
    player1ScoreText->setString("0");
    player2ScoreText->setString("0");

    
    if (!gameMusic.openFromFile("Assets/Sounds/retroArcadeMusic.mp3"))
    {
        std::cerr << "Failed to load music\n";
    }

    gameMusic.setLooping(true);
    gameMusic.play();
    
	paddleHitSound.setBuffer(paddleHitBuffer);
	scoreSound.setBuffer(scoreSoundBuffer);

    //Set initial ball velocity
    ResetBall();
}

void PongState::HandleInput(RenderWindow& window)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window.close();
        }
    }

    //Reset velocities
    paddle1.SetVelocity({ 0.f, 0.f });
    paddle2.SetVelocity({ 0.f, 0.f });

    //Paddle 1 controls (W/S)
    if (Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        paddle1.SetVelocity({ 0.f, -4.f });
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        paddle1.SetVelocity({ 0.f, 4.f });
    }

    //Paddle 2 controls (Up/Down)
    if (Keyboard::isKeyPressed(Keyboard::Key::Up))
    {
        paddle2.SetVelocity({ 0.f, -4.f });
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
    {
        paddle2.SetVelocity({ 0.f, 4.f });
    }
}

void PongState::Update() //Continuously update the object states
{
    //Move objects
    ball.move(ball.GetVelocity());
    paddle1.move(paddle1.GetVelocity());
    paddle2.move(paddle2.GetVelocity());

    //Check collisions
    CheckCollisions({ 1920u, 1080u });

    //Update score text
    player1ScoreText->setString(std::to_string(player1Score));
    player2ScoreText->setString(std::to_string(player2Score));
}

void PongState::Render(RenderWindow& window) //Render the objects
{
    window.clear();
    window.draw(gate);
    window.draw(gate2);
    window.draw(gate3);
    window.draw(ball);
    window.draw(paddle1);
    window.draw(paddle2);
    window.draw(*player1ScoreText);
    window.draw(*player2ScoreText);
    window.display();
}

void PongState::HandlePaddleBounce(GameObject& ball, GameObject& paddle, bool isLeftPaddle) //Function to handle the velocity of the ball bouncing off the paddle
{
	//Play sound
	paddleHitSound.play();

    float paddleHeight = paddle.GetGlobalBounds().size.y;
    float paddleHalfWidth = paddle.GetGlobalBounds().size.x / 2.f;
    float ballHalfWidth = ball.GetGlobalBounds().size.x / 2.f;

    //Compute normalized hit position
    float deltaY = ball.getPosition().y - paddle.getPosition().y;
    float normalized = std::clamp(deltaY / (paddleHeight / 2.f), -1.f, 1.f);

    //Keep speed constant
    Vector2f velocity = ball.GetVelocity();
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    velocity.x = std::abs(velocity.x);
    velocity.x = isLeftPaddle ? velocity.x : -velocity.x;
    velocity.y = normalized * speed;

    ball.SetVelocity(velocity);

    //Reposition ball outside paddle
    float newX = isLeftPaddle
        ? paddle.getPosition().x + paddleHalfWidth + ballHalfWidth
        : paddle.getPosition().x - paddleHalfWidth - ballHalfWidth;

    ball.setPosition({ newX, ball.getPosition().y });
}

void PongState::CheckCollisions(const Vector2u& windowSize) //Function for handling any collisions in game
{
    //Ball-wall collision (top/bottom)
    if (ball.getPosition().y < 0 + ball.GetGlobalBounds().size.y / 2.f)
    {
        ball.setPosition({ ball.getPosition().x, 0 + ball.GetGlobalBounds().size.y / 2.f });
        ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });
    }
    else if (ball.getPosition().y > windowSize.y - ball.GetGlobalBounds().size.y / 2.f)
    {
        ball.setPosition({ ball.getPosition().x, windowSize.y - ball.GetGlobalBounds().size.y / 2.f });
        ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });
    }

    //Ball-wall collision (left/right) - scoring
    if (ball.getPosition().x > windowSize.x - ball.GetGlobalBounds().size.x / 2.f)
    {
        //Play score sound
		scoreSound.play();

        player1Score++;
        ResetBall();
    }
    else if (ball.getPosition().x < 0 + ball.GetGlobalBounds().size.x / 2.f)
    {
		//Play score sound
		scoreSound.play();

        player2Score++;
        ResetBall();
    }

    //Paddle-wall collision (top/bottom)
    auto pos1 = paddle1.getPosition();
    float halfHeight1 = paddle1.GetGlobalBounds().size.y / 2.f;
    pos1.y = std::clamp(pos1.y, halfHeight1, (float)windowSize.y - halfHeight1);
    paddle1.setPosition(pos1);

    auto pos2 = paddle2.getPosition();
    float halfHeight2 = paddle2.GetGlobalBounds().size.y / 2.f;
    pos2.y = std::clamp(pos2.y, halfHeight2, (float)windowSize.y - halfHeight2);
    paddle2.setPosition(pos2);

    //Ball-paddle collision
    if (ball.Intersects(paddle1))
    {
        HandlePaddleBounce(ball, paddle1, true);
    }
    else if (ball.Intersects(paddle2))
    {
        HandlePaddleBounce(ball, paddle2, false);
    }
}

void PongState::ResetBall()
{
    ball.setPosition({ 960.f, 540.f });

    float random = distrib_float(gen);

    if (random < 0.25f)
        ball.SetVelocity({ -baseBallSpeed, -baseBallSpeed });
    else if (random < 0.5f)
        ball.SetVelocity({ -baseBallSpeed, baseBallSpeed });
    else if (random < 0.75f)
        ball.SetVelocity({ baseBallSpeed, -baseBallSpeed });
    else
        ball.SetVelocity({ baseBallSpeed, baseBallSpeed });
}