#include "Floor.h"
#include "Player.h"
#include <Novice.h>

Floor::Floor()
{
}

Floor::Floor(float x, float y, float length, float height,int type, float imgLength, float imgHeight,
	float scrW, float scrH, int textureHandle, Player& pPlayer)
	: x(x), y(y), length(length), height(height), type(type), imgLength(imgLength), imgHeight(imgHeight),
	scrW(scrW), scrH(scrH), textureHandle(textureHandle), pPlayer(&pPlayer)
{
}

void Floor::Update(int scrollX) {

	//“–‚½‚è”»’è
	Collision(scrollX);

}

void Floor::Draw(int scrollX) {

	Novice::DrawQuad(x - scrollX, y, x + imgLength - scrollX, y,
		x - scrollX, y + imgHeight, x + imgLength - scrollX, y + imgHeight,
		0, 0, scrW, scrH, textureHandle, 0xFFFFFFFF);

}

void Floor::Collision(int scrollX) {

	//ã”»’è
	if ((pPlayer->Player::getPosY() + pPlayer->Player::getRadius()) >= y &&
		pPlayer->Player::getPosY() - pPlayer->Player::getRadius() <= y + height &&
		pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scrollX > x - scrollX + 10 &&
		pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scrollX < x + length - scrollX - 10 &&
		pPlayer->Player::getSpeedY() >= 0 && type != CEILING) {

		pPlayer->Player::RecoveryTarzanGage();
		pPlayer->Player::setSpeedY();
		pPlayer->Player::setIsGround();
		pPlayer->Player::setPosY(y);
		pPlayer->Player::setLength();
		pPlayer->Player::setIsGrip();

		if (type == PLAYERACCEL) {

			pPlayer->Player::accelX();

		}
		else if (type == PLAYERDECEL) {

			pPlayer->Player::decelX();

		}
		else {

		}

	}

	//‰º”»’è
	if ((pPlayer->Player::getPosY() + pPlayer->Player::getRadius()) >= y &&
		pPlayer->Player::getPosY() - pPlayer->Player::getRadius() <= y + height &&
		pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scrollX > x - scrollX &&
		pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scrollX < x + length - scrollX &&
		pPlayer->Player::getSpeedY() < 0) {

		if (type == CEILING) {

			pPlayer->Player::resetTarzanGage();
			pPlayer->Player::setSpeedY();
			pPlayer->Player::setUnderPosY(y + height);

		}

	}

}