#include <iostream>
#include <vector>

#include "game_paradise.hpp"

Game_paradise::Game_paradise() {
	t_hero.loadFromFile(ANGEL_SPRITE_SRC);
	hero = sf::Sprite(t_hero);
	t_background.loadFromFile(BACKGROUND_SPRITE_SRC);
	background = sf::Sprite(t_background);
	background.setScale(20, 20);
	t_cloud.loadFromFile(PLATFORM_SPRITE_SRC);
	cloud = sf::Sprite(t_cloud);
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT - ANGEL_HEIGHT;

	music.openFromFile(PARADISE_MUSIC);
	score = 0;
}

int Game_paradise::Game(sf::RenderWindow& window, int& SCORE) {
	srand(time(0));
	window.setFramerateLimit(60);

	std::vector<std::vector<double>> platform(PLATFORM_NUM);
	for (size_t i = 0; i < PLATFORM_NUM; i++) {
		platform[i].push_back(rand() % WINDOW_WIDTH);
		platform[i].push_back(rand() % WINDOW_HEIGHT);
	}

	int start = 1;
	double rz = 0;
	double An = 0;

	while(rz < H_JUMP) {
		An += STEP;
		rz += An;
	}
	rz = An + 1;
	An = 0;
	sf::Font font;
	if (!font.loadFromFile("fonts/COURIER.TTF")) {
		return ERR_OF_FONT;
	}

	music.setLoop(true);
	music.play();

	while (1) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return GAME_STOP;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			x += PLAYER_A_X;
			if (x > WINDOW_WIDTH) {
				x = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			x -= PLAYER_A_X;
			if (x < 0) {
				x = WINDOW_WIDTH;
			}
		}
	
		An += STEP;
		y += An;
		if (y > WINDOW_HEIGHT - ANGEL_HEIGHT) {
			if (!start) {
				// std::cout << "Score: " << score << std::endl;
				SCORE += score;
				return PLAYER_DIED;
			}
			An =- rz;
		}

		if (y < H_JUMP) {
			for (size_t i = 0; i < PLATFORM_NUM; i++) {
				y = H_JUMP;
				platform[i][1] -= An;
				if (platform[i][1] > WINDOW_HEIGHT) {
					platform[i][1] = 0;
					platform[i][0] = rand() % WINDOW_WIDTH;
				}
			}
			start = 0;
		}

		for (size_t i = 0; i < PLATFORM_NUM; i++) {
			if ((x + ANGEL_WIDTH > platform[i][0]) &&
			  (x < platform[i][0] + PLATFORM_WIDTH) &&
			  (y + ANGEL_HEIGHT > platform[i][1]) &&
			  (y + ANGEL_HEIGHT < platform[i][1] + PLATFORM_HEIGHT)) {
				An =- rz;
				score++;
			}
		}

		window.clear();
		window.draw(background);
		hero.setPosition(x, y);

		sf::Text stat("Score: " + std::to_string(score), font);
		stat.setColor(FONT_COLOR);

		for (size_t i = 0; i < PLATFORM_NUM; i++) {
			cloud.setPosition(platform[i][0], platform[i][1]);
			window.draw(cloud);
		}
		window.draw(hero);
		window.draw(stat);
		window.display();
	}
	return 0;
}
