#include "anims.h"

Animation::Animation(){
	x = 0;
	y = 0;
	offsetX = 0;
	offsetY = 0;
	type = 0;
	id = 0;
	timer = 0;
	lenght = 1;
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
		lenght = 3; 

		topOffset.x = 22;
		topOffset.y = 0;
		rightOffset.x = 32;
		rightOffset.y = 22;
		downOffset.x = 10;
		downOffset.y = 32;
		leftOffset.x = 0;
		leftOffset.y = 22;

		topOrigin.x = 6;
		topOrigin.y = 12;

		rightOrigin.x = 0;
		rightOrigin.y = 6;

		bottomOrigin.x = 6;
		bottomOrigin.y = 0;

		leftOrigin.x = 12;
		leftOrigin.y = 6;

		texture = &mainManager["swordAttack"];
		sprite.setTexture(*texture);
	}
}

void Animation::start(){
	timer = 1;
}

void Animation::update(float xx, float yy, int actorFrameH){
	x = xx;
	y = yy;
	if (actorFrameH == 3 && !timer){
		frameH = 3;
		sprite.setOrigin(topOrigin.x, topOrigin.y);
		offsetX = topOffset.x;
		offsetY = topOffset.y;
	}
	if (actorFrameH == 2 && !timer){
		frameH = 2;
		sprite.setOrigin(rightOrigin.x, rightOrigin.y);
		offsetX = rightOffset.x;
		offsetY = rightOffset.y;
	}
	if (actorFrameH == 0 && !timer){
		frameH = 0;
		sprite.setOrigin(bottomOrigin.x, bottomOrigin.y);
		offsetX = downOffset.x;
		offsetY = downOffset.y;
	}
	if (actorFrameH == 1 && !timer){
		frameH = 1;
		sprite.setOrigin(leftOrigin.x, leftOrigin.y);
		offsetX = leftOffset.x;
		offsetY = leftOffset.y;
	}

	if (timer){
		timer++;
		if (timer >= lenght){
			timer = 0; // 5 == 5 * 20 milisecons == 100 miliseconds
		}
	}
	//std::cout << frameH << std::endl;
	sprite.setTextureRect(sf::IntRect(frameW * texture->getSize().x, frameH * texture->getSize().y / 4, texture->getSize().x, texture->getSize().y / 4)); // 4 - number of elements in collumn (animation file).
	sprite.setPosition(x + offsetX, y + offsetY);
}

void Animation::draw(sf::RenderWindow *win){
	
	if(timer) win->draw(sprite);
}

bool Animation::active(){
	if (timer > 0) return true;
	return false;
}