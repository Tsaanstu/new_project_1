#ifndef PROJECT_INCLUDE_ANIMATION_HPP
#define PROJECT_INCLUDE_ANIMATION_HPP

#include "definitions.hpp"

class Animation {
 private:
	sf::Vector2f coord;
	sf::Vector2f object_size;
	sf::Texture t_animation;
	sf::Sprite s_animation;
	double anim_speed;
	double anim;
	int activation;
	double PICTURE_HEIGHT;
 public:
	Animation() = default;
	~Animation() = default;
	Animation(double w, double h, double x, double y, std::string src, double PICTURE_HEIGHT, double as);
	Animation(const Animation& x);
	int mouse_in_anim(sf::RenderWindow& window);
	void tik();
	//  set
	void set_anim(double a);
	void set_Position(sf::Vector2f coord);
	void activate();
	void deactivate();
	//  get
	int get_status();
	sf::Vector2f get_Position();
	int get_height();
	int get_width();
	sf::Sprite get_s_animation();
};

#endif  // PROJECT_INCLUDE_ANIMATION_HPP
