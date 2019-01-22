#include "questions_from_file.hpp"

void map_gen(std::map <int, Question> &question_map) {
    int j;
    int i = 0;
    srand(time(0));
    while(i < 5) {
        j = 1 + rand() % 12;
        if (question_map.find(j) != question_map.end()) {
            continue;
        } else {
            question_map.emplace(j, Question(std::to_string(j) + ".txt"));
            i++;
        }
    }
}

void print_map(std::map <int, Question> &Map_to_print) {
    int k = 0;
    for (auto it = Map_to_print.begin(); it != Map_to_print.end(); ++it, k++) {
        std::cout << k << "|" << it->first << "|" << it->second.get_question().toAnsiString() << std::endl;
    }
}

void get_text_vector(std::map <int, Question> &question_map, std::vector <sf::Text> &text_vector, sf::Font &font, int &right_answer) {
    // вопрос
    text_vector[0].setFont(font);
    text_vector[0].setString(question_map.begin()->second.get_question());
    text_vector[0].setCharacterSize(24);
    text_vector[0].setColor(sf::Color::Black);

    // текст ответа А
    text_vector[1].setFont(font);
    text_vector[1].setString(question_map.begin()->second.get_answer_a());
    text_vector[1].setCharacterSize(24);
    text_vector[1].setColor(sf::Color::Black);

    // текст ответа В
    text_vector[2].setFont(font);
    text_vector[2].setString(question_map.begin()->second.get_answer_b());
    text_vector[2].setCharacterSize(24);
    text_vector[2].setColor(sf::Color::Black);

    // текст ответа С
    text_vector[3].setFont(font);
    text_vector[3].setString(question_map.begin()->second.get_answer_c());
    text_vector[3].setCharacterSize(24);
    text_vector[3].setColor(sf::Color::Black);

    // текст ответа D
    text_vector[4].setFont(font);
    text_vector[4].setString(question_map.begin()->second.get_answer_d());
    text_vector[4].setCharacterSize(24);
    text_vector[4].setColor(sf::Color::Black);

    // правильный ответ
    right_answer = question_map.begin()->second.get_right_anser();

    question_map.erase(question_map.begin());
}

void set_text_positions(std::vector <sf::Text> &text_vector) {
    text_vector[0].setPosition(250, 110);

    float text_y = 3.0/4 * WINDOW_HEIGHT - text_vector[1].getGlobalBounds().height - 20;
    float text_x = 1.0/4 * WINDOW_WIDTH - text_vector[1].getGlobalBounds().width / 2.0;
    text_vector[1].setPosition(text_x, text_y);

    text_y = 3.0/4 * WINDOW_HEIGHT - text_vector[2].getGlobalBounds().height - 20;
    text_x = 3.0/4 * WINDOW_WIDTH - text_vector[2].getGlobalBounds().width / 2.0;
    text_vector[2].setPosition(text_x, text_y);

    text_y = 3.0/4 * WINDOW_HEIGHT + text_vector[3].getGlobalBounds().height + 40;
    text_x = 1.0/4 * WINDOW_WIDTH - text_vector[3].getGlobalBounds().width / 2.0;
    text_vector[3].setPosition(text_x, text_y);

    text_y = 3.0/4 * WINDOW_HEIGHT + text_vector[4].getGlobalBounds().height + 40;
    text_x = 3.0/4 * WINDOW_WIDTH - text_vector[4].getGlobalBounds().width / 2.0;
    text_vector[4].setPosition(text_x, text_y);

}

void update_intrects(std::vector <sf::Text> &text_vector, std::vector <sf::IntRect> &intrect_vector) {
    intrect_vector.clear();
    
    if (!text_vector[1].getString().isEmpty()) {
        // прямоугольник, содерж ответ A    
        intrect_vector.push_back(sf::IntRect(text_vector[1].getGlobalBounds().left - 15, text_vector[1].getGlobalBounds().top - 10,
                    text_vector[1].getGlobalBounds().width + 30, text_vector[1].getGlobalBounds().height + 20));
    }
    
    if (!text_vector[2].getString().isEmpty()) {
        // прямоугольник, содерж ответ В
        intrect_vector.push_back(sf::IntRect(text_vector[2].getGlobalBounds().left - 15, text_vector[2].getGlobalBounds().top - 10,
                    text_vector[2].getGlobalBounds().width + 30, text_vector[2].getGlobalBounds().height + 20));
    }

    if (!text_vector[3].getString().isEmpty()) {
        // прямоугольник, содерж ответ C
        intrect_vector.push_back(sf::IntRect(text_vector[3].getGlobalBounds().left - 15, text_vector[3].getGlobalBounds().top - 10,
                    text_vector[3].getGlobalBounds().width + 30, text_vector[3].getGlobalBounds().height + 20));
    }

    if (!text_vector[4].getString().isEmpty()) {
        // прямоугольник, содерж ответ D
        intrect_vector.push_back(sf::IntRect(text_vector[4].getGlobalBounds().left - 15, text_vector[4].getGlobalBounds().top - 10,
                    text_vector[4].getGlobalBounds().width + 30, text_vector[4].getGlobalBounds().height + 20));
    }
}


