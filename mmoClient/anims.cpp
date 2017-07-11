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
		image.loadFromFile("./img/sword_layer.png");
		texture.loadFromImage(image);
		sprite.setPosition(x, y);
	}
}

void Animation::start(){
	timer = 1;
}

void Animation::update(float xx, float yy, int actorFrameW){
	x = xx;
	y = yy;
	if (actorFrameW == 3 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
		frameW = 3;
		sprite.setOrigin(6, 12);
		offsetX = 22;
		offsetY = 0;
	}
	if (actorFrameW == 2 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 30, 30, 30));
		frameW = 2;
		sprite.setOrigin(0, 6);
		offsetX = 32;
		offsetY = 22;
	}
	if (actorFrameW == 0 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 60, 30, 30));
		frameW = 0;
		sprite.setOrigin(6, 0);
		offsetX = 10;
		offsetY = 32;
	}
	if (actorFrameW == 1 && !timer){
		//sprite.setTextureRect(sf::IntRect(0, 90, 30, 30));
		frameW = 1;
		sprite.setOrigin(12, 6);
		offsetX = 0;
		offsetY = 22;
	}

	if (timer){
		timer++;
		if (timer > 5){
			timer = 0; // 5 == 5 * 20 milisecons == 100 miliseconds
		}
	}
	//std::cout << frameH << std::endl;
	sprite.setTextureRect(sf::IntRect(0, frameW * image.getSize().y / 4, image.getSize().x, image.getSize().y / 4));
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