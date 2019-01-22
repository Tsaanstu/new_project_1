#ifndef PROJECT_INCLUDE_GAME_LAB_HPP
#define PROJECT_INCLUDE_GAME_LAB_HPP

#include "enemy.hpp"
#include "player.hpp"
#include "definitions.hpp"

class Game_lab {
 private:
	Labirint *lab;
	sf::View view;
	Map *map;
	sf::Clock clock;
	Player *m_player;
	std::vector<Enemy*> enemy;
	int px;
	int py;
	double CurrentFrame;

	sf::SoundBuffer b_ghost_sound;
	sf::Sound ghost_sound;
	sf::Music music;
 public:
	int is_finish(Player *m_player, size_t N);
	Game_lab();
	int Game(sf::RenderWindow& window, int& PLAYER_HP, int& SCORE, int e_speed = 1);
	~Game_lab() = default;
	int crash(Man *m1, Man *m2);
	void place_man(Man *enemy);
};

#endif  // PROJECT_INCLUDE_GAME_LAB_HPP
