#include <iostream>
#include <math.h>

#include "game_hell.hpp"

Game_hell::Game_hell() {
	PLATFORM_SIZE = sf::Vector2f(WIDTH_PLATFORM, HEIGHT_PLATFORM);
	player_platform = new Platform(HEIGHT_PLATFORM, WIDTH_PLATFORM, HELL_LEFT_PLATFORM_SPRITE_SRC);
	bot_platform = new Platform(HEIGHT_PLATFORM, WIDTH_PLATFORM, HELL_RIGHT_PLATFORM_SPRITE_SRC);
	ball = new Ball(BALL_RADIUS, BALL_SPRITE_SRC);
	ballAngle = 0;
	player_platform->set_Position(sf::Vector2f(0, WINDOW_HEIGHT / 2));
	bot_platform->set_Position(sf::Vector2f(WINDOW_WIDTH - PLATFORM_SIZE.x, WINDOW_HEIGHT / 2));
	ball->set_Position(sf::Vector2f(200, WINDOW_HEIGHT / 2));
	b_sound.loadFromFile(HELL_SOUND_BALL_POKE);
	sound = sf::Sound(b_sound);
	music.openFromFile(HELL_MUSIC);
	score = 0;
}

int Game_hell::Game(sf::RenderWindow& window, int &SCORE) {
	srand(time(0));
	sf::Font font;
	if (!font.loadFromFile("fonts/COURIER.TTF")) {
		return ERR_OF_FONT;
	}
	music.setLoop(true);
	music.play();
	while (window.isOpen()) {
		sf::Event event;
		double timer = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if ((event.type == sf::Event::Closed)) {
				window.close();
				break;
			}
		}
		//  ход игрока
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (player_platform->get_Position().y > 0) {
				player_platform->Move(0, -PLATFORM_SPEED * timer);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (player_platform->get_Position().y + PLATFORM_SIZE.y < WINDOW_HEIGHT) {
				player_platform->Move(0, PLATFORM_SPEED * timer);
			}
		}
		//  ход противника
		if (!(ball->get_Position().y >= bot_platform->get_Position().y && ball->get_Position().y <= bot_platform->get_Position().y + PLATFORM_SIZE.y)) {
			if (ball->get_Position().y < bot_platform->get_Position().y) {
				bot_platform->Move(0, -PLATFORM_SPEED * timer);
			} else {
				bot_platform->Move(0, PLATFORM_SPEED * timer);
			}
		}

		double direction = BALL_SPEED * timer;
		ball->Move(cos(ballAngle) * direction, sin(ballAngle) * direction);
		if (ball->get_Position().x < 0) {
			// std::cout << "Проиграл" << std::endl;
			SCORE += (score / 2);
			return PLAYER_DIED;
		}
		if (ball->get_Position().x + ball->get_radius() > WINDOW_WIDTH) {
			// std::cout << "Выиграл" << std::endl;
			SCORE += score;
			return GAME_WIN;
		}
		if (ball->get_Position().y - ball->get_radius() < 0) {
			ballAngle = -ballAngle;
			ball->set_Position(sf::Vector2f(ball->get_Position().x, ball->get_radius() + 0.1));
		}
		if (ball->get_Position().y + ball->get_radius() > WINDOW_HEIGHT) {
			ballAngle = -ballAngle;
			ball->set_Position(sf::Vector2f(ball->get_Position().x, WINDOW_HEIGHT - ball->get_radius() - 0.1));
		}
		//  Толчок от платформы игрока
		if (ball->get_Position().x - ball->get_radius() < player_platform->get_Position().x + PLATFORM_SIZE.x / 2 &&
                ball->get_Position().x - ball->get_radius() > player_platform->get_Position().x &&
                ball->get_Position().y >= player_platform->get_Position().y &&
                ball->get_Position().y <= player_platform->get_Position().y + PLATFORM_SIZE.y) {
			if (ball->get_Position().y > player_platform->get_Position().y) {
				ballAngle = pi - ballAngle + (rand() % 20) * pi / 180;
			}
			else {
				ballAngle = pi - ballAngle - (rand() % 20) * pi / 180;
			}
			ball->set_Position(sf::Vector2f(player_platform->get_Position().x + ball->get_radius() + PLATFORM_SIZE.x / 2 + 0.1,
			  ball->get_Position().y));
			score += 1;
			sound.play();
		}
		//  Толчок от платформы противника
		if (ball->get_Position().x + ball->get_radius() > bot_platform->get_Position().x - PLATFORM_SIZE.x / 2 &&
		  ball->get_Position().x + ball->get_radius() < bot_platform->get_Position().x &&
		  ball->get_Position().y >= bot_platform->get_Position().y &&
		  ball->get_Position().y <= bot_platform->get_Position().y + PLATFORM_SIZE.y) {
			if (ball->get_Position().y > bot_platform->get_Position().y) {
				ballAngle = pi - ballAngle + ((10 + rand() % 20) * (10 + rand() % 20) % 20) * pi / 180;
			} else {
				ballAngle = pi - ballAngle - ((10 + rand() % 20) * (10 + rand() % 20) % 20) * pi / 180;
			}
			ball->set_Position(sf::Vector2f(bot_platform->get_Position().x - ball->get_radius() - PLATFORM_SIZE.x / 2 - 0.1,
			  ball->get_Position().y));
			score += 1;
			sound.play();
		}

		sf::Text stat("Score: " + std::to_string(score), font);
		stat.setColor(sf::Color::Red);

		sf::Texture st_bg;
		st_bg.loadFromFile(HELL_BG_SRC);
		sf::Sprite sh_bg(st_bg);

		window.clear();
		window.draw(sh_bg);
		window.draw(stat);
		window.draw(ball->get_s_platform());
		window.draw(player_platform->get_s_platform());
		window.draw(bot_platform->get_s_platform());
		window.display();
	}
	return 0;
}
