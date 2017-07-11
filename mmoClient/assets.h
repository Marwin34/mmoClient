#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Network.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#pragma once

/*
	Class made in order to load assets from files.
	Include global container.
*/

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

extern AssetsManager mainManager; // Global container.
