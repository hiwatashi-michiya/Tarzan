#include "Wall.h"
#include "Player.h"
#include <Novice.h>
#include "Stage.h"

Wall::Wall() : position({ 0.0f,0.0f }), width(0.0f), height(0.0f), hitSpeed(0.0f),
isAlive(true), type(BREAK), color(0xFFFFFFFF), pPlayer(pPlayer)
{
}

Wall::Wall(Vec2 position, float width, float height, float hitSpeed,
	bool isAlive, int type, int color, Player& pPlayer, int textureHandle)
	: position({position.x,position.y}), width(width), height(height), hitSpeed(hitSpeed),
	isAlive(true), type(type), color(color), pPlayer(&pPlayer), textureHandle(textureHandle)
{

}

//-----------------------------------------

void Wall::Update(Vec2 scroll) {

	drawTime += 1;

	if (drawTime == 60) {
		drawTime = 0;
	}

	if (drawTime % 6 == 0) {
		scrX += 64;
	}

	if (scrX > 192) {
		scrX = 0;
	}

	if (isAlive == true) {

		color = 0xFFFFFFFF;

		if (pPlayer->getPosX() > position.x - width &&
			pPlayer->getPosX() < position.x + width * 2) {
			Collision(scroll);
		}

	}

}

void Wall::Draw(Vec2 scroll) {

	if (isAlive == true && position.x - scroll.x < WINDOW_WIDTH && position.x > 0 - width) {

		Novice::DrawQuad(position.x - scroll.x, position.y - scroll.y, position.x + width - scroll.x, position.y - scroll.y,
			position.x - scroll.x, position.y + height - scroll.y, position.x + width - scroll.x, position.y + height - scroll.y,
			scrX, 0, 64, 64, textureHandle, color);

	}

}

//------------------------------------------

void Wall::Collision(Vec2 scroll) {

	if ((pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scroll.x > position.x - scroll.x) &&
		(pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scroll.x < position.x + width - scroll.x) &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y >= position.y - scroll.y &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y <= position.y + height - scroll.y) {

		isHit = true;

		if (((pPlayer->Player::getSpeedX()) >= hitSpeed || (pPlayer->Player::getReverseSpeedX()) >= hitSpeed) && type == BREAK) {
			isAlive = false;
		}
		else if (pPlayer->Player::getIsGround() == false) {
			pPlayer->Player::resetTarzanGage();
			pPlayer->Player::setSpeedX();

			if (type == BREAK) {
				color = 0xFF0000FF;
			}
			else {
				color = 0x0000FFFF;
			}
			
		}
		else {
			pPlayer->Player::setSpeedX();
			if (type == BREAK) {
				color = 0xFF0000FF;
			}
			else {
				color = 0x0000FFFF;
			}
		}

	}
	else {
		isHit = false;
	}

}