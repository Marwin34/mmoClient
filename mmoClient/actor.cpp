#include "actor.h"

ActorTCPdatas::ActorTCPdatas(){
	id = 0;
	x = 0;
	y = 0;
	dir = 4;
	sAttack = false;
}

ActorTCPdatas::~ActorTCPdatas(){

}

int ActorTCPdatas::getId(){
	return id;
}

sf::Packet& operator <<(sf::Packet& packet, const ActorTCPdatas& actor)
{
	return packet; // Empty.
}

sf::Packet& operator >>(sf::Packet& packet, ActorTCPdatas& actor)
{
	return packet >> actor.id >> actor.x >> actor.y >> actor.dir >> actor.sAttack;
}

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

	texture = &mainManager["test"];
	sprite.setTexture(*texture);
	textureSize = texture->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sprite.setOrigin((float)0, (float)(0));
	//prite.setScale(2,2);
}

Actor::~Actor(){

}

void Actor::init(int data){
	id = data;
}

void Actor::update(){
	autoAttack.update(x, y, frameW);

	if (attack) {
		attack = false;
		autoAttack.start();
	}

	if (lastDir == dir){
		frameH++;
	}
	if (dir == 4 || frameH >= 16) frameH = 0;

	if (!autoAttack.active()){
		if (dir == 0) frameW = 3;
		if (dir == 1) frameW = 2;
		if (dir == 2) frameW = 0;
		if (dir == 3) frameW = 1;
	}
	//std::cout << " update : " << attack << std::endl;
	lastDir = dir;
}

void Actor::captureData(ActorTCPdatas &data){
	id = data.id;
	x = data.x;
	y = data.y;
	dir = data.dir;
	if (data.sAttack) attack = data.sAttack;
}

void Actor::draw(sf::RenderWindow *win){
	sprite.setTextureRect(sf::IntRect(frameH / 4 * textureSize.x / 5, frameW * textureSize.y / 4, textureSize.x / 5, textureSize.y / 4));
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
