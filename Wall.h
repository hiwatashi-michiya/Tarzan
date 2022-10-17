#pragma once
#include "Vec2.h"

const int WALL_NUMBER = 1;

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
	/// <param name="radius">����</param>
	/// <param name="hitSpeed">�ǂ��܂ł̃X�s�[�h��ς����邩</param>
	/// <param name="isAlive">��ꂽ���ǂ���</param>
	/// <param name="color">�F</param>
	/// <param name="pPlayer">�󂯓n���|�C���^(Player�N���X����)</param>
	Wall(Vec2 position, float width, float height, float hitSpeed, bool isAlive, 
		int type, int color, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

	inline float getHitSpeedX() { return hitSpeed; }

private:

	void Collision(int scrollX);

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

};



