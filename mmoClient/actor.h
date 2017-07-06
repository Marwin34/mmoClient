#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class ActorTCPdatas{ // Its a claa only for receiving datas from server.
public:
	float x, y; // Position on server side.
	int id;
	int dir; // Direction received from server, only for animation etc.
	bool sAttack;

	ActorTCPdatas();
	~ActorTCPdatas();
	int getId();

	friend sf::Packet& operator <<(sf::Packet&, const ActorTCPdatas&); // Send operator, not used right now.
	friend sf::Packet& operator >>(sf::Packet&, ActorTCPdatas&); // Receive operator.
};

class Actor :public ActorTCPdatas {
	int lastCharId;
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
	void init(int);
	void update();
	void captureData(ActorTCPdatas&);
	void draw(sf::RenderWindow*);
	void showStats();
};