#include <fstream>
#include <iostream>

#include "command.hpp"

int Commands::get_move_num() {
	return move_num;
}

const std::string& Commands::get_move() const {
	return move;
}

std::string Commands::get_command_from_file(int m_id, int *move_num, std::string file_name) {
	std::ifstream file(file_name);
	if (!file) {
		std::cerr << "file " << file_name << " not found" << std::endl;
		return file_name;
	}

	int id = 0;
	while(file >> id) {
		std::string buf;
		file >> *move_num;
		file.get();
		std::getline(file, buf, '\n');
		if (m_id == id) {
			file.close();
			return buf;
		}
	}
	file.close();
	return " ";
}
