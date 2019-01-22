#include "game.hpp"

int Game::draw(sf::RenderWindow& window) {
	sf::Font font;
	if (!font.loadFromFile("fonts/COURIER.TTF")) {
		return ERR_OF_FONT;
	}
	std::vector<int> GAME_LEVEL(4);
	for(size_t i = 0; i < 4; i++) {
		GAME_LEVEL[i] = 0;
	}
	int PLAYER_HP = 100;
	int SCORE = 0;
	double BG_ANIM = 0;
	int gs = 0;
	Player_moves moves;
	moves.input_moves();
	int make_a_move = 1;
	sf::Text temp_t;

	b_dragon_sound.loadFromFile("sounds/ZD.ogg");
	dragon_sound = sf::Sound(b_dragon_sound);
	music.openFromFile("sounds/KR.ogg");

	std::vector<Button> buttons = move(make_a_move, &moves, font);
	std::vector<Animation> animation;
	animation.push_back(Animation(130, 120, BORDER_WIDTH + 6, BORDER_WIDTH + 6, "images/animation1.png", 520, 0.02));
	animation.push_back(Animation(130, 120, WINDOW_WIDTH - 3.5 * BORDER_WIDTH - 30, BORDER_WIDTH + 5, "images/animation2.png", 520, 0.02));

	Animation *bg_picture = new Animation(PICTURE_MODULE_WIDTH, PICTURE_MODULE_HEIGHT,
		WINDOW_WIDTH / 2 - PICTURE_MODULE_WIDTH / 2,
		BORDER_WIDTH, moves.get_picture_link(make_a_move), 2700, ANIM_SPEED);
	music.setLoop(true);
	music.play();
	while (window.isOpen()) {
		int mouse_in_rect = 0;
		size_t choose = 10;

		bg_picture->activate();
		create_button(buttons);
		mouse_in_rect = mouse_in_button(buttons, window, &choose);
		for (size_t i = 0; i < animation.size(); i++) {
			if (animation[i].mouse_in_anim(window) == 1) {
				animation[i].activate();
				animation[i].set_anim(0);
				dragon_sound.stop();
				dragon_sound.play();
			}
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && mouse_in_rect == 1) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (moves.choose_move(make_a_move, choose) > 1000) {
						music.pause();
						on_minigame(moves.choose_move(make_a_move, choose) % 1000, window, PLAYER_HP, SCORE);
						music.play();
						if (PLAYER_HP <= 0) {
							PLAYER_HP = 0;
						}
						if (PLAYER_HP == 0 && make_a_move < 1008 && gs == 0) {
							make_a_move = 1009 + rand() % 2;
							gs = 1;
						} else {
							make_a_move = moves.choose_move(make_a_move, 0);
						}
						buttons = move(make_a_move, &moves, font);
					} else {
						make_a_move = moves.choose_move(make_a_move, choose);
						
						if (make_a_move == 66) {
							moves.rebuild_command(66, GAME_LEVEL);
						}

						buttons = move(make_a_move, &moves, font);
						if (moves.get_picture_link(make_a_move) != PICTURE_LINK) {
							delete bg_picture;
							bg_picture = new Animation(PICTURE_MODULE_WIDTH, PICTURE_MODULE_HEIGHT,
								WINDOW_WIDTH / 2 - PICTURE_MODULE_WIDTH / 2,
								BORDER_WIDTH, moves.get_picture_link(make_a_move), 2700, ANIM_SPEED);
							bg_picture->activate();
						}
					}
				}
			}
		}

		if (make_a_move == 1008) {
			return 0;
		}

		switch(make_a_move) {
			case 59:
				GAME_LEVEL[0] = 1;
				break;
			case 69:
				GAME_LEVEL[1] = 1;
				break;
			case 68:
				GAME_LEVEL[2] = 1;
				break;
			case 67:
				GAME_LEVEL[3] = 1;
				break;
		}
		int temp_l_m = 4;
		for(size_t i = 0; i < 4; i++) {
			if (GAME_LEVEL[i] != 0) {
				temp_l_m--;
			}
		}
		if (temp_l_m == 0 && gs != 3) {
			gs = 3;
			make_a_move = 70;
			SCORE += 1000;
			continue;
		}

		window.clear(WINDOW_COLOR);
		//  Подложка
		sf::Texture t_podl;
		t_podl.loadFromFile("images/back_img_1.png");
		sf::Sprite s_podl(t_podl);		
		window.draw(s_podl);

		//  Фон
		if (moves.get_background_link(make_a_move) != BACKGROUND_LINK) {
			sf::Texture t_bg;
			t_bg.loadFromFile(moves.get_background_link(make_a_move));
			sf::Sprite s_bg(t_bg);
			BG_ANIM += ANIM_SPEED;
			if (BG_ANIM > 3) {
				BG_ANIM -= 3;
			}
			s_bg.setTextureRect(sf::IntRect(WINDOW_WIDTH * static_cast<int>(BG_ANIM), 0,
				WINDOW_WIDTH, WINDOW_HEIGHT));
			s_bg.setPosition(0, 0);
			window.draw(s_bg);
		}
		//  Текст
		sf::Text history = output_history(moves, font, make_a_move);
		history.setFont(font);
		history.setCharacterSize(FONT_SIZE);
		window.draw(history);
		//  Картинка
		if (moves.get_picture_link(make_a_move) != PICTURE_LINK) {
			if (bg_picture->get_status() == 1) {
				bg_picture->tik();
			}
			window.draw(bg_picture->get_s_animation());
		}
		//  Анимация
		for (size_t i = 0; i < animation.size(); i++) {
			if (animation[i].get_status() == 1) {
				animation[i].tik();
			}
		}
		for (size_t i = 0; i < animation.size(); i++) {
			window.draw(animation[i].get_s_animation());
		}
		//  Кнопки
		for (size_t i = 0; i < buttons.size(); i++) {
			window.draw(buttons[i].get_text());
        	}
		//  HP & XP
		sf::Text stat_HP("hp: " + std::to_string(PLAYER_HP), font);
		std::string s_S_s = "score: " + std::to_string(SCORE);
		sf::Text stat_Score(s_S_s, font);

		stat_HP.setPosition(sf::Vector2f(BORDER_WIDTH,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT / 2));
		stat_HP.setColor(FONT_COLOR_1);
		window.draw(stat_HP);
		stat_Score.setPosition(sf::Vector2f(WINDOW_WIDTH - BORDER_WIDTH -
			s_S_s.size() * 20,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT / 2));
		stat_Score.setColor(FONT_COLOR_1);
		window.draw(stat_Score);

		window.display();
	}
	return 0;
}

