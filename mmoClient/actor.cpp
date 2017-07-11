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

	texture = &mainManager["player"];
	sprite.setTexture(*texture);
	textureSize = texture->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 5, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));
}

Actor::~Actor(){

}

void Actor::init(int data){
	id = data;
}

void Actor::update(){
	autoAttack.update(x, y, frameH);

	if (attack) {
		attack = false;
		autoAttack.start();
	}

	if (lastDir == dir){
		frameW++;
	}
	if (dir == 4 || frameW >= 16) frameW = 0;

	if (!autoAttack.active()){
		if (dir == 0) frameH = 3;
		if (dir == 1) frameH = 2;
		if (dir == 2) frameH = 0;
		if (dir == 3) frameH = 1;
	}
	else frameW = 17; // It points on last frame of animation.
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
	sprite.setTextureRect(sf::IntRect(frameW / 4 * textureSize.x / 5, frameH * textureSize.y / 4, textureSize.x / 5, textureSize.y / 4));
	sprite.setPosition(x, y);
	if (frameH != 3) {
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
