#include "player_move.hpp"

#include <iostream>

void Player_move::rebuild_command(std::vector<int>& g) {
	std::vector<int> gl;

	for(size_t i = 0; i < 4; i++) {
		if (g[i] != 2) {
			gl.push_back(g[i]);
		}
	}

	for(size_t i = 0; i < gl.size(); i++) {
		if (gl[i] == 1) {
			gl.erase(gl.begin() + i);
			moves.erase(moves.begin() + i);
			break;
		}
	}

	for(size_t i = 0; i < 4; i++) {
		if(g[i] == 1) {
			g[i] = 2;
		}
	}
}

std::vector<Commands>& Player_move::get_moves() {
	return moves;
}

std::string Player_move::get_picture_link() {
	return picture_link;
}

std::string Player_move::get_background_link() {
	return background_link;
}

Storyline& Player_move::get_story() {
	return story;
}

void Player_move::set_story(std::string str) {
	story.set_story(str);
}

void Player_move::set_name(const std::string& str) {
	name = str;
}

void Player_move::set_picture_link(const std::string& str) {
	picture_link = str;
}

void Player_move::set_background_link(const std::string& str) {
	background_link = str;
}

void Player_move::output() {
	std::cout << name << std::endl;
	std::cout << "Available command: ";
	for (size_t i = 0; i < moves.size(); i++) {
		std::cout << std::endl << moves[i].get_move() << " ( " << moves[i].get_move_num() << " )";
	}
	std::cout << std::endl << story.get_story() << std::endl << std::endl;
}
