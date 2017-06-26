#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Actor{
	float x, y; // Position on server side.
	int id;
	int mapId; // Id of the map where actor is.
	int lastCharId;
	int dir;
	int sDir; // Direction received from server, only for animation etc.
	int lastDir;
	int frameW, frameH; // Vertical and horizontal frames indicators.
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Texture test;

	friend sf::Packet& operator <<(sf::Packet&, const Actor&); // Send operator.
	friend sf::Packet& operator >>(sf::Packet&, Actor&); // Receive operator.
public:
	Actor();
	~Actor();
	void init();
	void update();
	void control(std::vector<std::vector<float>>*);
	void captureData(Actor&);
	void draw(sf::RenderWindow*);
	void showStats();
	int getId();
};