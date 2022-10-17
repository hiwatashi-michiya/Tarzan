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
	Player(Vec2 position, Vec2 velocity, float radius, Vec2 center, int color, 
		bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround);

	void Update(int* scrollX);

	void Draw(int scrollX);

	float KeepMaxSpeed(float maxSpeed);

	//---------------- x ------------------

	//X���W�̎擾
	inline float getPosX() { return position.x; }

	//X���x�̎擾
	inline float getSpeedX() { return velocity.x; }

	//X���x�𔽓]������
	inline float setSpeedX() { velocity.x *= -1; return velocity.x; }

	//X���x������������
	inline float accelX() { velocity.x *= 1.001f; return velocity.x; }

	//X���x������������
	inline float decelX() { velocity.x /= 1.005f;	return velocity.x; }

	//---------------- y ------------------

	//Y���W�̎擾
	inline float getPosY() { return position.y; }

	//Y���W���~�߂�
	inline float setPosY(float y) { position.y = y - radius; return position.y; }

	//Y���x�̎擾
	inline float getSpeedY() { return velocity.y; }

	//Y���x��0�ɂ���
	inline float setSpeedY() { velocity.y = 0; return velocity.y; }

	//------------ ���̑� -----------------

	//�傫���̎擾
	inline float getRadius() { return radius; }

	//�n�ʔ��肩�ǂ����̎擾
	inline bool getIsGround() { return isGround; }

	//�n�ʔ���ɂ���
	inline bool setIsGround() { isGround = true; return isGround; }

	//�^�[�U���Q�[�W�����Z�b�g������
	inline int resetTarzanGage() { TarzanGage = 0; return TarzanGage; }

	//�^�[�U���Q�[�W���񕜂���
	inline int RecoveryTarzanGage() { TarzanGage = TARZAN_GAGE; return TarzanGage; }

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

