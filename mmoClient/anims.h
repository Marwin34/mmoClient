#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "assets.h"

class Animation {
	int type;
	int id;
	int timer;
	int lenght; // How long aniamtion will appear.
	int frameW;
	int frameH;
	float x, y;
	float offsetX, offsetY;

	sf::Vector2f topOffset; // How much the sprite will be away from player origin.
	sf::Vector2f rightOffset;
	sf::Vector2f downOffset;
	sf::Vector2f leftOffset;

	sf::Vector2i topOrigin; // Set the origin of sprite.
	sf::Vector2i rightOrigin;
	sf::Vector2i bottomOrigin;
	sf::Vector2i leftOrigin;

	sf::Texture *texture;
	sf::Sprite sprite;
public:
	Animation();
	~Animation();
	void init(int, float, float);
	void start();
	void update(float, float, int);
	void draw(sf::RenderWindow*);
	bool active();
};