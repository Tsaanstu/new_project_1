//
// Created by faceless on 20.04.18.
//

#include "Floor.hpp"

namespace FlappyWitch {
    Floor::Floor(float window_width, float window_height) {
        window_width = WINDOW_WIDTH;
        window_height = WINDOW_HEIGHT;

        _floor_texture.loadFromFile("images/tree.png");
        _floor_texture.setRepeated(true);

        sf::IntRect floor_rect(0.0f, 0.0f, window_width + RECT_WIDTH, RECT_HEIGHT);

        _floor_sprite.setTexture(_floor_texture);
        _floor_sprite.setTextureRect(floor_rect);
        _floor_sprite.setPosition(0.f, window_height - RECT_HEIGHT);
    }

void Floor::Update() {
    if(_floor_sprite.getPosition().x <= -20.f) {
            _floor_sprite.move(20.f, 0.f);
    }
}

sf::Sprite Floor::Sprite() {
    return _floor_sprite;
}

void Floor::Movement(float horizontal_movement) {
    _floor_sprite.move( (-1) * horizontal_movement, 0.f);
    Update();
}
}
