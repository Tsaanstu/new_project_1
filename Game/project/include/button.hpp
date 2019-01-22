#ifndef PROJECT_INCLUDE_BUTTON_HPP
#define PROJECT_INCLUDE_BUTTON_HPP

#include "definitions.hpp"

class Button {
 private:
	sf::Text text;
	sf::IntRect int_rect;
	int height;
	int width;
 public:
	//  set
	void set_text(sf::Text text);
	void set_int_rect(sf::IntRect int_rect);
	void set_height(int height);
	void set_width(int width);
	//  get
	sf::Text get_text();
	sf::IntRect get_int_rect();
	int get_height();
	int get_width();

	Button() = default;
	Button(const Button& b);
	Button(sf::Text text);
	~Button() = default;
};

#endif  // PROJECT_INCLUDE_BUTTON_HPP_
