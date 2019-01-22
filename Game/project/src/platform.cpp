#include <iostream>

#include "platform.hpp"

Platform::Platform(double h, double w, std::string src) {

	platform_size = sf::Vector2f(h, w);
	platform.setSize(platform_size);
	platform.setOutlineThickness(3);
	platform.setOutlineColor(sf::Color::Black);
	platform.setFillColor(sf::Color::Red);
	// std::cout << src << std::endl;
	t_platform.loadFromFile(src);
	s_platform = sf::Sprite(t_platform);
}

void Platform::Move(double offsetX, double offsetY) {
	platform.move(offsetX, offsetY);
	coord = platform.getPosition();
	s_platform.setPosition(coord);
}

//  set
void Platform::set_Position(sf::Vector2f c) {
	coord = c;
	platform.setPosition(c.x, c.y);
	s_platform.setPosition(coord);
}

//  get
sf::Vector2f Platform::get_Position() {
	return coord;
}

int Platform::get_height() {
	return platform_size.x;
}

int Platform::get_width() {
	return platform_size.y;
}

sf::Sprite Platform::get_s_platform() {
	return s_platform;
}
