#include "main_menu.hpp"

void Main_menu::config_reader(std::string file_path) {
    std::ifstream fout(file_path, std::ios::in);
    if (!fout) {
        std::cerr << "\033[0;31m" << std::strerror(errno) << "\033[0m\n";
    }

    if (!font.loadFromFile("fonts/ocr_onectt.ttf")) {
        std::cerr << "\033[0;31m" << "--ФОНТЫ НЕ ЗАГРУЗИЛИСЬ" << "\033[0m\n";;
    }

    std::string buf;  // пукт подменю
    std::string buf_name;  // название подменю
    int buf_x, buf_y;  // расположение пунктов меню
    std::pair<sf::Text, sf::IntRect> buf_pair;  // пара текст и его обертка
    sf::Text buf_text;  // текст пункта меню

    buf_text.setFont(font);
    buf_text.setCharacterSize(FONT_SIZE_MENU_BUTTON_sm);
    buf_text.setColor(sf::Color(204, 204, 204));

    while(!fout.eof()) {
        fout >> buf;
        if (buf.back() == ':') {
            buf_name = buf;
            buf_name.pop_back();

            all_menu.emplace(buf_name, std::vector<std::pair<sf::Text, sf::IntRect>>());  // добавление подуровня в мапу

            levels.emplace_back(  // добавление соответствия в "словарь"
                buf_name, 
                sf::String::fromUtf8(buf_name.begin(), buf_name.end())
            );
        } else {
            fout >> buf_x >> buf_y;

            // блок о нас
            if (buf == "about") {
                buf_text.setString(L"Разработка квеста:\n    Владимир Атасунц  Кирилл Сметанкин\n    Ирина Никифорова\nХудожник:\n    Надежда Меркулова\nНаписание сюжета:\n    Ирина Никифорова\nРазработка мини-игр:\n    Надежда Меркулова  Владимир Атасунц\n    Кирилл Сметанкин");
                buf_text.setPosition(buf_x, buf_y);
                buf_pair = std::pair<sf::Text, sf::IntRect>(buf_text, sf::IntRect());
                all_menu.find(buf_name)->second.push_back(buf_pair);
                continue;
            }

            // борда лидеров
            if (buf == "leaderboard") {
                std::ifstream fout_board("data/records.txt", std::ios::in);
                if (!fout_board) {
                    std::cerr << "\033[0;31m" << std::strerror(errno) << "\033[0m\n";
                }

                size_t i = 0;  // top-10
                buf.clear();
                int num;
                std::string name;
                int score;
                std::string tmp;
                while(!fout_board.eof()) {
                    fout_board >> num >> name >> score;
                    if (name.empty()) {
                        break;
                    }

                    tmp = std::to_string(num) + " " + name + " " + std::to_string(score) + '\n';
                    buf += tmp;

                    i++;
                    name.clear();
                    
                    if (i == 10) {
                        break;
                    }
                }

                buf_text.setString(sf::String::fromUtf8(buf.begin(), buf.end()));
                buf_text.setPosition(buf_x, buf_y);
                buf_pair = std::pair<sf::Text, sf::IntRect>(buf_text, sf::IntRect());
                all_menu.find(buf_name)->second.push_back(buf_pair);

                fout_board.close();
                continue;
            }

            buf_text.setString(sf::String::fromUtf8(buf.begin(), buf.end()));
            buf_text.setPosition(buf_x, buf_y);

            buf_pair = std::pair<sf::Text, sf::IntRect>(
                buf_text,
                sf::IntRect(
                    buf_text.getGlobalBounds().left, 
                    buf_text.getGlobalBounds().top, 
                    buf_text.getGlobalBounds().width, 
                    buf_text.getGlobalBounds().height
                )
            );

            all_menu.find(buf_name)->second.push_back(buf_pair);
        }
    }
    fout.close();
}

Main_menu::Main_menu() {
    config_reader("configs/config.txt");

    title.setString("New_project_1");
    title.setFont(font);
    title.setColor(sf::Color::Black);
    title.setPosition(20, 20);
    title.setCharacterSize(FONT_SIZE_MENU_TITLE);

    user_level = "main";
    prev_user_level = "main";

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "new_game", sf::Style::Titlebar | sf::Style::Close);

    background_image.loadFromFile("images/back_img_supalong.png");
    background_texture.loadFromImage(background_image);
    background_sprite.setTexture(background_texture);
    background_sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));
    background_sprite.scale(1.7f, 1.7f);

    back_x = 0;
    move_back = 0.05;
    backgr_time = 0;

    move_text = 3;
    text_time = 0;

    moved_right = true;  // move_text_right_mid отработала
    moved_mid = false;  // move_text_right_left отработала

    music.openFromFile("sounds/menu_theme.ogg");
    music.setVolume(50);
}

