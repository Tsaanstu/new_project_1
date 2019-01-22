#ifndef PROJECT_INCLUDE_QUIZ_MER_HPP_
#define PROJECT_INCLUDE_QUIZ_MER_HPP_

#include <SFML/Graphics.hpp>
#include "questions.hpp"
#include "questions_from_file.hpp"

class Quiz_mr {
 public:
    Quiz_mr();
    void game_show(sf::RenderWindow &window, int &hp, int &score);
    void dragon_move();  // управлеяет движениями дракона
 private:
    std::map <int, Question> question_map;
    int right_answer_num;

    sf::Font font;

    sf::Image dragon_image;
    sf::Texture dragon_texture;
    sf::Sprite dragon_sprite;

    sf::Image background_image;
    sf::Texture background_texture;
    sf::Sprite background_sprite;

    std::vector <sf::Text> text_vector;  // вектор вопросов и ответов
    std::vector <sf::IntRect> intrect_vector;  // вектор прямоугольников, содержащих текст
    std::vector <sf::ConvexShape> wrapper_vector;  // вектор 6-угольников вокруг ответов
    
    int hp_before;  // хп игрока до начала игры
    sf::Text hp_show;
    sf::Text score_show;
    int current_frame;  // номер текущего фрейма дракона

    sf::Music music;  // создаем объект музыки
};

#endif  // PROJECT_INCLUDE_QUIZ_MER_HPP_
