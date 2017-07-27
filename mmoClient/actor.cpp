#include "actor.h"

ActorTCPdatas::ActorTCPdatas(){
	id = 0;
	dstX = 0;
	dstY = 0;
	dir = 4;
	maxHp = 0;
	currHp = maxHp;
	sAttack = false;
}

ActorTCPdatas::~ActorTCPdatas(){

}

int ActorTCPdatas::getId(){
	return id;
}

sf::Packet& operator >>(sf::Packet& packet, ActorTCPdatas& actor)
{
	return packet >> actor.id >> actor.dstX >> actor.dstY >> actor.dir >> actor.sAttack >> actor.currHp >> actor.maxHp;
}

PlayerTCPdatas::PlayerTCPdatas(){
	x = 0;
	y = 0;
	dir = 4;
	maxHp = 0;
	currHp = maxHp;
	sAttack = false;
	dealedInput = 0;
}

PlayerTCPdatas::~PlayerTCPdatas(){

}

int PlayerTCPdatas::getId(){
	return 0;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerTCPdatas& actor)
{
	return packet >> actor.dealedInput >> actor.x >> actor.y >> actor.sAttack >> actor.currHp >> actor.maxHp;
}

Player::Player(){
	id = 0;
	x = 0;
	y = 0;
	drawX = x;
	drawY = y;
	spdX = 0;
	spdY = 0;
	sprite.setPosition(0, 0);
	dir = 4;
	lastDir = dir;
	frameH = 0;
	frameW = 0;
	wsadIndex = 4;
	mouseIndex = 0;
	inputIndex = 0;
	lastInputId = 0;
	attack = false;
	send = false;
	autoAttack.init(1, x, y);
	inputsHistory.resize(0);
}

void Player::loadGraphics(){
	sprite.setTexture(*mainManager["player"]);
	textureSize = mainManager["player"]->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 5, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));

	hpIndiactor.setTexture(*mainManager["hpIndicator"]);
}

Player::~Player(){

}

void Player::init(int data){
	id = data;
}

void Player::input(){
	wsadIndex = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) wsadIndex = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) wsadIndex = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) wsadIndex = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) wsadIndex = 3;
	mouseIndex = 0;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))mouseIndex = 1;
}

void Player::update(std::vector<std::vector<float>> *obstacles){
	spdX = 0;
	spdY = 0;
	if (wsadIndex == 0){
		spdY = -2;
	}
	if (wsadIndex == 1){
		spdX = 2;
	}
	if (wsadIndex == 2){
		spdY = 2;
	}
	if (wsadIndex == 3){
		spdX = -2;
	}
	for (unsigned j = 0; j < obstacles->size(); j++){
		resetSpd(obstacles->at(j)[0] * 32, obstacles->at(j)[1] * 32, obstacles->at(j)[2] * 32, obstacles->at(j)[3] * 32, wsadIndex); // 32 = block size;
	}
	drawX += spdX;
	drawY += spdY;
	if (wsadIndex != 4 || mouseIndex != 0){
		send = true;
		inputIndex++;
		InputS tmp;
		tmp.index = inputIndex;
		tmp.wsadIndex = wsadIndex;
		tmp.mouseIndex = mouseIndex;
		tmp.x = drawX;
		tmp.y = drawY;
		inputsHistory.push_back(tmp);
	}
	dir = wsadIndex;
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
	lastDir = dir;
	hpIndiactor.setScale(float(maxHp) / float(currHp), 1);
}

void Player::resetSpd(float x2, float y2, float width2, float height2, int direcrtion){
	if (direcrtion == 0  // TOP
		&& drawX <= x2 + width2
		&& x2 <= drawX + 32
		&& drawY + spdY <= y2 + height2
		&& y2 <= drawY + spdY + 32){
		wsadIndex = 4;
		spdY = 0;
	}

	if (direcrtion == 1 // RIGHT
		&& drawX + spdX <= x2 + width2
		&& x2 <= drawX + spdX + 32
		&& drawY <= y2 + height2
		&& y2 <= drawY + 32) {
		wsadIndex = 4;
		spdX = 0;
	}

	if (direcrtion == 2 // DOWN
		&& drawX <= x2 + width2
		&& x2 <= drawX + 32
		&& drawY + spdY <= y2 + height2
		&& y2 <= drawY + spdY + 32){
		wsadIndex = 4;
		spdY = 0;
	}

	if (direcrtion == 3 // LEFT
		&& drawX + spdX <= x2 + width2
		&& x2 <= drawX +spdX + 32
		&& drawY <= y2 + height2
		&& y2 <= drawY + 32){
		wsadIndex = 4;
		spdX = 0;
	}
}