sf::Text Game::output_history(Player_moves moves, sf::Font& font, int make_a_move) {
	sf::Text history;
	std::string string_his = moves.get_story(make_a_move);
	std::basic_string<sf::Uint32> tmp;
	sf::Utf8::toUtf32(string_his.begin(),
		string_his.end(), std::back_inserter(tmp));
	int j = 0;
	for (size_t i = 0; i < tmp.size(); i++) {
		j++;
		if (j == 70) {
			j = i;
			while (tmp[j] != ' ') {
				j--;
			}
			tmp[j] = '\n';
			j = 0;
		}
	}
	history.setFont(font);
	history.setString(tmp);
	history.setCharacterSize(FONT_SIZE);
	history.setColor(FONT_COLOR_1);
	history.setPosition(0.1 * WINDOW_WIDTH, WINDOW_HEIGHT / 3 + BORDER_WIDTH);
	return history;
}

int Game::mouse_in_button(std::vector<Button>& buttons, sf::RenderWindow& window, size_t* choose) {
	int mouse_in_rect = 0;
	for(size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].get_int_rect().contains(sf::Mouse::getPosition(window))) {
			sf::Text temp_t = buttons[i].get_text();
			temp_t.setColor(FONT_COLOR_1);
			buttons[i].set_text(temp_t);
			*choose = i;
			mouse_in_rect = 1;
		}
	}
	return mouse_in_rect;
}

void Game::create_button(std::vector<Button>& buttons) {
	for(size_t i = 0; i < buttons.size(); i++) {
		sf::Text temp_t = buttons[i].get_text();
		temp_t.setColor(FONT_COLOR_1);
		buttons[i].set_text(temp_t);
	}
}

