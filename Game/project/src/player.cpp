#include "player.hpp"

void Player::move(Map *map, sf::View *view, double *time, int *py, int *px, double *CurrentFrame) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		for (auto i = 1; i < HERO_WIDTH - 10; i++) {
			if (map->get_TileMap()[(*py - 1) / BLOCK_HEIGHT][(*px + i) / BLOCK_WIDTH] == '0') {
				return;
			}
		}
		set_direction(0);
		set_speed(0.1);
		*CurrentFrame = *CurrentFrame + 0.005 * *time;
		if (*CurrentFrame > 4) {
			*CurrentFrame -= 4;
		}
		set_Texture_Rect(HERO_WIDTH * int(*CurrentFrame), (HERO_HEIGHT + 2) * 3, HERO_WIDTH, HERO_HEIGHT);
		getplayercoordinateforview(view, get_x_coor(), 
			get_y_coor(), WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		for (auto i = 1; i < HERO_HEIGHT - 10; i++) {
			if (map->get_TileMap()[(*py + i) / BLOCK_HEIGHT][*px / BLOCK_WIDTH + 1] == '0') {
				if ((get_x_coor() / BLOCK_WIDTH - *px / BLOCK_WIDTH) > 0.3) {
					return;
				}
			}
		}
		set_direction(1);
		set_speed(0.1);
		*CurrentFrame = *CurrentFrame + 0.005 * *time;
		if (*CurrentFrame > 4) {
			*CurrentFrame -= 4;
		}
		set_Texture_Rect(HERO_WIDTH * int(*CurrentFrame), (HERO_HEIGHT + 2) * 2, HERO_WIDTH, HERO_HEIGHT);
		getplayercoordinateforview(view, get_x_coor(),
		get_y_coor(), WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		for (auto i = 1; i < HERO_WIDTH - 10; i++) {
			if (map->get_TileMap()[*py / BLOCK_HEIGHT + 1][(*px + i) / BLOCK_WIDTH] == '0') {
				if ((get_y_coor() / BLOCK_HEIGHT - *py / BLOCK_WIDTH) > 0.15) {
					return;
				}
			}
		}
		set_direction(2);
		set_speed(0.1);
		*CurrentFrame = *CurrentFrame + 0.005 * *time;
		if (*CurrentFrame > 4) {
			*CurrentFrame -= 4;
		}
		set_Texture_Rect(HERO_WIDTH * int(*CurrentFrame), 2, HERO_WIDTH, HERO_HEIGHT);
		getplayercoordinateforview(view, get_x_coor(),
		get_y_coor(), WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		for (auto i = 1; i < HERO_HEIGHT - 10; i++) {
			if (map->get_TileMap()[(*py + i) / BLOCK_HEIGHT][(*px - 1) / BLOCK_WIDTH] == '0') {
				return;
			}
		}
		set_direction(3); 
		set_speed(0.1);
		*CurrentFrame = *CurrentFrame + 0.005 * *time;
		if (*CurrentFrame > 4) {
			*CurrentFrame -= 4;
		}
		set_Texture_Rect(HERO_WIDTH * int(*CurrentFrame), HERO_HEIGHT + 2, HERO_WIDTH, HERO_HEIGHT);
		getplayercoordinateforview(view, get_x_coor(),
		get_y_coor(), WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
