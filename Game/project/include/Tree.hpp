//
// Created by faceless on 20.04.18.
//

#ifndef UNTITLED1_tree_H
#define UNTITLED1_tree_H

#include <SFML/Graphics.hpp>
#include "definitions.hpp"

namespace FlappyWitch {
class Tree {
public:
    explicit Tree(float distance_by_x = 300.f, float start_pos_x = -200.f);
    ~Tree() = default;

    void Movement(float horizontal_movement = 0);

    sf::Sprite getSpriteByNum(int sprite_num);

    bool IsPassed();

    void GenerateNewPos(int mod = 0);

    void SetNewPos(float new_pos_x);
    float GetPosX();


private:
    sf::Texture _tree_texture_top;
    sf::Texture _tree_texture_bot;
    sf::Sprite _tree_sprite_top;
    sf::Sprite _tree_sprite_bot;

    float _max_distance;
    float _start_top_height = -400.f;
    float _start_bot_height = -200.f;
    float _distance_by_y = 400.f;
};
}

#endif //UNTITLED1_tree_H

