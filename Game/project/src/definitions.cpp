#include "definitions.hpp"

sf::Font GET_FONT() {
	sf::Font font;
	if (!font.loadFromFile(FONT_URL)) {
		// cerr << ERR_OF_FONT; // TODO(gleensande): fix
	}
	return font;
}
