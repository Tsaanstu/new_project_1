#ifndef PROJECT_INCLUDE_PLAYER_MOVE_HPP
#define PROJECT_INCLUDE_PLAYER_MOVE_HPP

#include <vector>

#include "command.hpp"
#include "storyline.hpp"

class Player_move {
 private:
	std::string name;
	std::vector<Commands> moves;
	Storyline story;
	std::string picture_link;
	std::string background_link;
 public:
	Player_move() = default;
	~Player_move() = default;
	void set_story(std::string story);
	void set_picture_link(const std::string& bl);
	void set_background_link(const std::string& bl);
	void set_name(const std::string& name);
	Storyline& get_story();
	std::string get_picture_link();
	std::string get_background_link();
	std::vector<Commands>& get_moves();
	void output();
	void rebuild_command(std::vector<int>& gl);
};

#endif  //  PROJECT_INCLUDE_PLAYER_MOVE_HPP
