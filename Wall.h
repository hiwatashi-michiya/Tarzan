#pragma once
#include "Vec2.h"

class Player;

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
	Wall(Vec2 position, float radius, float hitSpeed, bool isAlive, int color, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

	inline float getHitSpeedX() { return hitSpeed; }

private:

	void Collision(int scrollX);

	//�ǂ̈ʒu
	Vec2 position;

	//�傫��
	float radius;

	//�ϋv��(�X�s�[�h���e��)
	float hitSpeed;

	//���Ă��邩�ǂ���
	bool isAlive;

	//�F
	int color;

	Player* pPlayer;

};



