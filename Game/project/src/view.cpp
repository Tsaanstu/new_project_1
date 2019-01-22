#include "view.hpp"

void getplayercoordinateforview(sf::View *view, double x, double y, int xraz, int yraz) {
	double tempX, tempY;
	if ((x > xraz / 2) && (x < (SIZE_LAB * BLOCK_WIDTH - xraz / 2))) {
		tempX = x;
	} else if (x >= (SIZE_LAB * BLOCK_WIDTH - xraz / 2)) {
		tempX = SIZE_LAB * BLOCK_WIDTH - xraz / 2;
	} else {
		tempX = xraz / 2;
	}

	if ((y > yraz / 2) && (y < (SIZE_LAB * BLOCK_HEIGHT - yraz / 2))) {
		tempY = y;
	} else if (y >= (SIZE_LAB * BLOCK_HEIGHT - yraz / 2)) {
		tempY = SIZE_LAB * BLOCK_HEIGHT - yraz / 2;
	} else {
		tempY = yraz / 2;
	}
	view->setCenter(tempX, tempY);
}

void viewmap(sf::View *view, double time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view->move(0.1 * time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view->move(0, 0.1 * time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view->move(-0.1 * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view->move(0, -0.1 * time);
	}

}

void changeview(sf::View *view) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		view->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
