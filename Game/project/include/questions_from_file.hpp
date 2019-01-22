#ifndef PROJECT_INCLUDE_QUESTIONS_FROM_FILE_HPP_
#define PROJECT_INCLUDE_QUESTIONS_FROM_FILE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include "questions.hpp"
#include "definitions.hpp"


// void next_question(sf::Text &question, sf::Text &anwser_a, sf::Text &anwser_b, sf::Text &anwser_c, sf::Text &anwser_d);

void map_gen(std::map <int, Question> &question_map);  // рандомные вопросы

void print_map(std::map <int, Question> &Map_to_print);

// вставляет в вектор первый элемент из мапы и удаляет его
void get_text_vector(std::map <int, Question> &question_map, std::vector <sf::Text> &text_vector, sf::Font &font, int &right_answer);

void update_intrects(std::vector <sf::Text> &text_vector, std::vector <sf::IntRect> &intrect_vector);

void set_text_positions(std::vector <sf::Text> &text_vector);

void update_wrapper(std::vector <sf::Text> &text_vector, std::vector <sf::ConvexShape> &wrapper_vector);

// реакции дракона на ответы, answer = true - правильный ответ, end = true - вопросов больше нет
void set_response_on_answer(std::vector <sf::Text> &text_vector, bool answer, bool end);

#endif  // PROJECT_INCLUDE_QUESTIONS_FROM_FILE_HPP_