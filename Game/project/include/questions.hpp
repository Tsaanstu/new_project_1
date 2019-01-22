#ifndef PROJECT_INCLUDE_QUESTIONS_HPP_
#define PROJECT_INCLUDE_QUESTIONS_HPP_

#include <iostream>
#include <fstream>
#include <cstring>
#include <SFML/Graphics.hpp>

class Question {
 public:
    // может кинуть exception (bad argument), если неправильный путь к файлу
    Question(std::string file_name);
    sf::String get_question();  // возвращает строку со \n по ширине окна
    sf::String get_answer_a();
    sf::String get_answer_b();
    sf::String get_answer_c();
    sf::String get_answer_d();
    int get_right_anser(); 

    void set_quetsion(const sf::String &str);
    void set_answer_a(const sf::String &str);
    void set_answer_b(const sf::String &str);
    void set_answer_c(const sf::String &str);
    void set_answer_d(const sf::String &str);
    void set_right_answer(const int &num);
 private:
    sf::String question;
    sf::String answer_a;
    sf::String answer_b;
    sf::String answer_c;
    sf::String answer_d;
    int right_answer;
};
#endif  // PROJECT_INCLUDE_QUESTIONS_HPP_