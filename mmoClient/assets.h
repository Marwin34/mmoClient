#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Network.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#pragma once

class AssetsManager{
	std::map <std::string, sf::Texture> textures;
	sf::Font mainFont;
public:
	AssetsManager();
	~AssetsManager();
	void load();
	sf::Font* font();
	sf::Texture& operator[](std::string);
};