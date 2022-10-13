#include "Wall.h"
#include "Player.h"
#include <Novice.h>
#include "Map.h"

Wall::Wall() : position({0.0f,0.0f}), radius(0.0f),hitSpeed(0.0f),isAlive(true),color(0xFFFFFFFF), pPlayer(pPlayer)
{
}

Wall::Wall(Vec2 position, float radius, float hitSpeed, bool isAlive, int color,Player& pPlayer)
	: position({position.x,position.y}), radius(radius), hitSpeed(hitSpeed), isAlive(true), color(color), pPlayer(&pPlayer)
{

}

//-----------------------------------------

void Wall::Update(int scrollX) {

	if (pPlayer->getPosX() > position.x - radius &&
		pPlayer->getPosX() < position.x + radius * 2) {
		Collision(scrollX);
	}

}

void Wall::Draw(int scrollX) {

	if (isAlive == true && position.x < WINDOW_WIDTH && position.x > 0 - radius) {

		Novice::DrawBox(position.x - scrollX, position.y, radius / 2, radius, 0.0f, color, kFillModeSolid);

	}

}

//------------------------------------------

void Wall::Collision(int scrollX) {

	if (pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scrollX > position.x - scrollX) {

		if ((pPlayer->Player::getSpeedX()) >= hitSpeed) {
			isAlive = false;
		}
		else {
			pPlayer->Player::setSpeedX();
		}

	}

}