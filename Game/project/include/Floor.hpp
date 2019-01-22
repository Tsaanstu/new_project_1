//
// Created by faceless on 20.04.18.
//

#ifndef UNTITLED1_FLOOR_H
#define UNTITLED1_FLOOR_H

#include <SFML/Graphics.hpp>

#include "definitions.hpp"

namespace FlappyWitch {
class Floor {
public:
    Floor(float window_width = WINDOW_WIDTH, float window_height = WINDOW_HEIGHT);
    ~Floor() = default;

    void Update();

    sf::Sprite Sprite();

    void Movement(float horizontal_movement = 0);

private:
    sf::Texture _floor_texture;
    sf::Sprite _floor_sprite;

};
}


#endif //UNTITLED1_FLOOR_H
