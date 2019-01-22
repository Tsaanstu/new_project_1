#include "ball.hpp"

Ball::Ball(double r, std::string src) {
	ball_radius = r;

	ball.setRadius(ball_radius - 3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::White);

	t_ball.loadFromFile(src);
	s_ball = sf::Sprite(t_ball);
}

void Ball::Move(double offsetX, double offsetY) {
	ball.move(offsetX, offsetY);
	coord = ball.getPosition();
	s_ball.setPosition(coord);
}

//  set
void Ball::set_Position(sf::Vector2f c) {
	coord = c;
	ball.setPosition(c.x, c.y);
	s_ball.setPosition(coord);
}

//  get
sf::Vector2f Ball::get_Position() {
	return coord;
}

double Ball::get_radius() {
	return ball_radius;
}

sf::Sprite Ball::get_s_platform() {
	return s_ball;
}
