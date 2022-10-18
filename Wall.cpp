#include "Wall.h"
#include "Player.h"
#include <Novice.h>
#include "Map.h"

Wall::Wall() : position({ 0.0f,0.0f }), width(0.0f), height(0.0f), hitSpeed(0.0f),
isAlive(true), type(BREAK), color(0xFFFFFFFF), pPlayer(pPlayer)
{
}

Wall::Wall(Vec2 position, float width, float height, float hitSpeed,
	bool isAlive, int type, int color, Player& pPlayer)
	: position({position.x,position.y}), width(width), height(height), hitSpeed(hitSpeed),
	isAlive(true), type(type), color(color), pPlayer(&pPlayer)
{

}

//-----------------------------------------

void Wall::Update(int scrollX) {

	if (isAlive == true) {

		color = 0xFFFFFFFF;

		if (pPlayer->getPosX() > position.x - width &&
			pPlayer->getPosX() < position.x + width * 2) {
			Collision(scrollX);
		}

	}

}

void Wall::Draw(int scrollX) {

	if (isAlive == true && position.x - scrollX < WINDOW_WIDTH && position.x > 0 - width) {

		Novice::DrawBox(position.x - scrollX, position.y, width, height, 0.0f, color, kFillModeSolid);

	}

}

//------------------------------------------

void Wall::Collision(int scrollX) {

	if ((pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scrollX > position.x - scrollX) &&
		(pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scrollX < position.x + width - scrollX) &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() >= position.y &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() <= position.y + height) {

		if ((pPlayer->Player::getSpeedX()) >= hitSpeed && type == BREAK) {
			isAlive = false;
		}
		else if (pPlayer->Player::getIsGround() == false) {
			pPlayer->Player::resetTarzanGage();
			pPlayer->Player::setSpeedX();
			color = 0xFF0000FF;
		}
		else {
			pPlayer->Player::setSpeedX();
			color = 0xFF0000FF;
		}

	}

}