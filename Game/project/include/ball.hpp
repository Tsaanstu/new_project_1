#ifndef PROJECT_INCLUDE_BALL_HPP_
#define PROJECT_INCLUDE_BALL_HPP_

#include <vector>

#include "definitions.hpp"

class Ball {
 private:
	sf::Vector2f coord;
	sf::CircleShape ball;
	sf::Texture t_ball;
	sf::Sprite s_ball;
	double ball_radius;
 public:
	Ball() = default;
	~Ball() = default;
	Ball(double r, std::string src);
	void Move(double offsetX, double offsetY);
	//  set
	void set_Position(sf::Vector2f coord);
	//  get
	sf::Vector2f get_Position();
	double get_radius();
	sf::Sprite get_s_platform();
};

#endif  //  PROJECT_INCLUDE_BALL_HPP_
