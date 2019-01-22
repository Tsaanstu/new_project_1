#ifndef PROJECT_INCLUDE_DEFINITIONS_HPP
#define PROJECT_INCLUDE_DEFINITIONS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

// errors
const int ERR_OF_FONT = -1;
const int GAME_WIN = 100;
const int PLAYER_DIED = 101;
const int GAME_STOP = 102;

// window
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const sf::Color WINDOW_COLOR = sf::Color::White;
const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(222, 236, 199);

const int BORDER_WIDTH = 42;
const double ANIM_SPEED = 0.1;

const std::string FRAME_LINK = "images/frame1.png";

const std::string BACKGROUND_LINK = "data/backgrounds/";
const std::string PICTURE_LINK = "data/images/";
const int PICTURE_MODULE_HEIGHT = 252;  //  720 * 7 / 20 = 252 ->  280 - 252 = 28
const int PICTURE_MODULE_WIDTH = 450;  //  1280 * 3 / 5
//  const int PICTURE_MODULE_INTERVAL = 32;

const int COMMAND_MODULE_HEIGHT = 216;  //  720 * 6 / 20
const int COMMAND_MODULE_WIDTH = 768;
const int COMMAND_MODULE_INTERVAL = 32;

const int TEXT_MODULE_HEIGHT = 252;  //  210
const int TEXT_MODULE_WIDTH = 1024;  //  1280 * 4 / 5
//  const int TEXT_MODULE_INTERVAL = 32;

// font
const int FONT_SIZE_MENU_TITLE = 60;
const int FONT_SIZE_MENU_BUTTON_sm = 32;
const int FONT_SIZE_MENU_BUTTON_bg = 36;

const int FONT_SIZE = 24;
const sf::Color FONT_COLOR = sf::Color::Black;
const sf::Color FONT_COLOR_1 = sf::Color::White;
const std::string FONT_URL = "fonts/COURIER.TTF";  // TODO(gleensande): rename to SRC

// button
const int BUTTON_OUTLINE_THICKNESS = 3;
const sf::Color BUTTON_BACKGROUND_COLOR = sf::Color::Green;
const sf::Color BUTTON_OUTLINE_COLOR = sf::Color::Black;
const int DISTANCE_BETWEEN_BUTTON = 80;
const int BUTTON_WIDTH = 120;
const int BUTTON_HEIGHT = 50;

// labirint
const int BLOCK_WIDTH = 90;
const int BLOCK_HEIGHT = 90;

const int HERO_WIDTH = 70;
const int HERO_HEIGHT = 85;

const int ENEMY_WIDTH = 70;
const int ENEMY_HEIGHT = 70;

const int SIZE_LAB = 29;
const size_t ENEMY_NUM = 5;

const std::string MAP_SRC = "images/map2.png";
const std::string HERO_SPRITE_SRC = "images/hero3.png";
const std::string ENEMY_SPRITE_SRC = "images/ghost2.png";

const std::string LABIRINT_SOUND_MOVE = "sounds/move.ogg";
const std::string LABIRINT_SOUND_GHOST = "sounds/laughter.ogg";
const std::string LABIRINT_MUSIC = "sounds/HM.ogg";

// To paradise
const int PLATFORM_WIDTH = 68;
const int PLATFORM_HEIGHT = 10;

const int ANGEL_WIDTH = 80;
const int ANGEL_HEIGHT = 80;

const int PLATFORM_NUM = 14;

const double PLAYER_A_X = 7;
const double STEP = 0.2;
const int H_JUMP = 400;

const std::string BACKGROUND_SPRITE_SRC = "images/background1.png";
const std::string ANGEL_SPRITE_SRC = "images/doudle_hero.png";
const std::string PLATFORM_SPRITE_SRC = "images/doudle_platform.png";

const std::string PARADISE_MUSIC = "sounds/KOHD.ogg";

// To hell
const double pi = 3.14159;
const double BALL_RADIUS = 10;

const double WIDTH_PLATFORM = 50;
const double HEIGHT_PLATFORM = 100;

const double PLATFORM_SPEED = 400;
const double BALL_SPEED = 600;

const std::string HELL_RIGHT_PLATFORM_SPRITE_SRC = "images/platform2.png";
const std::string HELL_LEFT_PLATFORM_SPRITE_SRC = "images/platform1.png";
const std::string BALL_SPRITE_SRC = "images/ball2.png";
const std::string HELL_BG_SRC = "images/bg_hell_1.png";

const std::string HELL_SOUND_BALL_POKE = "sounds/cry.ogg";
const std::string HELL_MUSIC = "sounds/HtH.ogg";

// Flappy witch

const float FRAME_DURATION = 1.f/60.f;

const float SPACE_BETWEEN_TREES = 400.f;

const float HORIZONTAL_SPEED = 300.f;
const float GRAVITY = 12.f;
const float FLIGHT_POWER = 5.f;

const int HP_IF_LOSE = 100;
const int TREES_AMOUNT = 5;
const int TREES_AMOUNT_TO_WIN = 10;
const double RECT_WIDTH = 40.0;
const double RECT_HEIGHT = 40.0;

const int RECT_LEFT = 10;
const int RECT_TOP = 10;
const int WITCH_RECT_WIDTH = 38;
const int WITCH_RECT_HEIGHT = 32;
const int START_POS_X = 38;
const int START_POS_Y = 320;


// player_moves
const std::string MOVES_FILE = "data/unions.txt";  // TODO(gleensande): rename to SRC

// finish
const std::string RECORDS_SRC = "data/records.txt"; 
const int RECORDS_NUM = 10;

// entry field
const int ENTRY_X = 300;
const int ENTRY_Y = 400;
const int ENTRY_MAX_SYMB = 20;
const int ENTRY_WIDTH = FONT_SIZE * ENTRY_MAX_SYMB + 10;
const int ENTRY_HEIGHT = FONT_SIZE + 10;
const int ENTRY_OUTLINE_THICKNESS = 3;
const sf::Color ENTRY_ENTER_FINISHED_COLOR = sf::Color(100, 100, 100, 100);
const sf::Color ENTRY_BACKGROUND_COLOR = sf::Color::White;
const sf::Color ENTRY_OUTLINE_INACTIVE_COLOR = sf::Color::Black;
const sf::Color ENTRY_OUTLINE_ACTIVE_COLOR = sf::Color::Yellow;
const sf::Color ENTRY_OUTLINE_ENTER_FINISHED_COLOR = sf::Color(100, 100, 100, 100);

// FUNCTIONS

// font
sf::Font GET_FONT();

#endif  // PROJECT_INCLUDE_DEFINITIONS_HPP
