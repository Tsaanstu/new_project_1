#ifndef PROJECT_INCLUDE_ENTRY_HPP_
#define PROJECT_INCLUDE_ENTRY_HPP_

#include "definitions.hpp"

class Entry {
 private:
	int height;
	int width;
	int state; // 0 - inactive, 1 - active, 2 - enter finished
	sf::RectangleShape rect;
 public:
	int x;
	int y;
	int symbols;
	sf::Text text;
	std::string str;
	Entry(int x = ENTRY_X, int y = ENTRY_Y, int height = ENTRY_HEIGHT, int width = ENTRY_WIDTH);
	int get_x();
	int get_y();
	int get_height();
	int get_width();
	int get_state();
	std::string get_str();
	void draw(sf::RenderWindow& window, sf::Font font, char c = ' ' );
	void make_active();
	void make_inactive();
	void make_enter_finished();
	bool in_rect(int x, int y);
};	
	
#endif  // PROJECT_INCLUDE_ENTRY_HPP_
