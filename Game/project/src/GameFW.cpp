//
// Created by faceless on 19.04.18.
//

#include "GameFW.hpp"
#include "definitions.hpp"

namespace FlappyWitch {
Game::Game (sf::RenderWindow *new_window_pointer)  : _is_game_lost(false),
                                                     _is_game_won(false),
                                                     passed_tree_counter(0) {
    _window_pointer = new_window_pointer;

    _music.openFromFile("sounds/bg.wav");

    _swing_buf.loadFromFile("sounds/swing.wav");
    _swing = sf::Sound(_swing_buf);

    _passed_buf.loadFromFile("sounds/passed.wav");
    _passed = sf::Sound(_passed_buf);

    _is_game_finished = false;

    _frame_time  = sf::seconds(FRAME_DURATION);
    _horizontal_speed = HORIZONTAL_SPEED;
    _space_between_trees = SPACE_BETWEEN_TREES;

    for(int i = 0; i < TREES_AMOUNT; i++){
        _trees[i].Movement((400.f + i * _space_between_trees) * -1);
        _trees[i].GenerateNewPos(200 * i);
    }
}

void Game::Run(int &health, int &score) {
    _music.setLoop(true);
    _music.play();
    sf::Clock clock;
    sf::Time elapsed_time_since_update = sf::Time::Zero;
    while (!_is_game_finished) {
        sf::Time elapsed_time = clock.restart();
        elapsed_time_since_update += elapsed_time;
        if (elapsed_time_since_update > _frame_time) {
            elapsed_time_since_update -= _frame_time;
            HandleEvents();
            Update(_frame_time, score);
            Render();
        }
    }

    score += passed_tree_counter;
    if (_is_game_lost) {
        health -= HP_IF_LOSE;
    }
}

void Game::Run(int &health, int &score, int trees_amount_to_win) {
    _music.setLoop(true);
    _music.play();
    sf::Clock clock;
    sf::Time elapsed_time_since_update = sf::Time::Zero;
    while (!_is_game_finished) {
        sf::Time elapsed_time = clock.restart();
        elapsed_time_since_update += elapsed_time;
        if (elapsed_time_since_update > _frame_time) {
            elapsed_time_since_update -= _frame_time;
            HandleEvents();
            Update(_frame_time, score, trees_amount_to_win);
            Render();
        }
    }

    score += passed_tree_counter;
    if (_is_game_lost) {
        health -= HP_IF_LOSE;
    }
}

void Game::HandleEvents() {
    sf::Event event{};
    while ((*_window_pointer).pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            (*_window_pointer).close();
            _is_game_finished = true;
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Space:
		            _witch.Fly();
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::Update(sf::Time dt, int& score) {
    _floor.Movement(_horizontal_speed * dt.asSeconds());

    for (int i = 0; i < TREES_AMOUNT; i++) {
        if (Collision(_witch, _floor, _trees)) {
            _is_game_lost = true;
            _is_game_finished = true;
            return;
        }

        _trees[i].Movement(_horizontal_speed * dt.asSeconds());

        if (_trees[i].IsPassed()) {
            passed_tree_counter++;
            _passed.play();
            _trees[i].SetNewPos(LastTreePos() + _space_between_trees);
            _trees[i].GenerateNewPos(i * rand());
        }
    }
    _witch.Update(dt);
}

void Game::Update(sf::Time dt, int& score, int trees_amount_to_win) {
    if (passed_tree_counter == trees_amount_to_win) {
        _is_game_won = true;
        _is_game_finished = true;
        return;
    }

    _floor.Movement(_horizontal_speed * dt.asSeconds());

    for (int i = 0; i < TREES_AMOUNT; i++) {
        if (Collision(_witch, _floor, _trees)) {
            _is_game_lost = true;
            _is_game_finished = true;
            return;
        }

        _trees[i].Movement(_horizontal_speed * dt.asSeconds());

        if (_trees[i].IsPassed()) {
            passed_tree_counter++;
            _passed.play();
            _trees[i].SetNewPos(LastTreePos() + _space_between_trees);
            _trees[i].GenerateNewPos(i * rand());
        }
    }
    _witch.Update(dt);
}

void Game::Render() {
    _background_texture.loadFromFile("images/bg1.png");
    sf::Sprite _background_sprite(_background_texture);
    _background_sprite.scale(1.7f, 1.7f);

    sf::Font font;
    font.loadFromFile("fonts/ocr_onectt.ttf");

    if (!_is_game_finished) {
        (* _window_pointer).draw(_background_sprite);
        for (int i = 0; i < TREES_AMOUNT; i++) {
            (*_window_pointer).draw(_trees[i].getSpriteByNum(0));
            (*_window_pointer).draw(_trees[i].getSpriteByNum(1));
        }

        sf::Text your_score;
        your_score.setFont(font);
        your_score.setColor(sf::Color::White);
        your_score.setString("Your score: ");
        your_score.setCharacterSize(20);
        your_score.setPosition(10, 10);
        (*_window_pointer).draw(your_score);

        sf::Text text_game_score;
        text_game_score.setFont(font);
        text_game_score.setColor(sf::Color::White);
        text_game_score.setString(std::to_string(passed_tree_counter));
        text_game_score.setCharacterSize(20);
        text_game_score.setPosition(160, 10);
        (*_window_pointer).draw(text_game_score);

        (*_window_pointer).draw(_floor.Sprite());
        (*_window_pointer).draw(_witch.CurrentFrame());
        (*_window_pointer).display();
    } else {
        sf::Clock render_clock;
	(* _window_pointer).draw(_background_sprite);

        sf::Text text_your_score;
        text_your_score.setFont(font);
        text_your_score.setString("Your score: ");
        text_your_score.setCharacterSize(50);
        text_your_score.setPosition(200, 400);

        sf::Text text_score;
        text_score.setFont(font);
        text_score.setString(std::to_string(passed_tree_counter));
        text_score.setCharacterSize(50);
        text_score.setPosition(650, 400);

        if (_is_game_won) {
            text_if_win.setFont(font);
            text_if_win.setString("Great, you won! \\(^_^)/");
            text_if_win.setColor(sf::Color::White);
            text_if_win.setCharacterSize(50);
            text_if_win.setPosition(200, 300);
            (*_window_pointer).draw(text_if_win);
            (*_window_pointer).draw(text_your_score);
            (*_window_pointer).draw(text_score);
            (*_window_pointer).display();
        }

        if (_is_game_lost) {
            text_if_loose.setFont(font);
            text_if_loose.setString("Sorry, you lose (T_T)");
            text_if_loose.setColor(sf::Color::White);
            text_if_loose.setCharacterSize(50);
            text_if_loose.setPosition(200, 300);
            (*_window_pointer).draw(text_if_loose);
            (*_window_pointer).display();
            (*_window_pointer).draw(text_if_loose);
            (*_window_pointer).draw(text_your_score);
            (*_window_pointer).draw(text_score);
            (*_window_pointer).display();
        }

        while (render_time.asSeconds() < 2) {
            render_time = render_clock.getElapsedTime();
            }
        }
    }

float Game::LastTreePos() {
    float last_tree_pos = 0.f;
    for(int i = 0; i < TREES_AMOUNT; i++){
        if(_trees[i].GetPosX() > last_tree_pos)
            last_tree_pos = _trees[i].GetPosX();
    }
    return last_tree_pos;
}

bool Game::Collision(Witch witch, Floor floor, std::array<Tree, TREES_AMOUNT> trees) {
    float width = (witch.CurrentFrame().getGlobalBounds().width) / 2;
    float height = (witch.CurrentFrame().getGlobalBounds().height) / 2;
    sf::FloatRect rect(witch.CurrentFrame().getPosition().x - 20, witch.CurrentFrame().getPosition().y - 50, width, height);
    if (rect.intersects(floor.Sprite().getGlobalBounds())) {
	return true;
    } else {
        for (auto &tree : trees) {
            if ((rect.intersects(tree.getSpriteByNum(0).getGlobalBounds())) ||
                (rect.intersects(tree.getSpriteByNum(1).getGlobalBounds()))) {
		return true;
            }
        }
    }
    return false;
}
}

