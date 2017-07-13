#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "assets.h"

#pragma once

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

	sf::Vector2f topOrigin; // Set the origin of sprite.
	sf::Vector2f rightOrigin;
	sf::Vector2f bottomOrigin;
	sf::Vector2f leftOrigin;

	sf::Vector2u textureSize;

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