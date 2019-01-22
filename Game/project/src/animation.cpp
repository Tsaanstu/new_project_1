#include "animation.hpp"

#include <iostream>

Animation::Animation(double w, double h, double x, double y, std::string src, double PH, double as) {
	anim_speed = as;
	anim = 0;
	activation = 0;
	object_size = sf::Vector2f(h, w);
	coord = sf::Vector2f(x, y);
	PICTURE_HEIGHT = PH;
	t_animation.loadFromFile(src);
	s_animation = sf::Sprite(t_animation);
	s_animation.setPosition(coord);
	s_animation.setTextureRect(sf::IntRect(0, 0, w, h));
}

Animation::Animation(const Animation& x) {
	anim_speed = x.anim_speed;
	anim = x.anim;
	activation = x.activation;
	coord = x.coord;
	object_size = x.object_size;
	t_animation = x.t_animation;
	PICTURE_HEIGHT = x.PICTURE_HEIGHT;
	s_animation = sf::Sprite(t_animation);
	s_animation.setTextureRect(sf::IntRect(0, 0, object_size.y, object_size.x));
	s_animation.setPosition(coord);
}

int Animation::mouse_in_anim(sf::RenderWindow& window) {
	if (sf::IntRect(coord.x, coord.y, object_size.x, object_size.y).contains(sf::Mouse::getPosition(window))) {
		return 1;
	} else {
		return 0;
	}
}

void Animation::tik() {
	if (anim > (PICTURE_HEIGHT / object_size.y - 1)) {
		anim = 0;
		s_animation.setTextureRect(sf::IntRect(0, 0, object_size.y, object_size.x));
		deactivate();
	} else {
		anim += anim_speed;
		s_animation.setTextureRect(sf::IntRect(object_size.y * static_cast<int>(anim), 0,
			object_size.y, object_size.x));
	}
}

//  set
void Animation::set_Position(sf::Vector2f c) {
	coord = c;
	s_animation.setPosition(coord);
}

void Animation::set_anim(double a) {
	anim = a;
}

void Animation::activate() {
	activation = 1;
	//  anim = 0;
}

void Animation::deactivate() {
	activation = 0;
}

//  get
sf::Vector2f Animation::get_Position() {
	return coord;
}

int Animation::get_status() {
	return activation;
}

int Animation::get_height() {
	return object_size.x;
}

int Animation::get_width() {
	return object_size.y;
}

sf::Sprite Animation::get_s_animation() {
	return s_animation;
}
