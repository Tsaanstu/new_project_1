#ifndef PROJECT_INCLUDE_PLAYER_MOVES_HPP
#define PROJECT_INCLUDE_PLAYER_MOVES_HPP

#include <map>

#include "player_move.hpp"

class Player_moves {
 private:
	std::map<int, Player_move> all_moves;
 public:
	Player_moves() = default;
	~Player_moves() = default;
	int input_moves(std::string file_name = "data/unions.txt");
	void output_all_moves();
	size_t choose_move(size_t this_move, int choose);  //  номер хода в map, номер команды из хода
	Player_move& operator[](size_t i);
	std::vector<std::string> get_commands(int num);
	std::string get_story(int num);
	std::string get_picture_link(int num);
	std::string get_background_link(int num);
	//
	void output_commands(int num);
	void output_story(int num);
	void rebuild_command(int num, std::vector<int>& gl);
};

#endif  //  PROJECT_INCLUDE_PLAYER_MOVES_HPP
