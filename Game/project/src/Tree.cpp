//
// Created by faceless on 20.04.18.
//

#include "Tree.hpp"
#include "GameFW.hpp"

namespace FlappyWitch {
    Tree::Tree(float distance_by_x, float start_pos_x) {
        _tree_texture_top.loadFromFile("images/tree.png");
        _tree_texture_bot.loadFromFile("images/tree.png");
 
        _tree_sprite_top.setTexture(_tree_texture_top);
        _tree_sprite_bot.setTexture(_tree_texture_bot);

        _tree_sprite_bot.move(0.f, _tree_texture_bot.getSize().y + _distance_by_y);

        _tree_sprite_top.move( (-1) * start_pos_x, distance_by_x - _tree_texture_top.getSize().y);
        _tree_sprite_bot.move( (-1) * start_pos_x, distance_by_x - _tree_texture_bot.getSize().y);

        _start_top_height = _tree_sprite_top.getPosition().y - distance_by_x;
        _start_bot_height = _tree_sprite_bot.getPosition().y - distance_by_x;

        _max_distance = 300.f;
    }

    void Tree::Movement(float horizontal_movement) {
        _tree_sprite_bot.move( (-1) * horizontal_movement, 0.f);
        _tree_sprite_top.move( (-1) * horizontal_movement, 0.f);
    }

    sf::Sprite Tree::getSpriteByNum(int sprite_num) {
        if (sprite_num == 0) {
            return _tree_sprite_top;
        } else {
            return _tree_sprite_bot;
        }
    }

    bool Tree::IsPassed() {
        if (_tree_sprite_bot.getPosition().x + _tree_texture_bot.getSize().x < 0) {
            // Game::AddScore();
            return true;
        }
        return false;
    }

    void Tree::GenerateNewPos(int mod) {
        int num = mod;
        float new_distance_by_x = num % int(_max_distance)+ 100.f;
        _tree_sprite_bot.setPosition(_tree_sprite_bot.getPosition().x, new_distance_by_x + _start_bot_height);
        _tree_sprite_top.setPosition(_tree_sprite_top.getPosition().x, new_distance_by_x + _start_top_height);
    }

    void Tree::SetNewPos(float new_pos_x) {
        _tree_sprite_bot.move(new_pos_x - _tree_sprite_bot.getPosition().x, 0.f);
        _tree_sprite_top.move(new_pos_x - _tree_sprite_top.getPosition().x, 0.f);
    }

    float Tree::GetPosX() {
        return _tree_sprite_bot.getPosition().x;
    }
}
