#ifndef PROJECT_INCLUDE_GAME_HELL_HPP_
#define PROJECT_INCLUDE_GAME_HELL_HPP_

#include "definitions.hpp"
#include "platform.hpp"
#include "ball.hpp"

class Game_hell {
 private:
	Platform *player_platform;
	Platform *bot_platform;
	Ball *ball;
	sf::Clock clock;
	double ballAngle;
	sf::Vector2f PLATFORM_SIZE;
	int score;
	sf::SoundBuffer b_sound;
	sf::Sound sound;
	sf::Music music;
 public:
	Game_hell();
	~Game_hell() = default;
	int Game(sf::RenderWindow& window, int& SCORE);
};

#endif  //  PROJECT_INCLUDE_GAME_HELL_HPP_
