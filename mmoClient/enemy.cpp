#include "enemy.h"

EnemyTCPdatas::EnemyTCPdatas(){
	id = 0;
	x = 0;
	y = 0;
	maxHp = 0;
	currHp = maxHp;
	sAttack = false;
}

EnemyTCPdatas::~EnemyTCPdatas(){

}

int EnemyTCPdatas::getId(){
	return id;
}

sf::Packet& operator >>(sf::Packet& packet, EnemyTCPdatas& enemy)
{
	return packet >> enemy.id >> enemy.x >> enemy.y >> enemy.sAttack >> enemy.currHp >> enemy.maxHp;
}

Enemy::Enemy(){
	id = 0;
	x = 0;
	y = 0;
	sprite.setPosition(0, 0);
	frameH = 0;
	frameW = 0;
	attack = false;
	autoAttack.init(1, x, y);

	sprite.setTexture(*mainManager["enemy"]);
	textureSize = mainManager["enemy"]->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 5, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));

	hpIndiactor.setTexture(*mainManager["hpIndicator"]);
}

Enemy::~Enemy(){

}

void Enemy::init(int data){
	id = data;
}

void Enemy::update(){
	hpIndiactor.setScale(float(maxHp) / float(currHp), 1);
}

void Enemy::captureData(EnemyTCPdatas &data){
	id = data.id;
	x = data.x;
	y = data.y;
	maxHp = data.maxHp;
	currHp = data.currHp;
	if (data.sAttack) attack = data.sAttack;
}

void Enemy::draw(sf::RenderWindow *win){
	sprite.setTextureRect(sf::IntRect(frameW / 4 * textureSize.x / 5, frameH * textureSize.y / 4, textureSize.x / 5, textureSize.y / 4));
	sprite.setPosition(x, y);	
	win->draw(sprite);
	hpIndiactor.setPosition(x - 4, y - 15);
	win->draw(hpIndiactor);
}

void Enemy::showStats(){
	std::cout << x << ", " << y << std::endl;
}
