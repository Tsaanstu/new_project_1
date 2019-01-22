#ifndef PROJECT_INCLUDE_VIEW_HPP_
#define PROJECT_INCLUDE_VIEW_HPP_

#include <SFML/Graphics.hpp>
#include "definitions.hpp"

void getplayercoordinateforview(sf::View *view, double x, double y, int xraz, int yraz);
void viewmap(sf::View *view, double time);
void changeview(sf::View *view);

#endif  //  PROJECT_INCLUDE_VIEW_HPP_
