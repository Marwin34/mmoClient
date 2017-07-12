#include "assets.h"

AssetsManager::AssetsManager(){
	textures.clear();
}

AssetsManager::~AssetsManager(){

}

void AssetsManager::load(){
	textures["none"].loadFromFile("./img/none.png");;
	textures["player"].loadFromFile("./img/charset_template_combat2.png");
	textures["player"].setSmooth(true);
	textures["swordAttack"].loadFromFile("./img/sword_layer.png");
	textures["swordAttack"].setSmooth(true);
	textures["hpIndicator"].loadFromFile("./img/hp.png");
	textures["hpIndicator"].setSmooth(true);

	//CZIONKI
	mainFont.loadFromFile("font/Anonymous_Pro.ttf");
}

sf::Font* AssetsManager::font(){
	return &mainFont;
}

sf::Texture* AssetsManager::operator[](std::string data){
	if (textures.count(data) > 0){
		return &textures[data];
	}
	else return &textures["none"];
}

//GLOBAL MAANGER 
AssetsManager mainManager;