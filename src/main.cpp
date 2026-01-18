#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Classes/GameObject.h"

auto handlePaddleBounce = [](GameObject& ball, GameObject& paddle, bool isLeftPaddle) //lambda for calculating ball bounce off paddles
    {
        float paddleHeight = paddle.GetGlobalBounds().size.y;
        float paddleHalfWidth = paddle.GetGlobalBounds().size.x / 2.f;
        float ballHalfWidth = ball.GetGlobalBounds().size.x / 2.f;

        //1. Compute normalized hit position
        float deltaY = ball.getPosition().y - paddle.getPosition().y;
        float normalized = std::clamp(deltaY / (paddleHeight / 2.f), -1.f, 1.f); //-1 top, +1 bottom

        //2. Keep speed constant
        Vector2f velocity = ball.GetVelocity();
        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

        velocity.x = std::abs(velocity.x);            // Xshould move away from paddle
        velocity.x = isLeftPaddle ? velocity.x : -velocity.x; //flip for right paddle
        velocity.y = normalized * speed;

        ball.SetVelocity(velocity);

        //3. Reposition ball outside paddle to prevent sticking
        float newX = isLeftPaddle ? paddle.getPosition().x + paddleHalfWidth + ballHalfWidth : paddle.getPosition().x - paddleHalfWidth - ballHalfWidth;

        ball.setPosition({ newX, ball.getPosition().y });
    };

//Set up random number generator for ball velocity variation
std::random_device rd; // For seeding
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_real_distribution<> distrib_float(0.f, 1.f);

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

	//Load Textures
	Texture ballTexture("Assets/Textures/ball.png");
    Texture paddle1Texture("Assets/Textures/paddle.png");
    Texture paddle2Texture("Assets/Textures/paddle.png");


    //Ball
    GameObject ball(ballTexture);
	ball.setPosition({ 960.f, 540.f });
    ball.scale({ 0.4f, 0.4f });

	//Set initial ball velocity with some randomness
	float random = distrib_float(gen);

    if(random < 0.25f)
        ball.SetVelocity({ -3.5f, -3.5f });
    else if(random < 0.5f)
        ball.SetVelocity({ -3.5f, 3.5f });
    else if(random < 0.75f)
        ball.SetVelocity({ 3.5f, -3.5f });
	else
		ball.SetVelocity({ 3.5f, 3.5f });


    //Player 1
    GameObject paddle1(paddle1Texture);
    paddle1.scale({ 1.f, 1.8f });
    paddle1.setPosition({ (float)paddle1.GetGlobalBounds().size.x / 2, (float)window.getSize().y / 2 });

	GameObject paddle2(paddle2Texture);
	paddle2.scale({ 1.f, 1.8f });
	paddle2.setPosition({ (float)(window.getSize().x - paddle2.GetGlobalBounds().size.x / 2), (float)window.getSize().y / 2 });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        //Player Input
		paddle1.SetVelocity({ 0.f,0.f }); //Set Velocity to 0 every frame the key is not being pressed so the paddles stop moving when no input is given
		paddle2.SetVelocity({ 0.f,0.f });

		//Paddle 1 Controls
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            paddle1.SetVelocity({ 0.f, -3.5f });
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::S))
        {
            paddle1.SetVelocity({ 0.f, 3.5f });
        }

		//Paddle 2 Controls
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
			paddle2.SetVelocity({ 0.f, -3.5f });
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
        {
			paddle2.SetVelocity({ 0.f, 3.5f });
        }


        //Wall collision (ball)
        if (ball.getPosition().y < 0 + ball.GetGlobalBounds().size.y / 2)
        {
            ball.setPosition({ ball.getPosition().x, 0 + ball.GetGlobalBounds().size.y / 2});
            ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });
        }
        else if (ball.getPosition().y > window.getSize().y - ball.GetGlobalBounds().size.y / 2)
        {
            ball.setPosition({ ball.getPosition().x, window.getSize().y - ball.GetGlobalBounds().size.y / 2 });
            ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });
        }
        else if (ball.getPosition().x > window.getSize().x - ball.GetGlobalBounds().size.x / 2)
        {
			//Will Add Score Here Later
            ball.setPosition({ 960.f, 540.f });
            ball.SetVelocity({ -3.5f, 3.5f });
        }
        else if (ball.getPosition().x < 0 + ball.GetGlobalBounds().size.x / 2)
		{
            //Will Add Score Here Later
            ball.setPosition({ 960.f, 540.f });
			ball.SetVelocity({ 3.5f, 3.5f });
        }


		//Wall Collision(paddle1) - We can just use clamp here because the paddle doesn't bounce off walls
        auto pos = paddle1.getPosition();
        float halfHeight = paddle1.GetGlobalBounds().size.y / 2.f; 
        pos.y = std::clamp(pos.y, halfHeight, window.getSize().y - halfHeight);
        paddle1.setPosition(pos);

		//Wall Collision(paddle2)
		auto pos2 = paddle2.getPosition();
		float halfHeight2 = paddle2.GetGlobalBounds().size.y / 2.f;
		pos2.y = std::clamp(pos2.y, halfHeight2, window.getSize().y - halfHeight2);
		paddle2.setPosition(pos2);
        

        //Object Collision
        if (ball.Intersects(paddle1))
        {
            handlePaddleBounce(ball, paddle1, true);
        }
        else if (ball.Intersects(paddle2))
        {
            handlePaddleBounce(ball, paddle2, false);
        }


        //Move objects
		ball.move(ball.GetVelocity());
        paddle1.move(paddle1.GetVelocity());
		paddle2.move(paddle2.GetVelocity());

		//Draw Objects
        window.clear();
        window.draw(ball);
        window.draw(paddle1);
		window.draw(paddle2);
        window.display();
    }

    
}
