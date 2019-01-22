#ifndef PROJECT_INCLUDE_MAP_HPP_
#define PROJECT_INCLUDE_MAP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "labirint.hpp"

class Map {
 private:
	std::vector<std::string> TileMap;
	size_t size;
	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;
 public:
	Map() = default;
	Map(sf::String file, size_t s = 0);
	~Map() = default;
	void Create_Lab(Labirint lab);
	void Output_Lab();
	const size_t& get_size();
	const std::vector<std::string>& get_TileMap();
	const sf::Sprite& get_s_map();
	void set_Position(int y, int x);
	void set_Texture_Rect(double a, double b, double c, double d);
};

#endif  //  PROJECT_INCLUDE_MAP_HPP_
