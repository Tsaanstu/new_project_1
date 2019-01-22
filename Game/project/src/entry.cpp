#include "entry.hpp"

Entry::Entry(int x, int y, int height, int width) {
	state = 0;
	symbols = 0;
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(x, y));	
	rect.setFillColor(ENTRY_BACKGROUND_COLOR);
	rect.setOutlineThickness(ENTRY_OUTLINE_THICKNESS);
	make_inactive();
	text.setColor(FONT_COLOR);
}

int Entry::get_x() {
	return x;
}

int Entry::get_y() {
	return y;
}

int Entry::get_height() {
	return height;
}

int Entry::get_width() {
	return width;
}

int Entry::get_state() {
	return state;
}

std::string Entry::get_str() {
	return str;
}

void Entry::draw(sf::RenderWindow& window, sf::Font font, char c) {
	window.draw(rect);
	if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		(c >= '0'&& c <= '9') || (c == '_'))) {
		if (symbols < ENTRY_MAX_SYMB) {
			symbols++;
			str += c;
		}
	} else if (c == '\b' && symbols > 0) {
		str.erase(str.length() - 1, 1);
		symbols--;
	}
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(FONT_SIZE);
	text.setPosition(x + 5, y + 5);
	window.draw(text);
}

void Entry::make_active() {
	state = 1;
	rect.setOutlineColor(ENTRY_OUTLINE_ACTIVE_COLOR); 
}

void Entry::make_inactive() {
	state = 0;
	rect.setOutlineColor(ENTRY_OUTLINE_INACTIVE_COLOR); 
}

void Entry::make_enter_finished() {
	state = 2;
	rect.setOutlineColor(ENTRY_OUTLINE_INACTIVE_COLOR); 
	text.setColor(ENTRY_ENTER_FINISHED_COLOR);
	rect.setOutlineColor(ENTRY_OUTLINE_ENTER_FINISHED_COLOR); 
}

bool Entry::in_rect(int a, int b) {
	if ((a >= x) && (a <= x + width) && (b >= y) && (b <= y + height)) {
		return true;
	}
	return false;	
}
