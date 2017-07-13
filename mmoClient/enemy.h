#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class EnemyTCPdatas{ // Its a class only for receiving datas from server.
public:
	float x, y; // Position on server side.
	int id;
	int currHp;
	int maxHp;
	bool sAttack;

	EnemyTCPdatas();
	~EnemyTCPdatas();
	int getId();

	friend sf::Packet& operator >>(sf::Packet&, EnemyTCPdatas&); // Receive operator.
};

class Enemy :public EnemyTCPdatas {
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
	void captureData(EnemyTCPdatas&);
	void draw(sf::RenderWindow*);
	void showStats();
};