void Game::on_minigame(int mg_id, sf::RenderWindow& window, int& PLAYER_HP, int& SCORE) {
	Game_lab gl;
	Quiz gq;
	Quiz_mr qmg;
	FlappyWitch::Game gfw(&window);;
	Game_hell gh;
	Game_paradise gp;
	Finish fin(SCORE);
	switch (mg_id) {
		case 1:
			gl.Game(window, PLAYER_HP, SCORE, 2);
			break;
		case 2:
			gq.game_show(window, PLAYER_HP, SCORE);
			break;
		case 3:
			gfw.Run(PLAYER_HP, SCORE, TREES_AMOUNT_TO_WIN);
			break;
		case 4:
			gl.Game(window, PLAYER_HP, SCORE);
			break;
		case 5:
			qmg.game_show(window, PLAYER_HP, SCORE);
			break;
		case 6:
			gp.Game(window, SCORE);
			break;
		case 7:
			gh.Game(window, SCORE);
			break;
		case 8:
			fin.show(window);
			break;
	}
}

std::vector<Button> Game::move(int make_a_move, Player_moves *moves, sf::Font &font) {
	std::vector<std::string> commands = moves->get_commands(make_a_move);
	std::vector<Button> buttons;

	std::vector<int> bit_level(4);

	for(size_t i = 0; i < commands.size(); i++) {
		sf::Text text_command;
		std::basic_string<sf::Uint32> tmp;
		sf::Utf8::toUtf32(commands[i].begin(),
			commands[i].end(), std::back_inserter(tmp));
		text_command.setFont(font);
		text_command.setString(tmp);
		text_command.setCharacterSize(FONT_SIZE);
		text_command.setColor(FONT_COLOR_1);

		buttons.push_back(Button(text_command));
	}

	for(size_t i = 0; i < commands.size(); i++) {
		buttons[i].set_width(buttons[i].get_text().getGlobalBounds().width);
		buttons[i].set_height(buttons[i].get_text().getGlobalBounds().height);
	}

	buttons_draw(buttons);

	for(size_t i = 0; i < buttons.size(); i++) {
		sf::IntRect intrect(buttons[i].get_text().getGlobalBounds().left, 
			buttons[i].get_text().getGlobalBounds().top, 
			buttons[i].get_text().getGlobalBounds().width, 
			buttons[i].get_text().getGlobalBounds().height);
		buttons[i].set_int_rect(intrect);
	}

	return buttons;
}

void Game::buttons_draw(std::vector<Button>& buttons) {
	sf::Text v1, v2, v3;
	switch (buttons.size()) {
		case 1:
			v1 = buttons[0].get_text();
			v1.setPosition(WINDOW_WIDTH / 2 - buttons[0].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT / 2);
			buttons[0].set_text(v1);
			break;
		case 2:
			v1 = buttons[0].get_text();
			v2 = buttons[1].get_text();
			v1.setPosition(WINDOW_WIDTH / 2 - buttons[0].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT + 20);

			v2.setPosition(WINDOW_WIDTH / 2 - buttons[1].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT / 2 - 20);

			buttons[0].set_text(v1);
			buttons[1].set_text(v2);
			break;
		default:
			v1 = buttons[0].get_text();
			v2 = buttons[1].get_text();
			v3 = buttons[2].get_text();
			v1.setPosition(WINDOW_WIDTH / 2 - buttons[0].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT);

			v2.setPosition(WINDOW_WIDTH / 2 - buttons[0].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT + buttons[0].get_height() + COMMAND_MODULE_INTERVAL);


			v3.setPosition(WINDOW_WIDTH / 2 - buttons[0].get_width() / 2,
			WINDOW_HEIGHT - COMMAND_MODULE_HEIGHT + buttons[0].get_height() + buttons[1].get_height()
			 + COMMAND_MODULE_INTERVAL * 2);


			buttons[0].set_text(v1);
			buttons[1].set_text(v2);
			buttons[2].set_text(v3);
			break;
	}
}
