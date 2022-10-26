#pragma once
#include "Vec2.h"


// �v���C���[�̏�Ԃ𕪂���
enum PLAYERSTATE {
	IDLE,
	RUN,
	TARZAN,
	JUMP,
	SKY,
	LANDING
};

// �v���C���[�̏��
const int PLAYER_STATE_NUM = 6;


// �d��
const float GRAVITY = 1.0f;
// �c�^��ł��o������
const int VINE_LENGTH = 250;
// �^�[�U���Q�[�W
const int TARZAN_GAGE = 300;

// �^�[�U���Q�[�W�ɑΉ������J���[�R�[�h
const float TARZAN_COLOR = 255 / (float)TARZAN_GAGE;

// ���a(�����蔻��͉~)
const int RADIUS = 16;

// �l���̓_
const Vec2 LEFTTOP = { -RADIUS,-RADIUS };
const Vec2 RIGHTTOP = { RADIUS - 1,-RADIUS };
const Vec2 LEFTBOTTOM = { -RADIUS,RADIUS - 1 };
const Vec2 RIGHTBOTTOM = { RADIUS - 1,RADIUS - 1 };

class Player
{
public:
	Player();
	Player(Vec2 position, Vec2 velocity, Vec2 center,
		bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround, float length, int textureHandle, int drawX);

	Player(Vec2 pos, int texturehandle[]);

	void Update(Vec2& scroll);

	void Draw(Vec2 scroll);

	float KeepMaxSpeed(float maxSpeed);

	//---------------- x ------------------

	//X���W�̎擾
	inline float getPosX() { return position.x; }

	//X���x�̎擾
	inline float getSpeedX() { return velocity.x; }

	//X���x�̎擾(���̒l)
	inline float getReverseSpeedX() { return -velocity.x; }

	//X���x�𔽓]������
	inline float setSpeedX() { velocity.x *= -1; return velocity.x; }

	//X���x��0�ɂ���
	inline float setSpeed0X() { velocity.x = 0; return velocity.x; }

	//X���x������������
	inline float accelX() {

		if (velocity.x > 0) {
			if (velocity.x < 50) {
				velocity.x *= 1.005f;
			}
		}
		else {
			if (velocity.x > -50) {
				velocity.x *= 1.005f;
			}
		}
		
		return velocity.x;
	}

	//X���x������������
	inline float decelX() { velocity.x /= 1.005f;	return velocity.x; }

	//---------------- y ------------------

	//Y���W�̎擾
	inline float getPosY() { return position.y; }

	//Y���W���~�߂�
	inline float setPosY(float y) { position.y = y - RADIUS; return position.y; }

	//Y���W���~�߂�(������)
	inline float setUnderPosY(float y) { position.y = y + RADIUS; return position.y; }

	//Y���x�̎擾
	inline float getSpeedY() { return velocity.y; }

	//Y���x��0�ɂ���
	inline float setSpeedY() { velocity.y = 0; return velocity.y; }

	//------------ ���̑� -----------------

	//�傫���̎擾
	inline float getRadius() { return RADIUS; }

	//�n�ʔ��肩�ǂ����̎擾
	inline bool getIsGround() { return isGround; }

	//�n�ʔ���ɂ���
	inline bool setIsGround() { isGround = true; unGrip = 0; return isGround; }
	
	//�^�[�U���Q�[�W�̎擾
	inline int getTarzanGage() { return TarzanGage; }

	//�^�[�U���Q�[�W�����Z�b�g������
	inline int resetTarzanGage() { TarzanGage = 0; return TarzanGage; }

	//�^�[�U���Q�[�W���񕜂���
	inline int RecoveryTarzanGage() { TarzanGage = TARZAN_GAGE; return TarzanGage; }

	//�O���b�v�t���O��߂�
	inline bool setIsGrip() { isGrip = false; return isGrip; }

	//������0�ɂ���
	inline bool setLength() { length = 0; return length; }

	//�摜�𓮂���
	inline int MoveDrawX() { drawX += 32; return drawX; }

	//�摜�̈ʒu��0�ɖ߂�
	inline int resetDrawX() { drawX = 0; return drawX; }

	//drawX�̎擾
	inline int getDrawX() { return drawX; }

	//�|�W�V�������Z�b�g
	inline Vec2 resetPosition() { position = { 200.0f,500.0f }; return position; }

	//�Z���^�[���Z�b�g
	inline Vec2 resetCenter() { center = { center.x = position.x + VINE_LENGTH ,center.y = position.y - 500 }; return center; }

	//�v���C���[�̏�����
	inline void resetPlayer() {
		position = { 200.0f,500.0f };
		GripGage = 0;
		TarzanGage = TARZAN_GAGE;
		drawX = 0;
		isGrip = false;
		isGround = false;
		length = 0;
		state = IDLE;
		unGrip = 0;
		center.y = position.y - 500;
		center.x = position.x + VINE_LENGTH;
		velocity = { 0.0f,0.0f };
	}

	// ���ׂẲ����~�߂�
	void stopAudio();

private:

	void Move();

	void Collision(Vec2& scroll);



	//���W
	Vec2 position;

	//���x
	Vec2 velocity;

	//���S���W
	Vec2 center;

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

	//����
	float length;

	//�摜
	int textureHandle;

	//�摜�`��̈ʒu
	int drawX;

	// �摜���܂Ƃ߂�����(�����o����Δz��ɂ���)
	int textures[PLAYER_STATE_NUM];

	// �ǂ̉摜���o����(�ǂ̏��������邩)
	PLAYERSTATE state;

	// �ۑ��̉摜
	int loghandle;



	// ����炷���߂̕ϐ�
	// 0: ����
	// 1: ���n
	// 2: �c�^���܂�
	int soundHandles[3];
	int soundChecks[3];



};

