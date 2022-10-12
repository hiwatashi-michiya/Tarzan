#pragma once
#include "Vec2.h"

// �d��
const float GRAVITY = 1.0f;
// �c�^��ł��o������
const int VINE_LENGTH = 250;
// �^�[�U���Q�[�W
const int TARZAN_GAGE = 300;

// �^�[�U���Q�[�W�ɑΉ������J���[�R�[�h
const float TARZAN_COLOR = 255 / (float)TARZAN_GAGE;

class Player
{
public:
	Player();
	Player(Vec2 position, Vec2 velocity, float radius, Vec2 center, int color, bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround);

	void Update(int* scrollX);

	void Draw(int scrollX);

	inline float getPosX() { return position.x; }

	inline float getSpeedX() { return velocity.x; }

	inline float getRadius() { return radius; }

private:

	void Move();

	void Collision(int* scrollX);

	//���W
	Vec2 position;

	//���x
	Vec2 velocity;

	//���a
	float radius;

	//���S���W
	Vec2 center;

	//�F
	int color;

	//����ł��邩�ǂ����̔���
	bool isGrip;

	// �^�[�U���Q�[�W
	int TarzanGage;

	// ���܂����t���[��
	int GripGage;

	//���܂�Ȃ��t���[��
	int unGrip;

	// �n�ʂɂ��邩
	bool isGround;

};

