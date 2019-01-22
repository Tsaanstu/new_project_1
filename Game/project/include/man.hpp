#ifndef PROJECT_INCLUDE_MAN_HPP_
#define PROJECT_INCLUDE_MAN_HPP_

#include "definitions.hpp"

class Man {
 private:
	int HP;
	double x_coor;
	double y_coor;
	double width;
	double height;
	double dx;
	double dy;
	double speed;
	int direction;
	//  input in constructor
	sf::String file_name;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
 public:
	Man() = default;
	Man(const Man& m);
	Man(sf::String file, double x, double y, double w, double h,
		int hp = 0, double d_x = 0, double d_y = 0, double s = 0, int d = 0);
	virtual ~Man() = default;
	//  get
	int get_HP() const;
	double get_x_coor() const;
	double get_y_coor() const;
	double get_width() const;
	double get_height() const;
	double get_dx() const;
	double get_dy() const;
	double get_speed() const;
	int get_direction() const;
	sf::String get_file_name() const;
	sf::Image get_image() const;
	sf::Texture get_texture() const;
	sf::Sprite get_sprite() const;
	sf::FloatRect get_Rect();
	//  set
	void set_HP(int hp);
	void set_speed(double s);
	void set_direction(int d);
	void set_Texture_Rect(double a, double b, double c, double d);
	void set_x_coor(double x);
	void set_y_coor(double y);

	void update(double time);
};

#endif  //  PROJECT_INCLUDE_MAN_HPP_
