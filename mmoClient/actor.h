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

//Class defineing player that is controlled by client.
class Player :public PlayerTCPdatas{
	struct InputS{
		int index;
		int wsadIndex;
		int mouseIndex;
		float x, y;
	};

	float drawX, drawY;
	float spdX, spdY;
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
	void resetSpd(float x2, float y2, float width2, float height2, int direcrtion);
	void update(std::vector<std::vector<float>> *);
	void draw(sf::RenderWindow*);
	void showStats();
	void sended();
	void loadGraphics();
	bool mustSend();

	friend sf::Packet& operator <<(sf::Packet&, const Player&); // Send operator.
};

//Class defineing other players.
class Other :public ActorTCPdatas {
	float x;
	float y;
	int lastCharId;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;
	bool firstTime; // Bool to set other players x,y after first start to avoid players moving from 0,0 to their position after initiation.

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

//Clas defineing enemies on the map.
class Enemy :public ActorTCPdatas {
	float x, y;
	int lastCharId;
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	bool attack;
	bool firstTime; // Bool to set other players x,y after first start to avoid players moving from 0,0 to their position after initiation.

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