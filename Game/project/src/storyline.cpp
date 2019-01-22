#include <fstream>
#include <iostream>

#include "storyline.hpp"

const std::string& Storyline::get_story() const {
	return story;
}

void Storyline::set_story(const std::string& st) {
	story = st;
}

std::string Storyline::get_story_from_file(int s_id, std::string file_name) {
	std::ifstream file(file_name);
	if (!file) {
		std::cerr << "file " << file_name << " not found" << std::endl;
		return file_name;
	}
	int id = 0;
	while(file >> id) {
		if (id == s_id) {
			std::string buf;
			char sym = file.get();
			while(sym != '~') {
				buf += sym;
				sym = file.get();
			}
			file.close();
			return buf;
		}
		char sym = file.get();
		while(sym != '~') {
			sym = file.get();
		}
	}
	file.close();
	return "";
}
