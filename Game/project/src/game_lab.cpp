#include <unistd.h>

#include "game_lab.hpp"

int Game_lab::is_finish(Player *m_player, size_t N) {
	if (m_player->get_x_coor() > BLOCK_WIDTH * (N - 2) && m_player->get_y_coor() >  BLOCK_HEIGHT * (N - 2)) {
		// std::cout << "finish" << std::endl;
		return 1;
	}
	return 0;
}

int Game_lab::crash(Man *m1, Man *m2) {
	if (m1->get_Rect().intersects(m2->get_Rect())) {
		return 1;
	}
	return 0;
}

void Game_lab::place_man(Man *th) {
	int x = rand() % (SIZE_LAB - 1);
	int y = rand() % (SIZE_LAB - 1);
	int temp = 0;
	while(lab->getme(x, y) == 0 || temp == 0) {
		temp = 0;
		x = rand() % SIZE_LAB;
		y = rand() % SIZE_LAB;
		for (int j = 1; j < x; j++) {
			if (lab->getme(y, j) == 0) {
				temp = 1;
			}
		}
		for (int i = 1; i < y; i++) {
			if (lab->getme(i, x) == 0) {
				temp = 1;
			}
		}
	}
	th->set_x_coor(x * BLOCK_WIDTH);
	th->set_y_coor(y * BLOCK_HEIGHT);
}

Game_lab::Game_lab() {
	lab = new Labirint(SIZE_LAB);
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	map = new Map(MAP_SRC, SIZE_LAB);
	map->Create_Lab(*lab);
	m_player = new Player(HERO_SPRITE_SRC, BLOCK_WIDTH, BLOCK_HEIGHT, HERO_WIDTH, HERO_HEIGHT);
	CurrentFrame = 0;
	for (size_t i = 0; i < ENEMY_NUM; i++) {
		Enemy* t_en = new Enemy(ENEMY_SPRITE_SRC, BLOCK_WIDTH, BLOCK_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT);
		place_man(t_en);
		enemy.push_back(t_en);
	}
	b_ghost_sound.loadFromFile(LABIRINT_SOUND_GHOST);
	ghost_sound = sf::Sound(b_ghost_sound);
	music.openFromFile(LABIRINT_MUSIC);
}

int Game_lab::Game(sf::RenderWindow& window, int& PLAYER_HP, int& SCORE, int e_speed) {
	sf::Clock clock, timer;
	m_player->set_HP(PLAYER_HP);
	size_t enemy_num = ENEMY_NUM;
	sf::Font font;
	if (!font.loadFromFile("fonts/COURIER.TTF")) {
		return ERR_OF_FONT;
	}
	music.setLoop(true);
	music.play();
	while (1) {
		double time = clock.getElapsedTime().asMicroseconds();
		double time_enemy = clock.getElapsedTime().asMicroseconds();
		int run_time = timer.getElapsedTime().asSeconds();
		clock.restart();
		time /= 800;
		time_enemy /= (800 / e_speed);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return GAME_STOP;
			}
		}
		std::vector<int> enemy_px(enemy_num);
		for (size_t i = 0; i < enemy_num; i++) {
			enemy_px[i] = enemy[i]->get_x_coor();
		}
		std::vector<int> enemy_py(enemy_num);
		for (size_t i = 0; i < enemy_num; i++) {
			enemy_py[i] = enemy[i]->get_y_coor();
		}

		px = m_player->get_x_coor();
		py = m_player->get_y_coor();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (is_finish(m_player, map->get_size())) {
			int s = 240 - run_time;
			if (s > 0) {
				SCORE += s;
			}
			PLAYER_HP = m_player->get_HP();
			view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
			window.setView(view);
			return GAME_WIN;
		} else {
			m_player->move(map, &view, &time, &py, &px, &CurrentFrame);
			m_player->update(time);
			viewmap(&view, time);
			changeview(&view);
			window.setView(view);
			window.clear();
			for (size_t i = 0; i < enemy_num; i++) {
				enemy[i]->move(map, &enemy_py[i], &enemy_px[i]);
				enemy[i]->update(time_enemy);
			}

			for (int i = 0; i < SIZE_LAB; i++) {
				for (int j = 0; j < SIZE_LAB; j++) {
					if (map->get_TileMap()[i][j] == '0') {
							map->set_Texture_Rect(BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
					} else if (map->get_TileMap()[i][j] == '2') {
							map->set_Texture_Rect(BLOCK_WIDTH * 2, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
					} else {
							map->set_Texture_Rect(0, 0, BLOCK_WIDTH, BLOCK_HEIGHT);
					}
					map->set_Position(j * BLOCK_HEIGHT, i * BLOCK_WIDTH);
					window.draw(map->get_s_map());
				}
			}
		}
		for (size_t i = 0; i < enemy_num; i++) {
			if (crash(enemy[i], m_player) == 1) {
				ghost_sound.play();
				enemy_num--;
				enemy.erase(enemy.begin() + i);
				m_player->set_HP(m_player->get_HP() - 20);
				if (m_player->get_HP() <= 0) {
					// std::cout << "Player died" << std::endl;
					PLAYER_HP = m_player->get_HP();
					view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
					window.setView(view);
					return PLAYER_DIED;
				}
			}
		}

		sf::Text stat("hp: " + std::to_string(m_player->get_HP()) +
		"\ntime: " + std::to_string(run_time), font);
		sf::Vector2f stat_coor = view.getCenter();
		stat_coor.x -= WINDOW_WIDTH / 2;
		stat_coor.y -= WINDOW_HEIGHT / 2;
		stat.setPosition(stat_coor);
		stat.setColor(FONT_COLOR);

		for (size_t i = 0; i < enemy_num; i++) {
			window.draw(enemy[i]->get_sprite());
		}
		window.draw(m_player->get_sprite());
		window.draw(stat);
		window.display();
	}
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(view);
	return 0;
}
