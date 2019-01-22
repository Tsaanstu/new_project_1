#include "quiz.hpp"

Quiz::Quiz() {
    map_gen(question_map);

    font.loadFromFile("fonts/ocr_onectt.ttf");

    hp_show.setFont(font);
    hp_show.setColor(sf::Color::Black);
    hp_show.setPosition(5, 5);
    hp_show.setCharacterSize(20);

    score_show.setFont(font);
    score_show.setColor(sf::Color::Black);
    score_show.setPosition(5, 25);
    score_show.setCharacterSize(20);

    dragon_image.loadFromFile("images/dragon_animation.png");
    dragon_texture.loadFromImage(dragon_image);
    dragon_sprite.setTexture(dragon_texture);
    dragon_sprite.setTextureRect(sf::IntRect(0, 0, 300, 300));
    dragon_sprite.setPosition(900, 100);

    background_image.loadFromFile("images/quiz_back.png");
    background_texture.loadFromImage(background_image);
    background_sprite.setTexture(background_texture);
    background_sprite.scale(1.0f, 1.0f);

    text_vector.resize(5);
    get_text_vector(question_map, text_vector, font, right_answer_num);
    set_text_positions(text_vector);

    update_intrects(text_vector, intrect_vector);

    update_wrapper(text_vector, wrapper_vector);
    
    current_frame = 0;

    music.openFromFile("sounds/quiz_2.ogg");
    music.setVolume(100);
    music.setLoop(true);
}

void Quiz::dragon_move() {
    current_frame++;
    if (current_frame > 5) {
        current_frame = 0;
    }
    dragon_sprite.setTextureRect(sf::IntRect(int(current_frame) * 300, 0, 300, 300));

    // движение дракона по вертикали при взмахе крыльев
    if (current_frame <= 3) {
        dragon_sprite.setPosition(dragon_sprite.getPosition().x, dragon_sprite.getPosition().y - 0.015);
    } else {
        dragon_sprite.setPosition(dragon_sprite.getPosition().x, dragon_sprite.getPosition().y + 0.02);                
    }
}

void Quiz::game_show(sf::RenderWindow &window, int &hp, int &score) {
    int user_answer = 0;
    float time;  // время анимации дракона
	sf::Clock clock;
	sf::Clock clock_res;
    float time_res;
    
    bool mouse_in_rect = false;
    bool mouse_in_rect_a = false;
    bool mouse_in_rect_b = false;
    bool mouse_in_rect_c = false;
    bool mouse_in_rect_d = false;

    bool response = false;
    bool end = false;

    music.play();
    while (window.isOpen()) {
        mouse_in_rect = false;
        mouse_in_rect_a = false;
        mouse_in_rect_b = false;
        mouse_in_rect_c = false;
        mouse_in_rect_d = false;

        // вывод строки состояни ГГ
        hp_show.setString("hp: " + std::to_string(hp));
        score_show.setString("score: " + std::to_string(score));

        for (auto& wrapper : wrapper_vector) {
            wrapper.setFillColor(sf::Color(221, 193, 199));
        }
        
        if (response) {
            get_text_vector(question_map, text_vector, font, right_answer_num);
            set_text_positions(text_vector);
            
            update_intrects(text_vector, intrect_vector);
            update_wrapper(text_vector, wrapper_vector);
            response = false;
        }

        if (intrect_vector[0].contains(sf::Mouse::getPosition(window))) {
            wrapper_vector[1].setFillColor(sf::Color(157, 130, 153));
            mouse_in_rect_a = true;
            mouse_in_rect = true;
        }

        if (intrect_vector[1].contains(sf::Mouse::getPosition(window))) {
            wrapper_vector[2].setFillColor(sf::Color(157, 130, 153));
            mouse_in_rect_b = true;
            mouse_in_rect = true;            
        }

        if (intrect_vector[2].contains(sf::Mouse::getPosition(window))) {
            wrapper_vector[3].setFillColor(sf::Color(157, 130, 153));
            mouse_in_rect_c = true;
            mouse_in_rect = true;            
        }

        if (intrect_vector[3].contains(sf::Mouse::getPosition(window))) {
            wrapper_vector[4].setFillColor(sf::Color(157, 130, 153));
            mouse_in_rect_d = true;
            mouse_in_rect = true;            
        }
        
        // ---анимация дракона---
        time = clock.getElapsedTime().asMicroseconds(); 
		time = time / 800; 

        if (time > 250.0) {
		    clock.restart();
            dragon_move();
        }
        
        sf::Event event;        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;                
            }

            if ((event.type == sf::Event::MouseButtonPressed && mouse_in_rect == true)) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mouse_in_rect_a == true) {
                        user_answer = 1;
                    }
                    if (mouse_in_rect_b == true) {
                        user_answer = 2;
                    }
                    if (mouse_in_rect_c == true) {
                        user_answer = 3;
                    }
                    if (mouse_in_rect_d == true) {
                        user_answer = 4;
                    }

                    if (user_answer == right_answer_num) {
                        score += 10;  // добавление очков за правильный ответ

                        if (question_map.empty()) {  // ответ правильный и вопросы закончились
                            end = true;
                            response = true;

                            set_response_on_answer(text_vector, true, true);
                            update_wrapper(text_vector, wrapper_vector);

                        } else {  // ответ правильный и вопросы остались
                            response = true;

                            set_response_on_answer(text_vector, true, false);
                            update_wrapper(text_vector, wrapper_vector);
                        }
                        
                    } else {  // ответ неправильный и вопросы закончились
                        hp -= 10;  // вычет хп(или пальцев) у плеера за неправильный ответ

                        if (question_map.empty()) {
                            end = true;
                            response = true;

                            set_response_on_answer(text_vector, false, true);
                            update_wrapper(text_vector, wrapper_vector);
    
                        } else {  // ответ неправильный и вопросы остались
                            response = true;

                            set_response_on_answer(text_vector, false, false);
                            update_wrapper(text_vector, wrapper_vector);
                        }                                                      
                    }
                }
            }
        }
        
        window.clear();
        window.draw(background_sprite);
	    window.draw(dragon_sprite);

        for (auto& wrapper : wrapper_vector) {
            window.draw(wrapper);
        }

        for (auto& text : text_vector) {
            window.draw(text);
        }

        window.draw(score_show);
        window.draw(hp_show);

        window.display();

        if (response) {
            clock_res.restart();
            do {
                time_res = clock_res.getElapsedTime().asMicroseconds(); 
                time_res = time_res / 800; 

                time = clock.getElapsedTime().asMicroseconds(); 
                time = time / 800; 

                if (time > 250.0) {
                    clock.restart();
                    dragon_move();
                }

                window.clear();
                window.draw(background_sprite);
                window.draw(dragon_sprite);

                for (auto& wrapper : wrapper_vector) {
                    window.draw(wrapper);
                }

                for (auto& text : text_vector) {
                    window.draw(text);
                }

                window.draw(score_show);
                window.draw(hp_show);

                window.display();
            } while (time_res < 1500);
            
            if (end) {
                // std::cout << "quiz ended\n";
                return;
            }
        }
    }
}
