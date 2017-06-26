#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Map{
	int width, height;
	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;
	std::vector<std::vector<float>> obstacles;
public:
	Map();
	~Map();
	void init(int); // Take id of the map and create it (using pattern).
	void draw(sf::RenderWindow*);
	bool loadFromFile(std::string);
	std::vector<std::vector<float>> getObstacles();
};