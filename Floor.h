#pragma once

const int FLOOR_NUMBER = 10;

class Player;

//enum TYPE {
//	NORMAL,
//	PLAYERACCEL,
//	PLAYERDECEL
//};

class Floor
{
public:
	Floor();
	Floor(float x,float y,float length,float height,float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

private:

	//�����蔻��
	void Collision(int scrollX);

	//���W
	float x;
	float y;

	//����
	float length;

	//����(�摜�\���p)
	float height;

	//DrawQuad�p
	float scrW;
	float scrH;

	int textureHandle;

	//�v���C���[�̃|�C���^
	Player* pPlayer;

};



