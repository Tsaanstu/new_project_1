#include "enemy.hpp"

void Enemy::move(Map *map, int *py, int *px) {
	if (get_direction() == 0) {
		for (auto i = 1; i < HERO_WIDTH - 10; i++) {
			if (map->get_TileMap()[(*py - 1) / BLOCK_HEIGHT][(*px + i) / BLOCK_WIDTH] == '0') {
				set_direction(rand() % 4);
				return;
			}
		}
		set_direction(0);
		set_speed(0.1);
		set_Texture_Rect((ENEMY_WIDTH + 1) * 3, 0, ENEMY_WIDTH, ENEMY_HEIGHT);
	} 
	if (get_direction() == 1) {
		for (auto i = 1; i < HERO_HEIGHT - 10; i++) {
			if (map->get_TileMap()[(*py + i) / BLOCK_HEIGHT][*px / BLOCK_WIDTH + 1] == '0') {
				if ((get_x_coor() / BLOCK_WIDTH - *px / BLOCK_WIDTH) > 0.3) {
					set_direction(rand() % 4);
					return;
				}
			}
		}
		set_direction(1);
		set_speed(0.1);
		set_Texture_Rect(ENEMY_WIDTH + 1, 0, ENEMY_WIDTH, ENEMY_HEIGHT);
	}
	if (get_direction() == 2) {
		for (auto i = 1; i < HERO_WIDTH - 10; i++) {
			if (map->get_TileMap()[*py / BLOCK_HEIGHT + 1][(*px + i) / BLOCK_WIDTH] == '0') {
				if ((get_y_coor() / BLOCK_HEIGHT - *py / BLOCK_WIDTH) > 0.15) {
					set_direction(rand() % 4);
					return;
				}
			}
		}
		set_direction(2);
		set_speed(0.1);
		set_Texture_Rect(0, 0, ENEMY_WIDTH, ENEMY_HEIGHT);
	}
	if (get_direction() == 3) {
		for (auto i = 1; i < HERO_HEIGHT - 10; i++) {
			if (map->get_TileMap()[(*py + i) / BLOCK_HEIGHT][(*px - 1) / BLOCK_WIDTH] == '0') {
				set_direction(rand() % 4);
				return;
			}
		}
		set_direction(3); 
		set_speed(0.1);
		set_Texture_Rect((ENEMY_WIDTH + 1) * 2, 0, ENEMY_WIDTH, ENEMY_HEIGHT);
	}
}
