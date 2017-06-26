#include "actor.h"

Actor::Actor(){
	id = 0;
	mapId = 0;
	x = 0;
	y = 0;
	sprite.setPosition(0, 0);
	dir = 4;
	sDir = 4;
	lastDir = sDir;
	frameH = 0;
	frameW = 0;
	image.loadFromFile("./img/player.png");
	texture.loadFromImage(image);
	sprite.setOrigin(0,image.getSize().y / 4 - 32);
}

Actor::~Actor(){


}

void Actor::init(){

}

void Actor::update(){
	if (lastDir == sDir){
		frameH++;
	}
	if (sDir == 4 || frameH >= 16) frameH = 0;
	if (sDir == 0) frameW = 3;
	if (sDir == 1) frameW = 2;
	if (sDir == 2) frameW = 0;
	if (sDir == 3) frameW = 1;
	
	sprite.setTextureRect(sf::IntRect(frameH / 4 * image.getSize().x / 4, frameW * image.getSize().y / 4, image.getSize().x / 4, image.getSize().y / 4));

	lastDir = sDir;
}

void Actor::control(std::vector<std::vector<float>> *obstacles){
	dir = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = 3;
}


void Actor::captureData(Actor &data){
	id = data.id;
	x = data.x;
	y = data.y;
	sDir = data.sDir;
	mapId = data.mapId;
}

void Actor::draw(sf::RenderWindow *win){
	sprite.setPosition(x, y);
	sprite.setTexture(texture);
	win->draw(sprite);
}

void Actor::showStats(){
	std::cout << x << ", " << y << ", " << dir << std::endl;
}

int Actor::getId(){
	return id;
}

sf::Packet& operator <<(sf::Packet& packet, const Actor& actor)
{
	return packet << actor.dir;
}

sf::Packet& operator >>(sf::Packet& packet, Actor& actor)
{
	return packet >> actor.id >> actor.x >> actor.y >> actor.sDir >> actor.mapId;
}