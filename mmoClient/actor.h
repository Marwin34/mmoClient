#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "anims.h"

class ActorTCPdatas{ // Its a class only for receiving datas from server.
public:
	float dstX, dstY; // Position on server side.
	int id;
	int dir; // Direction received from server, only for animation etc.
	int currHp;
	int maxHp;
	bool sAttack;

	ActorTCPdatas();
	~ActorTCPdatas();
	int getId();

	friend sf::Packet& operator >>(sf::Packet&, ActorTCPdatas&); // Receive operator.
};

class PlayerTCPdatas{ // Its a class only for receiving datas from server.
public:
	float x, y; // Position on server side.
	int dealedInput;
	int lastInputId;
	int dir; // Direction received from server, only for animation etc.
	int currHp;
	int maxHp;
	bool sAttack;

	PlayerTCPdatas();
	~PlayerTCPdatas();
	int getId();

	friend sf::Packet& operator >>(sf::Packet&, PlayerTCPdatas&); // Receive operator.
};

class Player :public PlayerTCPdatas{
	struct InputS{
		int index;
		int wsadIndex;
		int mouseIndex;
		float x, y;
	};

	float drawX, drawY;
	int id;
	int dir;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	int currHp;
	int maxHp;
	int inputIndex;
	bool attack;
	bool send;

	int wsadIndex;
	int mouseIndex;

	sf::Sprite sprite;
	sf::Sprite hpIndiactor;

	sf::Vector2u textureSize;

	std::vector<InputS> inputsHistory;

	Animation autoAttack;
public:

	Player();
	~Player();

	void init(int);
	void input();
	void captureData(PlayerTCPdatas&);
	void update();
	void draw(sf::RenderWindow*);
	void showStats();
	void sended();
	void loadGraphics();
	bool mustSend();

	friend sf::Packet& operator <<(sf::Packet&, const Player&); // Send operator.
};

class Other :public ActorTCPdatas {
	float x;
	float y;
	int lastCharId;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;

	sf::Sprite sprite;
	sf::Sprite hpIndiactor;

	sf::Vector2u textureSize;

	Animation autoAttack;

public:
	Other();
	~Other();
	void init(int);
	void update();
	void captureData(ActorTCPdatas&);
	void draw(sf::RenderWindow*);
	void showStats();
};

class Enemy :public ActorTCPdatas {
	float x, y;
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