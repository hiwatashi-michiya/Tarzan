#include "Floor.h"
#include "Player.h"
#include <Novice.h>

Floor::Floor()
{
}

Floor::Floor(float x, float y, float length, float height, float scrW, float scrH, int textureHandle, Player& pPlayer)
	: x(x), y(y), length(length), height(height), scrW(scrW), scrH(scrH), textureHandle(textureHandle), pPlayer(&pPlayer)
{
}

void Floor::Update(int scrollX) {

	//�����蔻��
	Collision(scrollX);

}

void Floor::Draw(int scrollX) {

	Novice::DrawQuad(x - scrollX, y, x + length - scrollX, y,
		x - scrollX, y + height, x + length - scrollX, y + height,
		0, 0, scrW, scrH, textureHandle, 0xFFFFFFFF);

}

void Floor::Collision(int scrollX) {

	//�v���C���[���n�ʂ̉��ɓ��낤�Ƃ����ꍇ���x��0�ɂ���
	if ((pPlayer->Player::getPosY() + pPlayer->Player::getRadius()) >= y &&
		pPlayer->Player::getPosX() + pPlayer->Player::getRadius() - scrollX > x - scrollX &&
		pPlayer->Player::getPosX() - pPlayer->Player::getRadius() - scrollX < x + length - scrollX &&
		pPlayer->Player::getSpeedY() >= 0) {

		pPlayer->RecoveryTarzanGage();
		pPlayer->setSpeedY();
		pPlayer->setIsGround();
		pPlayer->setPosY(y);

	}

}