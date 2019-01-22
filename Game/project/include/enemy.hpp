#ifndef PROJECT_INCLUDE_ENEMY_HPP_
#define PROJECT_INCLUDE_ENEMY_HPP_

#include "man.hpp"
#include "map.hpp"
#include "view.hpp"

class Enemy : public Man {
 public:
	explicit Enemy() = default;
	explicit Enemy(sf::String file, double x, double y, double w, double h, 
	int hp = 1, double d_x = 0, double d_y = 0, double s = 0, int d = 0) :
	Man(file, x, y, w, h, hp, d_x, d_y, s, d) {};
	~Enemy() = default;
	void move(Map *map, int *py, int *px);
};

#endif  //  PROJECT_INCLUDE_ENEMY_HPP_
