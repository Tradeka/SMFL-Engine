#include <SFML/Graphics.hpp>
#include "Classes/GameObject.h"
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

	Texture texture("Assets/Textures/ball.png");

	GameObject ball(texture);
	ball.setPosition({ 960.f, 540.f });
	ball.SetVelocity({ 3.5f, 3.5f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if(ball.getPosition().x + ball.GetSize().x / 2 >= 1920.f || ball.getPosition().x - ball.GetSize().x / 2 <= 0.f)
        {
            ball.SetVelocity({ -ball.GetVelocity().x, ball.GetVelocity().y});
		}
        else if (ball.getPosition().y + ball.GetSize().y / 2 >= 1080.f || ball.getPosition().y - ball.GetSize().y / 2 <= 0.f)
        {
            ball.SetVelocity({ ball.GetVelocity().x, -ball.GetVelocity().y });
        }
        
		ball.move(ball.GetVelocity());

        window.clear();
        window.draw(ball);
        window.display();
    }
}
