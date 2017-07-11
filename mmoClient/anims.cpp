#include "anims.h"

Animation::Animation(){
	x = 0;
	y = 0;
	offsetX = 0;
	offsetY = 0;
	type = 0;
	id = 0;
	timer = 0;
	frameH = 2;
	frameW = 0;
}

Animation::~Animation(){

}

void Animation::init(int sId, float sx, float sy){
	switch (sId) {
	case 1: // Mele attack with sword.
		x = sx; 
		y = sy;
		type = 1; // Mele type.
		id = 1; // ID.
		image.loadFromFile("./img/attackAnims2.png");
		texture.loadFromImage(image);
		sprite.setPosition(x, y);
	}
}

void Animation::start(){
	timer = 1;
}

void Animation::update(float xx, float yy, int dir){
	x = xx;
	y = yy;
 
	if (dir == 3 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
		frameW = 0;
		sprite.setOrigin(14, 25);
		offsetX = 13;
		offsetY = 5;
	}
	if (dir == 2 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 30, 30, 30));
		frameW = 1;
		sprite.setOrigin(4, 16);
		offsetX = 20;
		offsetY = 13;
	}
	if (dir == 0 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 60, 30, 30));
		frameW = 2;
		sprite.setOrigin(18, 5);
		offsetX = 20;
		offsetY = 17;
	}
	if (dir == 1 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 90, 30, 30));
		frameW = 3;
		sprite.setOrigin(25, 14);
		offsetX = 8;
		offsetY = 11;
	}

	if (timer){
		frameH = 2 - timer;
		timer++;
		if (timer > 3){
			timer = 0; // 5 == 5 * 20 milisecons == 100 miliseconds
			frameH = 2;
		}
	}
	//std::cout << frameH << std::endl;
	sprite.setTextureRect(sf::IntRect(frameH * image.getSize().x / 3, frameW * image.getSize().y / 4, image.getSize().x / 3, image.getSize().y / 4));
	sprite.setTexture(texture);
	sprite.setPosition(x + offsetX, y + offsetY);
}

void Animation::draw(sf::RenderWindow *win){
	
	if(timer) win->draw(sprite);
}

bool Animation::active(){
	if (timer > 0) return true;
	return false;
}