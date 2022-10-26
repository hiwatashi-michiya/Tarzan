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
	: position({ position.x,position.y }), width(width), height(height), hitSpeed(hitSpeed),
	isAlive(true), type(type), color(color), pPlayer(&pPlayer), textureHandle(textureHandle)
{
	NUM[0] = Novice::LoadTexture("./Resources/Images/UI/0_black.png");
	NUM[1] = Novice::LoadTexture("./Resources/Images/UI/1_black.png");
	NUM[2] = Novice::LoadTexture("./Resources/Images/UI/2_black.png");
	NUM[3] = Novice::LoadTexture("./Resources/Images/UI/3_black.png");
	NUM[4] = Novice::LoadTexture("./Resources/Images/UI/4_black.png");
	NUM[5] = Novice::LoadTexture("./Resources/Images/UI/5_black.png");
	NUM[6] = Novice::LoadTexture("./Resources/Images/UI/6_black.png");
	NUM[7] = Novice::LoadTexture("./Resources/Images/UI/7_black.png");
	NUM[8] = Novice::LoadTexture("./Resources/Images/UI/8_black.png");
	NUM[9] = Novice::LoadTexture("./Resources/Images/UI/9_black.png");
	breakSoundCheck = -1;
}

//-----------------------------------------

void Wall::Update(Vec2 scroll, int& sound) {

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

		drawHitSpeed = hitSpeed;

		color = 0xFFFFFFFF;

		if (pPlayer->getPosX() > position.x - width &&
			pPlayer->getPosX() < position.x + width * 2) {
			Collision(scroll, sound);
		}

	}

}

void Wall::Draw(Vec2 scroll) {

	if (isAlive == true && position.x - scroll.x < WINDOW_WIDTH && position.x > 0 - width) {

		Novice::DrawQuad(position.x - scroll.x, position.y - scroll.y, position.x + width - scroll.x, position.y - scroll.y,
			position.x - scroll.x, position.y + height - scroll.y, position.x + width - scroll.x, position.y + height - scroll.y,
			scrX, 0, 64, 64, textureHandle, color);

		if (type == BREAK) {

			for (int a = 0; a < 2; a++) {

				divideNumber = 1;

				for (int b = 0; b < 1; b++) {
					divideNumber *= 10;
				}

				for (int c = 0; c < a; c++) {
					divideNumber /= 10;
				}

				drawNumber = drawHitSpeed / divideNumber;

				for (int d = 0; d < 10; d++) {

					if (d == drawNumber) {
						Novice::DrawQuad(position.x + (width / 2) + 32 * a - 48 - scroll.x, position.y + height - 128 - scroll.y, position.x + (width / 2) + 32 * a + 16 - scroll.x, position.y + height - 128 - scroll.y,
							position.x + (width / 2) + 32 * a - 48 - scroll.x, position.y + height - 64 - scroll.y, position.x + (width / 2) + 32 * a + 16 - scroll.x, position.y + height - 64 - scroll.y,
							0, 0, 64, 64, NUM[d], 0xFFFFFFFF);
					}

				}

				drawHitSpeed = drawHitSpeed % divideNumber;

			}

		}

	}

}

//------------------------------------------

void Wall::Collision(Vec2 scroll, int& sound) {

	if ((pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scroll.x > position.x - scroll.x) &&
		(pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scroll.x < position.x + width - scroll.x) &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y >= position.y - scroll.y &&
		pPlayer->Player::getPosY() + pPlayer->Player::getRadius() - scroll.y <= position.y + height - scroll.y) {

		isHit = true;

		if (!Novice::IsPlayingAudio(breakSoundCheck) || breakSoundCheck == -1) {
			breakSoundCheck = Novice::PlayAudio(sound, 0, 0.1f);
		}


		if (((pPlayer->Player::getSpeedX()) >= hitSpeed || (pPlayer->Player::getReverseSpeedX()) >= hitSpeed) && type == BREAK) {
			isAlive = false;
		}
		else if (pPlayer->Player::getIsGround() == false) {
			pPlayer->Player::setSpeedX();

			if (pPlayer->Player::getIsGrip() == true) {
				pPlayer->Player::setIsGrip();
				pPlayer->Player::setGripGage();
				pPlayer->Player::setLength();
				pPlayer->Player::setUnGrip();
			}

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