void Player::captureData(PlayerTCPdatas &data){
	dealedInput = data.dealedInput;
	x = data.x;
	y = data.y;
	dir = data.dir;
	maxHp = data.maxHp;
	currHp = data.currHp;
	if (data.sAttack) attack = data.sAttack;

	if (lastInputId != dealedInput){
		int cnt = 0;
		for (unsigned i = 0; i < inputsHistory.size(); i++){
			if (dealedInput == inputsHistory[i].index){
				//std::cout << x << " , " << y << " , " << inputsHistory[i].x << " , " << inputsHistory[i].y << std::endl;
				if (x == inputsHistory[i].x && y == inputsHistory[i].y){
					cnt++;
					inputsHistory.erase(inputsHistory.begin(), inputsHistory.begin() + i);
					break;
				}
				else {
					drawX = x;
					drawY = y;
					inputsHistory.erase(inputsHistory.begin(), inputsHistory.begin() + i);
				}
			}
		}
		if (!cnt) {
			drawX = x;
			drawY = y;
			std::cout << "tu" << std::endl;
		}
		lastInputId = dealedInput;
	}
}



void Player::draw(sf::RenderWindow *win){
	
	sprite.setPosition(drawX, drawY);
	hpIndiactor.setPosition(drawX - 4, drawY - 15);

	sprite.setTextureRect(sf::IntRect(frameW / 4 * textureSize.x / 5, frameH * textureSize.y / 4, textureSize.x / 5, textureSize.y / 4));
	if (frameH != 3) {
		win->draw(sprite);
		autoAttack.draw(win);
	}
	else {
		autoAttack.draw(win);
		win->draw(sprite);
	}
	win->draw(hpIndiactor);
}

void Player::sended(){
	send = false;
}

void Player::showStats(){
	std::cout << x << ", " << y << ", " << dir << std::endl;
}

bool Player::mustSend(){
	return send;
}

sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
	return packet << player.inputIndex << player.wsadIndex << player.mouseIndex;
}

//Other players

Other::Other(){
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

	sprite.setTexture(*mainManager["player"]);
	textureSize = mainManager["player"]->getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 5, textureSize.y / 4));
	sprite.setOrigin((float)0, (float)(textureSize.y / 4 - 32));

	hpIndiactor.setTexture(*mainManager["hpIndicator"]);
}

Other::~Other(){

}

void Other::init(int data){
	id = data;
}

void Other::update(){
	//std::cout << dir << std::endl;
	if (dstX > x) x += 2;
	if (dstX < x) x -= 2;
	if (dstY > y) y += 2;
	if (dstY < y) y -= 2;

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
	hpIndiactor.setScale(float(maxHp) / float(currHp), 1);
}

void Other::captureData(ActorTCPdatas &data){
	id = data.id;
	dstX = data.dstX;
	dstY = data.dstY;
	dir = data.dir;
	maxHp = data.maxHp;
	currHp = data.currHp;
	if (data.sAttack) attack = data.sAttack;
}

void Other::draw(sf::RenderWindow *win){
	sprite.setPosition(x, y);
	hpIndiactor.setPosition(x - 4, y - 15);

	sprite.setTextureRect(sf::IntRect(frameW / 4 * textureSize.x / 5, frameH * textureSize.y / 4, textureSize.x / 5, textureSize.y / 4));
	if (frameH != 3) {
		win->draw(sprite);
		autoAttack.draw(win);
	}
	else {
		autoAttack.draw(win);
		win->draw(sprite);
	}
	win->draw(hpIndiactor);
}

void Other::showStats(){
	std::cout << x << ", " << y << ", " << dir << std::endl;
}

//Enemy

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

void Enemy::captureData(ActorTCPdatas &data){
	id = data.id;
	dstX = data.dstX;
	dstY = data.dstY;
	x = dstX;
	y = dstY;
	dir = data.dir;
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