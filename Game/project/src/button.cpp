#include "button.hpp"

Button::Button(const Button& b) {
	this->text = b.text;
	this->int_rect = b.int_rect;	
}

Button::Button(sf::Text text) {
	this->text = text;
}

void Button::set_text(sf::Text text) {
	this->text = text;
}
void Button::set_int_rect(sf::IntRect int_rect) {
	this->int_rect = int_rect;
}

sf::Text Button::get_text() {
	return text;
}

sf::IntRect Button::get_int_rect() {
	return int_rect;
}

void Button::set_height(int h) {
	height = h;
}

void Button::set_width(int w) {
	width = w;
}

int Button::get_height() {
	return height;
}

int Button::get_width() {
	return width;
}
