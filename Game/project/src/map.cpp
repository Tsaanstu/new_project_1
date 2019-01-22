#include "map.hpp"

const size_t& Map::get_size() {
	return size;
}

const std::vector<std::string>& Map::get_TileMap() {
	return TileMap;
}

void Map::set_Position(int y, int x) {
	s_map.setPosition(y, x);
}

void Map::set_Texture_Rect(double a, double b, double c, double d) {
	s_map.setTextureRect(sf::IntRect(a, b, c, d));
}

const sf::Sprite& Map::get_s_map() {
	return s_map;
}

Map::Map(sf::String file, size_t s) {
	map_image.loadFromFile(file);
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	size = s;

	std::string buf = "";
	for (size_t i = 0; i < size; i++) {
		buf += '0';
	}
	TileMap.push_back(buf);
	for (size_t i = 0; i < size - 2; i++) {
		buf = '0';
		for (size_t j = 0; j < size - 2; j++) {
			buf += ' ';
		}
		buf += '0';
		TileMap.push_back(buf);
	}
	buf = "";
	for (size_t i = 0; i < size; i++) {
		buf += '0';
	}
	TileMap.push_back(buf);
}

void Map::Create_Lab(Labirint lab) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			TileMap[i][j] = lab.getme(i, j) + '0';
		}
	}
}

void Map::Output_Lab() {
	for (size_t i = 0; i < size; i++) {
		std::cout << TileMap[i] << std::endl;
	}
}
