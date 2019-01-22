//
// Created by faceless on 19.04.18.
//

#ifndef UNTITLED1_WITCH_H
#define UNTITLED1_WITCH_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "definitions.hpp"

namespace FlappyWitch {
class Witch {
public:
    Witch();
    ~Witch() = default;

    void Update(sf::Time dt);
    void Rotate();

    sf::Sprite CurrentFrame();

    void Fly();

private:
    sf::SoundBuffer _swing_buf;
    sf::Sound _swing;

    sf::Texture _witch_texture;
    sf::Sprite _witch_sprite;

    float _vertical_speed;

    float _flight_power;

    int _current_frame = 0;
    int _frame_amount = 5;

    sf::Time _frame_duration;
    sf::Time _dt_since_prev_frame;
};
}


#endif //UNTITLED1_WITCH_H

