#ifndef PROJECT_INCLUDE_PLATFORM_HPP_
#define PROJECT_INCLUDE_PLATFORM_HPP_

#include <vector>

#include "definitions.hpp"

class Platform {
 private:
	sf::Vector2f coord;
	sf::Vector2f platform_size;
	sf::RectangleShape platform;
	sf::Texture t_platform;
	sf::Sprite s_platform;
 public:
	Platform() = default;
	~Platform() = default;
	Platform(double h, double w, std::string src);
	void Move(double offsetX, double offsetY);
	//  set
	void set_Position(sf::Vector2f coord);
	//  get
	sf::Vector2f get_Position();
	int get_height();
	int get_width();
	sf::Sprite get_s_platform();
};

#endif  //  PROJECT_INCLUDE_PLATFORM_HPP_
