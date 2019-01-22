//
// Created by faceless on 19.04.18.
//

#include "Witch.hpp"

#include <cmath>

namespace FlappyWitch {
Witch::Witch() {
    _swing_buf.loadFromFile("sounds/swing.wav");
    _swing.setBuffer(_swing_buf);

    _witch_texture.loadFromFile("images/flyingman.png");
    _witch_sprite.setTexture(_witch_texture);
    _witch_sprite.setTextureRect(sf::IntRect(RECT_LEFT, RECT_TOP, WITCH_RECT_WIDTH, WITCH_RECT_HEIGHT));
    _witch_sprite.scale(2.0f, 2.0f);

    _witch_sprite.setPosition(START_POS_X, START_POS_Y);
    _witch_sprite.setOrigin(RECT_LEFT, WITCH_RECT_WIDTH);

    _current_frame = 0;
    _vertical_speed = 0.0f;
    _flight_power = FLIGHT_POWER;
    _frame_duration = sf::seconds(FRAME_DURATION);
    _dt_since_prev_frame = sf::Time::Zero;
    }

    void Witch::Rotate() {
        static const float pi = 3.141592654f;
        static const float pi_to_deg = 180.f;

        _witch_sprite.setRotation(atan(_vertical_speed / (-HORIZONTAL_SPEED * FRAME_DURATION)) * (pi_to_deg / pi));
    }

    void Witch::Update(sf::Time dt) {
        if(_vertical_speed >= 0) {
            _dt_since_prev_frame += dt;
            if (_dt_since_prev_frame >= _frame_duration) {
                _current_frame++;
                _dt_since_prev_frame = sf::Time::Zero;
            }
            if (_current_frame >= _frame_amount) {
                _current_frame = 0;
            }
        }
        _witch_sprite.setTextureRect(sf::IntRect(_current_frame * WITCH_RECT_WIDTH, 0, WITCH_RECT_WIDTH, WITCH_RECT_HEIGHT));
        _witch_sprite.move(0, (-1) * _vertical_speed);
        if (_witch_sprite.getPosition().y < 0) {
            _witch_sprite.move(0, (-1) * _witch_sprite.getPosition().y);
        }
        _vertical_speed -= GRAVITY * dt.asSeconds();

        Rotate();
    }

    sf::Sprite Witch::CurrentFrame() {
        return _witch_sprite;
    }

    void Witch::Fly() {
        _vertical_speed = _flight_power;
        _swing.play();
    }
}
