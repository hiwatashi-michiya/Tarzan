#pragma once

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
	Floor(float x, float y, float length, float height, int type, float imgLength, float imgHeight,
		float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

private:

	//�����蔻��
	void Collision(int scrollX);

	//���W
	float x;
	float y;

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

};