void Main_menu::set_text_to_normal_size() {
    for (auto &text : vector_show) {
        text.first.setCharacterSize(FONT_SIZE_MENU_BUTTON_sm);
    }
}

void Main_menu::set_text_bigger(sf::RenderWindow &window) {
    for (auto &text : vector_show) {
        if (text.second.contains(sf::Mouse::getPosition(window))) {
            text.first.setCharacterSize(FONT_SIZE_MENU_BUTTON_bg);
            break;
        }
    }
}

int Main_menu::get_in(sf::RenderWindow &window, sf::Event event) {
    // 0 - ничего, 1 - вглубь, 2 - назад
    for (auto &text : vector_show) {
        if (text.second.contains(sf::Mouse::getPosition(window))) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (text.first.getString() == sf::String(L"<-Назад")) {  // проверка на НАЗАД
                    return 2;
                }
                
                // пока захардкодил, скорее так и останется
                if (user_level == "Миниигры" || text.first.getString() == sf::String(L"Сюжет")) {
                    // получаем текст, куда нажал пользователь
                    minigame_to_call = text.first.getString();

                    call_minigame();
                    music.play();  // после завершения миниигр продолжаем в музыку

                } else {              
                    for (auto &word : levels) {
                        if (word.second == text.first.getString()) {
                            prev_user_level = user_level;
                            user_level = word.first;

                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

bool Main_menu::move_text_right_mid(float cur_time) {
    // вернет false, когда текст выйдет за границы окна (справа)
    if (!moved_right) {
        text_time = cur_time - 1000;
    }
    float dT = (cur_time - text_time) / 800;
    text_time = cur_time;

    for (size_t i = 0; i < vector_show.size(); i++) {
        vector_show[i].first.move(move_text * dT, 0);

        if (vector_show[i].first.getPosition().x >= WINDOW_WIDTH) {
            vector_show = all_menu.find(user_level)->second;

            // обновляем позиции текста
            mid_pos_x = vector_show[0].first.getPosition().x;  // до какого момента сдвигаться
            
            for (auto &text : vector_show) {
                text.first.setPosition(-10, text.first.getPosition().y);
            }

            if (vector_show.back().first.getString() == sf::String(L"<-Назад")) {
                vector_show.back().first.setPosition(-210, vector_show.back().first.getPosition().y);  
            }
            return true;
        }
    }
    return false;
}

bool Main_menu::move_text_right_left(float cur_time) {
    // вернет true, когда встанет на свое место из конфига
    float dT = (cur_time - text_time) / 800;
    text_time = cur_time;

    for (size_t i = 0; i < vector_show.size(); i++) {
        if (vector_show[i].first.getPosition().x <= mid_pos_x) {
            vector_show[i].first.move(move_text * dT, 0);
        } else {
            return false;
        }
    }
    return true;
}

void Main_menu::call_minigame() {
    int PLAYER_HP = 100;
    int SCORE = 0;
    // ========ХАРДКООООД========
    if (minigame_to_call == sf::String(L"Викторина")) {
        music.pause();
        // создаем объект класса игры
        Quiz quiz_tmp;
        // вызываем его
        quiz_tmp.game_show(window, PLAYER_HP, SCORE);
        
        return;
    }

    if (minigame_to_call == sf::String(L"Лабиринт")) {
        music.pause();
        Game_lab gl;
        gl.Game(window, PLAYER_HP, SCORE);
        
        return;
    }

    if (minigame_to_call == sf::String(L"Flappy_witch")) {
        music.pause();
        FlappyWitch::Game gfw(&window);
        gfw.Run(PLAYER_HP, SCORE);

        return;
    }

    if (minigame_to_call == sf::String(L"Heavens_jump")) {
        music.pause();
        Game_paradise gp;
        gp.Game(window, SCORE);

        // удаление ограничения по кадрам из дудла
	    window.setFramerateLimit(0);
        
        return;
    }

    if (minigame_to_call == sf::String(L"Devil_pong")) {
        music.pause();
        Game_hell gh;
        gh.Game(window, SCORE);
	
        return;
    }

    if (minigame_to_call == sf::String(L"Сюжет")) {
        music.pause();
        Game game;
        game.draw(window);
	    window.setFramerateLimit(0);

        update_leaderboard();

        return;
    }

    // std::cout << "unknow game to call\n";
    std::cerr << "\033[0;31m" << "no game to call" << "\033[0m\n";
}

void Main_menu::update_leaderboard() {
    std::ifstream fout_board("data/records.txt", std::ios::in);
    if (!fout_board) {
        std::cerr << "\033[0;31m" << std::strerror(errno) << "\033[0m\n";
    }

    std::pair<sf::Text, sf::IntRect> buf_pair;  // пара текст и его обертка
    sf::Text buf_text;  // текст пункта меню
    
    buf_text.setFont(font);
    buf_text.setCharacterSize(FONT_SIZE_MENU_BUTTON_sm);
    buf_text.setColor(sf::Color(204, 204, 204));

    std::string buf;
    size_t i = 0;  // top-10

    int buf_x = 300;
    int buf_y = 120;

    // чистим старую борду
    all_menu.find("Рейтинг_игроков")->second.clear();

    int num;
    std::string name;
    int score;
    std::string tmp;

    while(!fout_board.eof()) {
        fout_board >> num >> name >> score;
        if (name.empty()) {
            
            break;
        }

        tmp = std::to_string(num) + " " + name + " " + std::to_string(score) + '\n';        
        buf += tmp;
        i++;
        name.clear();
        
        if (i == 10) {
            break;
        }
    } 

    buf_text.setString(sf::String::fromUtf8(buf.begin(), buf.end()));   
    buf_text.setPosition(buf_x, buf_y);
    buf_pair = std::pair<sf::Text, sf::IntRect>(buf_text, sf::IntRect());
    
    // запихуеваем
    all_menu.find("Рейтинг_игроков")->second.push_back(buf_pair);    
    // кнопка назад
    buf = "<-Назад";
    buf_x = 100;
    buf_y = 500;

    buf_text.setString(sf::String::fromUtf8(buf.begin(), buf.end()));
    buf_text.setPosition(buf_x, buf_y);

    buf_pair = std::pair<sf::Text, sf::IntRect>(
        buf_text,
        sf::IntRect(
            buf_text.getGlobalBounds().left, 
            buf_text.getGlobalBounds().top, 
            buf_text.getGlobalBounds().width, 
            buf_text.getGlobalBounds().height
        )
    );

    all_menu.find("Рейтинг_игроков")->second.push_back(buf_pair);

    fout_board.close();
}


void Main_menu::menu_show() {
    music.play();  // воспроизводим музыку
    vector_show = all_menu.find(user_level)->second; 

    float cur_time = 0;  // текущее время работы окна
	sf::Clock clock;

    int need_move = 0;  // надо двигать текст

    while (window.isOpen()) {
        cur_time = clock.getElapsedTime().asMicroseconds(); 
        
        set_text_to_normal_size();  // возвращает все подменюшки к 32 размеру
        set_text_bigger(window);  // увеливает при наведении до 36 размера
        move_background(cur_time);  // двигает background

        sf::Event event;        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;                
            }

            need_move = get_in(window, event);  // переход в подменю по ЛКМ
            if (need_move == 1) {
                moved_right = false;
            }
            
            // вверх по меню по ESC или "<-Назад"
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || need_move == 2) {
                user_level = prev_user_level;
                moved_right = false;
            }
        }        
        
        if (!moved_right) {
            moved_right = move_text_right_mid(cur_time);
            moved_mid = moved_right;  // наоброт
        }
        if (moved_mid) {
            moved_mid = move_text_right_left(cur_time);
        }
         
        window.clear();
        window.draw(background_sprite);

        for (auto &text : vector_show) {
            window.draw(text.first);
        }

        window.draw(title);
        window.display();
    }
    return;
}

void Main_menu::move_background(float cur_time) {
    float dT = (cur_time - backgr_time) / 800;
    backgr_time = cur_time;
    
    back_x += move_back * dT;
    if (back_x >= 1812) {
        back_x = 0;
    }
    background_sprite.setTextureRect(sf::IntRect(back_x, 0, 960, 640));
}
