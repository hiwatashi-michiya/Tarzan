#include "Floor.h"
#include "Player.h"
#include <Novice.h>
#include "Vec2.h"

Floor::Floor()
{
}

Floor::Floor(float posX, float posY, float length, float height,int type, float imgLength, float imgHeight,
	float scrW, float scrH, int textureHandle, Player& pPlayer)
	: posX(posX), posY(posY), length(length), height(height), type(type), imgLength(imgLength), imgHeight(imgHeight),
	scrW(scrW), scrH(scrH), textureHandle(textureHandle), pPlayer(&pPlayer)
{
}

void Floor::Update(Vec2 scroll) {

	//描画タイマー
	drawTime += 1;

	if (drawTime == 60) {
		drawTime = 0;
	}

	if (type == NORMAL) {

		if (drawTime % 10 == 0) {
			scrX += 64;
		}

	}

	if (type == CEILING) {

		if (drawTime % 10 == 0) {
			scrX += 64;
		}

	}

	if (type == PLAYERACCEL) {

		if (drawTime % 5 == 0) {
			scrX += 64;
		}

	}

	if (type == PLAYERDECEL) {

		if (drawTime % 15 == 0) {
			scrX += 64;
		}

	}

	if (scrX > 192) {
		scrX = 0;
	}

	//当たり判定
	Collision(scroll);

}

void Floor::Draw(Vec2 scroll) {

	Novice::DrawQuad(posX - scroll.x, posY - scroll.y, posX + imgLength - scroll.x, posY - scroll.y,
		posX - scroll.x, posY + imgHeight - scroll.y, posX + imgLength - scroll.x, posY + imgHeight - scroll.y,
		scrX, 0, scrW, scrH, textureHandle, 0xFFFFFFFF);

}

void Floor::Collision(Vec2 scroll) {

	//上判定
	if ((pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y) >= posY - scroll.y &&
		pPlayer->Player::getPosY() - pPlayer->Player::getRadius() - scroll.y <= posY + height - scroll.y &&
		pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scroll.x > posX - scroll.x &&
		pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scroll.x < posX + length - scroll.x &&
		pPlayer->Player::getSpeedY() >= 0 && type != CEILING) {

		pPlayer->Player::RecoveryTarzanGage();
		pPlayer->Player::setSpeedY();
		pPlayer->Player::setIsGround();
		pPlayer->Player::setPosY(posY);
		pPlayer->Player::setLength();
		pPlayer->Player::setIsGrip();
		pPlayer->Player::setUnJump();

		if (type == PLAYERACCEL) {

			pPlayer->Player::accelX();

		}
		else if (type == PLAYERDECEL) {

			pPlayer->Player::decelX();

		}
		else {

		}

	}

	//下判定
	if ((pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y) >= posY - scroll.y &&
		pPlayer->Player::getPosY() - pPlayer->Player::getRadius() - scroll.y <= posY + height - scroll.y &&
		pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scroll.x > posX - scroll.x &&
		pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scroll.x < posX + length - scroll.x &&
		pPlayer->Player::getSpeedY() < 0) {

		if (type == CEILING) {

			pPlayer->Player::setSpeedY();
			pPlayer->Player::setUnderPosY(posY + height);

			if (pPlayer->Player::getIsGrip() == true) {
				pPlayer->Player::setIsGrip();
				pPlayer->Player::setGripGage();
				pPlayer->Player::setLength();
				pPlayer->Player::setUnGrip();
			}

		}

	}

}