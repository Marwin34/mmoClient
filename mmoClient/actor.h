#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class Actor{
	float x, y; // Position on server side.
	int id;
	int lastCharId;
	int dir; // Direction received from server, only for animation etc.
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool sAttack;
	bool attack;

	sf::Sprite sprite;

	sf::Vector2u textureSize;

	Animation autoAttack;

	friend sf::Packet& operator <<(sf::Packet&, const Actor&); // Send operator, not used right now.
	friend sf::Packet& operator >>(sf::Packet&, Actor&); // Receive operator.
public:
	Actor();
	~Actor();
	void init();
	void createTexture(AssetsManager&);
	void update();
	void captureData(Actor&);
	void draw(sf::RenderWindow*);
	void showStats();
	int getId();
};