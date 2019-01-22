#include <iostream>
#include <fstream>

#include "finish.hpp"
#include "entry.hpp"
#include "animation.hpp"

Finish::Finish(int& xp) {
	this->xp = xp;	
}

void Finish::take_records(std::string name) {
	std::ifstream data(name);
	records.process(data);
	// records.print();
}

void Finish::show(sf::RenderWindow& window) {
	take_records();
	sf::Text result;
	sf::Text place;
	sf::Event event;
	sf::Font font = GET_FONT();
	double BG_ANIM = 0;
	int num;		
	Entry field;

	bool name_pushed = 0;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				return;
			}
			if (event.type == sf::Event::TextEntered) {
				if (field.get_state() == 1) {
					if (event.text.unicode < 128 ) {
						char c = static_cast<char>(event.text.unicode); 
						field.draw(window, font, c);
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && field.get_state() != 2) {
				int a = sf::Mouse::getPosition(window).x;
				int b = sf::Mouse::getPosition(window).y;
				if (field.in_rect(a, b)) {
					field.make_active();
				} else {
					field.make_inactive();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && field.get_state() == 1)  {
				if (name_pushed == 0) {
				field.make_enter_finished();
					name = field.get_str();
					num = records.insert_by_value(name, xp);
					// std::cout << "Name is: " << name << num << std::endl;
					// records.print();
					name_pushed = 1;
					std::wstring pl_string = std::to_wstring(num);
					std::wstring place_string = L"Сегодня вы на: " + pl_string + L" месте. Поздравляем!";
					place.setString(place_string);
				}
			}
		}

		window.clear();
		sf::Texture t_podl;
		t_podl.loadFromFile("images/back_img_1.png");
		sf::Sprite s_podl(t_podl);		
		window.draw(s_podl);

		sf::Texture t_bg;
		t_bg.loadFromFile("data/backgrounds/bg_torch.png");
		sf::Sprite s_bg(t_bg);
		BG_ANIM += ANIM_SPEED;
		if (BG_ANIM > 3) {
			BG_ANIM -= 3;
		}
		s_bg.setTextureRect(sf::IntRect(WINDOW_WIDTH * static_cast<int>(BG_ANIM), 0,
				WINDOW_WIDTH, WINDOW_HEIGHT));
		s_bg.setPosition(0, 0);
		window.draw(s_bg);

		std::wstring xp_string = std::to_wstring(xp);
		std::wstring result_string = L"Ваш результат: " + xp_string /*+ L". Пожалуйста, впишите Ваше имя ниже."*/;
		
		result.setFont(font);
		result.setString(result_string);
		result.setCharacterSize(FONT_SIZE);
		result.setColor(FONT_COLOR_1);
		result.setPosition(300, 300);
		window.draw(result);
		field.draw(window, font);
		sf::Text field_text;
		field_text.setFont(font);
		field_text.setString(field.str);
		field_text.setCharacterSize(FONT_SIZE);
		field_text.setColor(FONT_COLOR_1);
		field_text.setPosition(field.x + 3, field.y + 3);
		window.draw(field_text);
		
		place.setFont(font);
		place.setCharacterSize(FONT_SIZE);
		place.setColor(FONT_COLOR_1);
		place.setPosition(300, 500);

		if (name_pushed == 1) {
			if (num != 0) {
				window.draw(place);
				std::ofstream data_out(RECORDS_SRC);
				records.save(data_out);
			}
		}	
		window.display();
		
	}		
}
