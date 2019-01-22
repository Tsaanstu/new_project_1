#ifndef PROJECT_INCLUDE_MAIN_MENU_HPP_
#define PROJECT_INCLUDE_MAIN_MENU_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>
#include "definitions.hpp"
#include "quiz.hpp"  // quiz - minigame
#include "GameFW.hpp"  // flappy_witch - minigame
#include "game_lab.hpp"  // labirint - minigame
#include "game_hell.hpp"  // hell - minigame
#include "game_paradise.hpp"  // paradise - minigame
#include "game.hpp"  // game - plot
#include <fstream>
#include <cstring>

class Main_menu {
 public:
    Main_menu();
    void config_reader(std::string file_path);

    void menu_show();
    
    void set_text_to_normal_size();  // возвращает размер текста то стандарта
    void set_text_bigger(sf::RenderWindow &window);  // увеличивает размер при наведении
    int get_in(sf::RenderWindow &window, sf::Event event);  // уйти в подуровень
    void move_background(float cur_time);  // функция перемещения подложки

    bool move_text_right_mid(float cur_time);  // сдвиг текста из середины вправо, в конце обновляет vector_show
    bool move_text_right_left(float cur_time);
    void call_minigame();  // вызов миниигр
    void update_leaderboard();  // обновления списка лидеров в мапе
 private:
    sf::Font font;
    sf::Text title;
    
    std::map <std::string, std::vector <std::pair<sf::Text, sf::IntRect>>> all_menu;
    std::vector <std::pair<sf::Text, sf::IntRect>> vector_show;  // тмп, что отображать

    // тк из sf::Text в string русские символы хуй переведешь, 
    // будут пары, чтобы понять на какой уровень перейти
    std::vector <std::pair<std::string, sf::String>> levels;  // уровни

    std::string user_level;
    std::string prev_user_level;
    
    sf::RenderWindow window;

    sf::String minigame_to_call;

    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    float back_x;  // положение х бэкграунда
    float move_back;  // перемещения по х бэкграунда
    float backgr_time;  // время предыдущего сдвига фона

    float move_text;  // сдвиг текста за итерацию по x
    float text_time;  // время предыдущего сдвига текста

    float mid_pos_x;  // х текста в меню

    bool moved_right;  // move_text_right_mid отработала
    bool moved_mid;  // move_text_right_left отработала
    sf::Music music;  // создаем объект музыки
};

#endif  // PROJECT_INCLUDE_MAIN_MENU_HPP_
