#ifndef PROJECT_INCLUDE_GAME_PARADISE_HPP
#define PROJECT_INCLUDE_GAME_PARADISE_HPP

#include "definitions.hpp"

class Game_paradise {
 private:
	double x;
	double y;
	unsigned int score;
	sf::Texture t_hero;
	sf::Sprite hero;
	sf::Texture t_background;
	sf::Sprite background;
	sf::Texture t_cloud;
	sf::Sprite cloud;
	sf::Music music;
 public:
	Game_paradise();
	int Game(sf::RenderWindow& window, int& SCORE);
	~Game_paradise() = default;
};

#endif  //  PROJECT_INCLUDE_GAME_PARADISE_HPP
