#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class ActorTCPdatas{ // Its a class only for receiving datas from server.
public:
	float x, y; // Position on server side.
	int id;
	int dir; // Direction received from server, only for animation etc.
	int currHp;
	int maxHp;
	bool sAttack;

	ActorTCPdatas();
	~ActorTCPdatas();
	int getId();

	friend sf::Packet& operator <<(sf::Packet&, const ActorTCPdatas&); // Send operator, not used right now.
	friend sf::Packet& operator >>(sf::Packet&, ActorTCPdatas&); // Receive operator.
};

class Player :public ActorTCPdatas {
	std::vector <sf::Vector2f> pos;
	int lastCharId;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;

	sf::Sprite sprite;
	sf::Sprite hpIndiactor;

	sf::Vector2u textureSize;

	Animation autoAttack;

public:
	Player();
	~Player();
	void init(int);;
	void update();
	void captureData(ActorTCPdatas&);
	void draw(sf::RenderWindow*);
	void showStats();
};

class Enemy :public ActorTCPdatas {
	int lastCharId;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;

	sf::Sprite sprite;
	sf::Sprite hpIndiactor;

	sf::Vector2u textureSize;

	Animation autoAttack;

public:
	Enemy();
	~Enemy();
	void init(int);
	void update();
	void captureData(ActorTCPdatas&);
	void draw(sf::RenderWindow*);
	void showStats();
};