#pragma once
#include "Vec2.h"

const int WALL_NUMBER = 50;

class Player;

enum WALLTYPE {
	BREAK,
	UNBREAK
};

class Wall
{

public:

	Wall();
	/// <summary>
	/// �ǂ̃p�����[�^�[
	/// </summary>
	/// <param name="position">{X���W, Y���W}</param>
	/// <param name="width">����</param>
	/// /// <param name="height">�c��</param>
	/// <param name="hitSpeed">�ǂ��܂ł̃X�s�[�h��ς����邩</param>
	/// <param name="isAlive">��ꂽ���ǂ���</param>
	/// /// <param name="type">�ǂ̎��</param>
	/// <param name="color">�F</param>
	/// <param name="pPlayer">�󂯓n���|�C���^(Player�N���X����)</param>
	Wall(Vec2 position, float width, float height, float hitSpeed, bool isAlive, 
		int type, int color, Player& pPlayer, int textureHandle);

	void Update(Vec2 scroll);

	void Draw(Vec2 scroll);

	inline float getHitSpeedX() { return hitSpeed; }

	inline bool getIsHit() { return isHit; }

private:

	void Collision(Vec2 scroll);

	//�ǂ̈ʒu
	Vec2 position;

	//����
	float width;

	//�c��
	float height;

	//�ϋv��(�X�s�[�h���e��)
	float hitSpeed;

	//���Ă��邩�ǂ���
	bool isAlive;

	//�ǂ̎��
	int type;

	//�F
	int color;

	Player* pPlayer;

	//�摜
	int textureHandle;

	//�����������ǂ���
	bool isHit;

	//�`��͈͍��W�𓮂���
	int drawTime = 0;
	int scrX = 0;
	
	//�����̃��\�[�X
	int NUM[10];

	//�����\���̏����֐�
	int drawNumber;

	int divideNumber;

	int drawHitSpeed;

};



