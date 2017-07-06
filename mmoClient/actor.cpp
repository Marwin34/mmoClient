#include "actor.h"

ActorTCPData::ActorTCPData(){
	id = 0;
	x = 0;
	y = 0;
	dir = 4;
	sAttack = false;
}

ActorTCPData::~ActorTCPData(){

}

int ActorTCPData::getId(){
	return id;
}


sf::Packet& operator <<(sf::Packet& packet, const ActorTCPData& actor)
{
	return packet; // Empty.
}

sf::Packet& operator >>(sf::Packet& packet, ActorTCPData& actor)
{
	return packet >> actor.id >> actor.x >> actor.y >> actor.dir >> actor.sAttack;
}

Actor::Actor(){ 
	sprite.setPosition(0, 0);
	lastDir = 4;
	frameH = 0;
	frameW = 0;
	attack = false;
	autoAttack.init(1, x, y);

	std::cout << texture << std::endl;
	texture = &mainManager["player"];
	sprite.setTexture(*texture);
	textureSize = texture->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 4, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));
	//dddstd::cout << texture << std::endl;
}

Actor::~Actor(){

}

void Actor::init(){

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
	//std::cout << " update : " << attack << std::endl;
	if (attack) {
		attack = false;
		autoAttack.start();
		frameH = 12;
	}
	
	lastDir = dir;
}

void Actor::captureData(ActorTCPData &data){
	id = data.id;
	x = data.x;
	y = data.y;
	dir = data.dir;
	if (data.sAttack) attack = data.sAttack;
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

