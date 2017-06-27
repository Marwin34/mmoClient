#include "actor.h"

Actor::Actor(){
	id = 0;
	mapId = 0;
	x = 0;
	y = 0;
	sprite.setPosition(0, 0);
	dir = 4;
	lastDir = dir;
	frameH = 0;
	frameW = 0;
	autoAttackCd = 0;
	jPressed = false;
	image.loadFromFile("./img/player.png");
	texture.loadFromImage(image);
	sprite.setTextureRect(sf::IntRect(0, 0, image.getSize().x / 4, image.getSize().y / 4));
	sprite.setOrigin((float)0, (float)(image.getSize().y / 4 - 32));

	autoAttack.init(1, x, y);
}

Actor::~Actor(){


}

void Actor::init(){

}

void Actor::update(){

	if (autoAttackCd){
		autoAttackCd++;
		if (autoAttackCd > 10) autoAttackCd = 0;
	}

	if (lastDir == dir){
		frameH++;
	}
	if (dir == 4 || frameH >= 16) frameH = 0;

	if (dir == 0) frameW = 3;
	if (dir == 1) frameW = 2;
	if (dir == 2) frameW = 0;
	if (dir == 3) frameW = 1;

	autoAttack.update(x, y, frameW);

	if (jPressed) {
		autoAttackCd = 1;
		autoAttack.start();
		frameH = 12;
	}
	
	sprite.setTextureRect(sf::IntRect(frameH / 4 * image.getSize().x / 4, frameW * image.getSize().y / 4, image.getSize().x / 4, image.getSize().y / 4));
	lastDir = dir;
}

void Actor::control(){
	jPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !autoAttackCd) jPressed = true;
}


void Actor::captureData(Actor &data){
	id = data.id;
	x = data.x;
	y = data.y;
	dir = data.dir;
	mapId = data.mapId;
}

void Actor::draw(sf::RenderWindow *win){
	sprite.setPosition(x, y);
	sprite.setTexture(texture);
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
	return packet >> actor.id >> actor.x >> actor.y >> actor.dir >> actor.mapId;
}