#pragma once
#include "Vec2.h"

const int FLOOR_NUMBER = 50;

class Player;

enum FLOORTYPE {
	NORMAL,
	PLAYERACCEL,
	PLAYERDECEL,
	CEILING
};

class Floor
{
public:
	Floor();
	Floor(float posX, float posY, float length, float height, int type, float imgLength, float imgHeight,
		float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(Vec2 scroll);

	void Draw(Vec2 scroll);

private:

	//�����蔻��
	void Collision(Vec2 scroll);

	//���W
	float posX;
	float posY;

	//���蒷��
	float length;

	//���荂��
	float height;

	int type;

	//�摜����
	float imgLength;

	//�摜����
	float imgHeight;

	//DrawQuad�p
	float scrW;
	float scrH;

	int textureHandle;

	//�v���C���[�̃|�C���^
	Player* pPlayer;

	//�`��͈͍��W�𓮂���
	int drawTime = 0;
	int scrX = 0;

};



