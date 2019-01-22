#ifndef PROJECT_INCLUDE_PLAYER_HPP_
#define PROJECT_INCLUDE_PLAYER_HPP_

#include "man.hpp"
#include "map.hpp"
#include "view.hpp"

class Player : public Man {
 public:
	explicit Player() = default;
	explicit Player(sf::String file, double x, double y, double w, double h, 
	int hp = 0, double d_x = 0, double d_y = 0, double s = 0, int d = 0) :
	Man(file, x, y, w, h, hp, d_x, d_y, s, d) {};

	~Player() = default;
	void move(Map *map, sf::View *view, double *time, int *py, int *px, double *CurrentFrame);
};

#endif  //  PROJECT_INCLUDE_PLAYER_HPP_
