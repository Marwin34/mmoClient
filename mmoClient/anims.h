#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

class Animation {
	int type;
	int id;
	int timer;
	int frameW;
	int frameH;
	float x, y;
	float offsetX, offsetY;

	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Animation();
	~Animation();
	void init(int, float, float);
	void start();
	void update(float, float, int);
	void draw(sf::RenderWindow*);
};