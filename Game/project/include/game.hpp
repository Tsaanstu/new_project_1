#ifndef PROJECT_INCLUDE_GAME_HPP
#define PROJECT_INCLUDE_GAME_HPP

#include <vector>

#include "button.hpp"
#include "definitions.hpp"
#include "player_moves.hpp"
#include "game_lab.hpp"
#include "quiz.hpp"
#include "quiz_mermaid.hpp"
#include "GameFW.hpp"
#include "game_paradise.hpp"
#include "game_hell.hpp"
#include "animation.hpp"
#include "finish.hpp"

class Game {
 private:
	sf::SoundBuffer b_dragon_sound;
	sf::Sound dragon_sound;
	sf::Music music;
 public:
	Game() = default;
	int draw(sf::RenderWindow& window);
	void buttons_draw(std::vector<Button>& buttons);
	std::vector<Button> move(int make_a_move, Player_moves *moves, sf::Font &font);
	void on_minigame(int mg_id, sf::RenderWindow& window, int& PLAYER_HP, int& SCORE);
	void create_button(std::vector<Button>& buttons);
	int mouse_in_button(std::vector<Button>& buttons, sf::RenderWindow& window, size_t* choose);
	sf::Text output_history(Player_moves moves, sf::Font& font, int make_a_move);
	~Game() = default;
};

#endif  // PROJECT_INCLUDE_GAME_HPP_