void update_wrapper(std::vector <sf::Text> &text_vector, std::vector <sf::ConvexShape> &wrapper_vector) {
    wrapper_vector.clear();
    float x, y;
    
    // рамка вокруг вопроса
    sf::ConvexShape text_wrapper;
    text_wrapper.setPointCount(6);
    
    y = text_vector[0].getGlobalBounds().top - 70;
    x = text_vector[0].getGlobalBounds().left - 30;
    text_wrapper.setPoint(0, sf::Vector2f(x, y));

    y = text_vector[0].getGlobalBounds().top - 3;
    x = text_vector[0].getGlobalBounds().left + text_vector[0].getGlobalBounds().width + 10;
    text_wrapper.setPoint(1, sf::Vector2f(x, y));

    y = text_vector[0].getGlobalBounds().top + text_vector[0].getGlobalBounds().height - 10;
    x = text_vector[0].getGlobalBounds().left + text_vector[0].getGlobalBounds().width + 30;
    text_wrapper.setPoint(2, sf::Vector2f(x, y));

    y = text_vector[0].getGlobalBounds().top + text_vector[0].getGlobalBounds().height + 15 ;
    x = text_vector[0].getGlobalBounds().left + text_vector[0].getGlobalBounds().width + 80;
    text_wrapper.setPoint(3, sf::Vector2f(x, y));

    y = text_vector[0].getGlobalBounds().top + text_vector[0].getGlobalBounds().height + 10 ;
    x = text_vector[0].getGlobalBounds().left + text_vector[0].getGlobalBounds().width + 40;
    text_wrapper.setPoint(4, sf::Vector2f(x, y));

    y = text_vector[0].getGlobalBounds().top + text_vector[0].getGlobalBounds().height + 50;
    x = text_vector[0].getGlobalBounds().left - 5;
    text_wrapper.setPoint(5, sf::Vector2f(x, y));

    text_wrapper.setOutlineColor(sf::Color::Black);
    text_wrapper.setOutlineThickness(1);

    text_wrapper.setFillColor(sf::Color(221, 193, 199));
    wrapper_vector.push_back(text_wrapper);  // закинул в вектор

    // рамки вокруг ответов
    for (size_t i = 1; i < text_vector.size(); i++) {
        if (text_vector[i].getString().isEmpty()) {
            continue;
        }

        sf::ConvexShape text_wrapper;
        text_wrapper.setPointCount(6);

        y = text_vector[i].getGlobalBounds().top - 10;
        x = text_vector[i].getGlobalBounds().left - 15;
        text_wrapper.setPoint(0, sf::Vector2f(x, y));

        y = text_vector[i].getGlobalBounds().top - 10;
        x = text_vector[i].getGlobalBounds().left + text_vector[i].getGlobalBounds().width + 15;
        text_wrapper.setPoint(1, sf::Vector2f(x, y));

        y = text_vector[i].getGlobalBounds().top + text_vector[i].getGlobalBounds().height / 2.0;
        x = text_vector[i].getGlobalBounds().left + text_vector[i].getGlobalBounds().width + 40;
        text_wrapper.setPoint(2, sf::Vector2f(x, y));

        y = text_vector[i].getGlobalBounds().top + text_vector[i].getGlobalBounds().height + 10;
        x = text_vector[i].getGlobalBounds().left + text_vector[i].getGlobalBounds().width + 15;
        text_wrapper.setPoint(3, sf::Vector2f(x, y));

        y = text_vector[i].getGlobalBounds().top + text_vector[i].getGlobalBounds().height + 10;
        x = text_vector[i].getGlobalBounds().left - 15;
        text_wrapper.setPoint(4, sf::Vector2f(x, y));

        y = text_vector[i].getGlobalBounds().top + text_vector[i].getGlobalBounds().height / 2.0;
        x = text_vector[i].getGlobalBounds().left - 40;
        text_wrapper.setPoint(5, sf::Vector2f(x, y));

        text_wrapper.setOutlineColor(sf::Color::Black);
        text_wrapper.setOutlineThickness(1);

        wrapper_vector.push_back(text_wrapper);
    }
}

void set_response_on_answer(std::vector <sf::Text> &text_vector, bool answer, bool end) {
    for (auto& text : text_vector) {
        text.setString(L"");
    }

    if (answer) {
        if (!end) {
            text_vector[0].setString(L"Молодец,\n        верно!!");   
        } else {
            text_vector[0].setString(L"УУУУХ, \nвсе угадал");
        }
    } else {
        if (!end) {
            text_vector[0].setString(L"Неееет,\n       неправильно!!");
        } else {
            text_vector[0].setString(L"Не угадал,\n но вопросы закончились");       
        }
    }
}
