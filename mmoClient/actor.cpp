#include "actor.h"

Actor::Actor(){
	id = 0;
	x = 0;
	y = 0;
	sprite.setPosition(0, 0);
	dir = 4;
	lastDir = dir;
	frameH = 0;
	frameW = 0;
	attack = false;
	autoAttack.init(1, x, y);
}

Actor::~Actor(){


}

void Actor::init(){

}

void Actor::createTexture(AssetsManager &container){
	sprite.setTexture(container["player"]);
	textureSize = container["player"].getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 4, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));
}

void Actor::update(){
	if (lastDir == dir){
		frameH++;
	}
	if (dir == 4 || frameH >= 16) frameH = 0;

	if (dir == 0) frameW = 3;
	if (dir == 1) frameW = 2;
	if (dir == 2) frameW = 0;
	if (dir == 3) frameW = 1;

	autoAttack.update(x, y, frameW);

	if (attack) {
		autoAttack.start();
		frameH = 12;
	}
	
	lastDir = dir;
}

void Actor::control(){
}


void Actor::captureData(Actor &data){
	id = data.id;
	x = data.x;
	y = data.y;
	dir = data.dir;
	attack = data.attack;
}

void Actor::draw(sf::RenderWindow *win){
	sprite.setTextureRect(sf::IntRect(frameH / 4 * textureSize.x / 4, frameW * textureSize.y / 4, textureSize.x / 4, textureSize.y / 4));
	sprite.setPosition(x, y);
	if (frameW != 3) {
		win->draw(sprite);
		autoAttack.draw(win);
	}
	else {
		autoAttack.draw(win);
		win->draw(sprite);
	}
}

void Actor::showStats(){
	std::cout << x << ", " << y << ", " << dir << std::endl;
}

int Actor::getId(){
	return id;
}

sf::Packet& operator <<(sf::Packet& packet, const Actor& actor)
{
	return packet; // Empty.
}

sf::Packet& operator >>(sf::Packet& packet, Actor& actor)
{
	return packet >> actor.id >> actor.x >> actor.y >> actor.dir >> actor.attack;
}