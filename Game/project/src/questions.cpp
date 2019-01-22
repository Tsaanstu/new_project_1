#include "questions.hpp"

Question::Question(std::string file_name) {
    file_name = "questions/" + file_name;
    std::ifstream fout(file_name, std::ios::in);
    if (!fout) {
        std::cerr << "\033[0;31m" << std::strerror(errno) << "\033[0m" \
        << ", Path = " << file_name << std::endl;
        throw std::invalid_argument("Can't open file, look at previous str");
    }
    std::string utf8_tmp;
    std::basic_string<sf::Uint32> tmp;

    std::getline(fout, utf8_tmp);
    sf::Utf8::toUtf32(utf8_tmp.begin(), utf8_tmp.end(), std::back_inserter(tmp));    
    
    int j = 0;
    for (size_t i = 0; i < tmp.size(); i++) {  // разбиение строки на подстроки <= 30 симв. 
        j++;
        if (j == 29) {
            j = i;
            while (tmp[j] != ' ') {
                j--;
            }            
            tmp.insert(j , 1, '\n');
            j = 0;
        }
    }
    tmp.pop_back();
    question = tmp;

    tmp.clear();
    std::getline(fout, utf8_tmp);
    sf::Utf8::toUtf32(utf8_tmp.begin(), utf8_tmp.end(), std::back_inserter(tmp));
    tmp.pop_back();    
    answer_a = tmp;
   
    tmp.clear();
    std::getline(fout, utf8_tmp);
    sf::Utf8::toUtf32(utf8_tmp.begin(), utf8_tmp.end(), std::back_inserter(tmp));
    tmp.pop_back();
    answer_b = tmp;

    tmp.clear();
    std::getline(fout, utf8_tmp);
    sf::Utf8::toUtf32(utf8_tmp.begin(), utf8_tmp.end(), std::back_inserter(tmp));
    tmp.pop_back();
    answer_c = tmp;

    tmp.clear();
    std::getline(fout, utf8_tmp);
    sf::Utf8::toUtf32(utf8_tmp.begin(), utf8_tmp.end(), std::back_inserter(tmp));
    tmp.pop_back();
    answer_d = tmp;

    fout >> right_answer;
}
sf::String Question::get_question() {  // возвращает строку со \n по ширине окна
    return question;
}

sf::String Question::get_answer_a() {
    return answer_a;
}

sf::String Question::get_answer_b() {
    return answer_b;
}

sf::String Question::get_answer_c() {
    return answer_c;
}

sf::String Question::get_answer_d() {
    return answer_d;
}

int Question::get_right_anser() {
    return right_answer;
}