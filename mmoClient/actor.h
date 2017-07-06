#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class ActorTCPData{
public:
	float x, y; // Position on server side.
	int id;
	bool sAttack;
	int dir; // Direction received from server, only for animation etc.

	friend sf::Packet& operator <<(sf::Packet&, const ActorTCPData&); // Send operator, not used right now.
	friend sf::Packet& operator >>(sf::Packet&, ActorTCPData&); // Receive operator.

	ActorTCPData();
	~ActorTCPData();
	int getId();
};

class Actor :public ActorTCPData{
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;

	sf::Texture *texture;
	sf::Sprite sprite;

	sf::Vector2u textureSize;

	Animation autoAttack;
public:
	Actor();
	~Actor();
	void init();
	void update();
	void captureData(ActorTCPData&);
	void draw(sf::RenderWindow*);
	void showStats();
};