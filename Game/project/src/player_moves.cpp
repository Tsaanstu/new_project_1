#include <fstream>
#include <iostream>

#include "definitions.hpp"
#include "player_moves.hpp"

#define FILE_NOT_FOUND -2

void Player_moves::rebuild_command(int num, std::vector<int>& gl) {
	all_moves[num].rebuild_command(gl);
}

Player_move& Player_moves::operator[](size_t i) {
	return all_moves[i];
}

std::vector<std::string> Player_moves::get_commands(int num) {
	std::vector<Commands> temp = all_moves[num].get_moves();
	std::vector<std::string> commands;
	for(size_t i = 0; i < temp.size(); i++) {
		commands.push_back(temp[i].get_move());
	}
	return commands;
}

void Player_moves::output_commands(int num) {
	std::vector<Commands> temp = all_moves[num].get_moves();
	for (size_t i = 0; i < temp.size(); i++) {
		std::cout << std::endl << i << ")" << temp[i].get_move();
		std::cout << " ( " << temp[i].get_move_num() << " )";
	}
	std::cout << std::endl;
}

void Player_moves::output_story(int num) {
	std::string temp =  all_moves[num].get_story().get_story();
	std::cout << temp << std::endl;
}

std::string Player_moves::get_story(int num) {
	std::string temp =  all_moves[num].get_story().get_story();
	return temp;
}

std::string Player_moves::get_picture_link(int num) {
	std::string temp =  all_moves[num].get_picture_link();
	return temp;
}

std::string Player_moves::get_background_link(int num) {
	std::string temp =  all_moves[num].get_background_link();
	return temp;
}

static std::vector<int> get_num_from_file_str(std::ifstream& file) {
	int temp_c_id = 0;
	std::vector<int> c_id;
	char c = file.get();
	while ((c = file.get()) != '\n') {
		if (isdigit(c)) {
			temp_c_id = temp_c_id * 10 + c - '0';
		} else {
			c_id.push_back(temp_c_id);
			temp_c_id = 0;
		}
	}
	c_id.push_back(temp_c_id);
	return c_id;
}

int Player_moves::input_moves(std::string file_name) {
	std::ifstream file(file_name);
	if (!file) {
		std::cerr << "file " << file_name << " not found" << std::endl;
		return FILE_NOT_FOUND;
	}
	int m_key = 0;
	while (file >> m_key) {
		std::string name;  //  ввод описания хода (для отладки)
		std::getline(file, name);
		Player_move temp_move;
		temp_move.set_name(name);

		int s_id = 0;  //  ввод текста
		file >> s_id;
		temp_move.set_story(temp_move.get_story().get_story_from_file(s_id));

		//  ввод комманд
		std::vector<int> c_id = get_num_from_file_str(file);
		Commands temp;
		for (size_t i = 0; i < c_id.size(); i++) {
			int temp_move_num = 0;
			std::string m = temp.get_command_from_file(c_id[i], &temp_move_num);
			temp_move.get_moves().push_back(Commands(m, temp_move_num));
		}

		//  путь до фона
		std::getline(file, name);
		name = BACKGROUND_LINK + name;
		temp_move.set_background_link(name);

		//  путь до изображения
		std::getline(file, name);
		name = PICTURE_LINK + name;
		temp_move.set_picture_link(name);

		all_moves[m_key] = temp_move;
	}
	file.close();
	return 0;
}

void Player_moves::output_all_moves() {
	for (auto it = all_moves.begin(); it != all_moves.end(); ++it) {
		std::cout << it->first << " ";
		it->second.output();
	}
}

size_t Player_moves::choose_move(size_t this_move, int choose) {
	int temp = all_moves[this_move].get_moves()[choose].get_move_num();
	return temp;
}
