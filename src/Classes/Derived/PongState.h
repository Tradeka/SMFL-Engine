#pragma once
#include "Classes/Base/GameState.h"
#include "Classes/Base/GameObject.h"
#include <random>
#include <memory>
#include <SFML/Audio/Music.hpp>

using namespace sf;

class PongState : public GameState
{
public:
    PongState();
    ~PongState() override = default;

    void HandleInput(RenderWindow& window) override;
    void Update() override;
    void Render(RenderWindow& window) override;

private:
    //Helper functions
    void HandlePaddleBounce(GameObject& ball, GameObject& paddle, bool isLeftPaddle);
    void CheckCollisions(const Vector2u& windowSize);
    void ResetBall();

    //Textures - must be declared before GameObjects that use them
    Texture ballTexture;
    Texture paddleTexture;
    Texture gateTexture;

    //Game objects - initialized in constructor initializer list
    GameObject ball;
    GameObject paddle1;
    GameObject paddle2;
    GameObject gate;
    GameObject gate2;
    GameObject gate3;

    //Game state
    int player1Score;
    int player2Score;
    float baseBallSpeed;

    //UI
    Font gameFont;
    std::unique_ptr<Text> player1ScoreText;
    std::unique_ptr<Text> player2ScoreText;

    //Random number generation
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> distrib_float;

    //Music/Sounds
	sf::Music gameMusic;
};
