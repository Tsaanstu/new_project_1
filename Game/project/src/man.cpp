#include "man.hpp"

Man::Man(const Man& m) {
	HP = m.get_HP();
	x_coor = m.get_x_coor();
	y_coor = m.get_y_coor();
	width = m.get_width();
	height = m.get_width();
	dx = m.get_dx();
	dy = m.get_dy();
	speed = m.get_speed();
	direction = m.get_direction();
	file_name = m.get_file_name();
	image = m.get_image();
	texture = m.get_texture();
	sprite = m.get_sprite();
}

void Man::update(double time) {
	switch (direction) {
		case 1: 
			dx = speed; 
			dy = 0; 
			break;
		case 3: 
			dx = -speed; 
			dy = 0; 
			break;
		case 2: 
			dx = 0; 
			dy = speed; 
			break;
		case 0: 
			dx = 0; 
			dy = -speed; 
			break;
	}

	x_coor += dx * time;
	y_coor += dy * time;
	speed = 0;
	sprite.setPosition(x_coor, y_coor);
}

Man::Man(sf::String file, double x, double y, double w, double h,
int hp, double d_x, double d_y, double s, int d) {
	x_coor = x;
	y_coor = y;
	width = w;
	height = h;
	dx = d_x; 
	dy = d_y;
	speed = s; 
	direction = d;
	file_name = file;
	HP = hp;

	image.loadFromFile(file_name);
	image.createMaskFromColor(sf::Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

int Man::get_HP() const {
	return HP;
}

double Man::get_x_coor() const {
	return x_coor;
}

double Man::get_y_coor() const {
	return y_coor;
}

double Man::get_width() const {
	return width;
}

double Man::get_height() const {
	return height;
}

double Man::get_dx() const {
	return dx;
}

double Man::get_dy() const {
	return dy;
}

double Man::get_speed() const {
	return speed;
}

void Man::set_speed(double s) {
	speed = s;
}

void Man::set_direction(int d) {
	direction = d;
}

void Man::set_Texture_Rect(double a, double b, double c, double d) {
	sprite.setTextureRect(sf::IntRect(a, b, c, d));
}

int Man::get_direction() const {
	return direction;
}

sf::FloatRect Man::get_Rect() {
	return sf::FloatRect(x_coor, y_coor, width, height);
}

sf::Sprite Man::get_sprite() const {
	return sprite;
}

sf::String Man::get_file_name() const {
	return file_name;
}

sf::Image Man::get_image() const {
	return image;
}

sf::Texture Man::get_texture() const {
	return texture;
}

void Man::set_HP(int hp) {
	HP = hp;
}

void Man::set_x_coor(double x) {
	x_coor = x;
}

void Man::set_y_coor(double y) {
	y_coor = y;	
}
