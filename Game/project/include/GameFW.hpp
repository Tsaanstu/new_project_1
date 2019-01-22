//
// Created by faceless on 19.04.18.
//

#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include "Witch.hpp"
#include "Floor.hpp"
#include "Tree.hpp"
#include "definitions.hpp"


namespace FlappyWitch {
class Game {
 public:
    Game() = delete;
    explicit Game(sf::RenderWindow *new_window_pointer);
    ~Game() = default;
    void Run(int &health, int &score);
    void Run(int &health, int &score, int trees_amount_to_win);
 private:
    sf::RenderWindow * _window_pointer;

    sf::Music _music;

    sf::SoundBuffer _swing_buf;
    sf::Sound _swing;

    sf::SoundBuffer _passed_buf;
    sf::Sound _passed;

    sf::Texture _background_texture;
    sf::Sprite _background_sprite;

    sf::Time render_time;

    sf::Text text_if_win;
    sf::Text text_if_loose;

    void HandleEvents();
    void Update(sf::Time dt, int& score);
    void Update(sf::Time dt, int& score, int trees_amount_to_win);
    void Render();

    bool Collision(Witch witch, Floor floor, std::array<Tree, TREES_AMOUNT> trees);

    float LastTreePos();

    sf::Time _frame_time;

    float _horizontal_speed;
    float _space_between_trees;

    Witch _witch;
    Floor _floor;
    std::array<Tree, TREES_AMOUNT> _trees;

    bool _is_game_finished;
    bool _is_game_lost ;
    bool _is_game_won ;

    int passed_tree_counter;
};
}


#endif //UNTITLED1_GAME_H

