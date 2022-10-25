#pragma once

#include <Novice.h>
#include <math.h>
#include<time.h>
#include "Vec2.h"

//**�x�N�g���̍\����**//
typedef struct Vector2 {
	float x;
	float y;
};

typedef struct Vector2x2 {
	Vector2 Top;
	Vector2 Bottom;
};

typedef struct ShakeList {
	Vec2 pos;
	int time;
};

//**�p�[�e�B�N���̍\����**//

//�p�[�e�B�N���̍ő吔��ݒ�
const int emitterMax = 120;

//�G�t�F�N�g�����n�_�̐ݒ�
// <�p�[�e�B�N���𔭐��������Ԃł��邩(�t���O)>
// <X���W,Y���W>
//��ݒ肷��
//�����ǉ��v�f������Βǉ����Ă��悢
typedef struct EffectPoint {
	int isActive;
	Vector2 pos;
	Vector2 vel;
	float acc;
};

//�p�[�e�B�N���̏���ݒ肷��\����
// <�p�[�e�B�N�����\������Ă��邩(�t���O)>
// <X���W,Y���W>
// <X���̑傫��,Y���̑傫��>
// <�p�x>
// <�F>
// <�摜>
// <�������̊p���W>
// <�E�����̊p���W>
//��ݒ肷��
//�����ǉ��v�f������Βǉ����Ă��悢
typedef struct Effect {
	int isActive;
	Vector2 pos;
	Vector2 size;
	float angle;
	unsigned int color;
	int imagesPos;
	Vector2x2 left;
	Vector2x2 right;
};

#pragma region �p�[�e�B�N���̕ϐ��̏������p�֐�

//�g�U
Effect inisharaizuDiffusion();

//���x
Effect inisharaizuSpeed();

//���x��
Effect inisharaizuSpeedLine();

//�c��
Effect inisharaizuAfterImage();

//����
Effect inisharaizuLanding();

//���Փ�
Effect inisharaizuLeftClash();

//�E�Փ�
Effect inisharaizuRightClash();

#pragma endregion


#pragma region �p�[�e�B�N���̔�������(�������͔����ƈړ������������Ă���)

//�g�U�p�[�e�B�N��
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void diffusionParticle(float posX, float posY, Effect effect[], int* displayTime);


//���x�p�[�e�B�N��(�x��)
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̈ړ����x> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void speedParticle(float posX, float posY, float vel, Effect effect[], int* displayTime);


//�������p�[�e�B�N��
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̈ړ����x> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void speedLineParticle(float posX, float posY, float vel, Effect effect[], int* displayTime);


//�c��
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void afterImage(float posX, float posY, Effect effect[], int* displayTime);


//������
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void landingParticle(float posX, float posY, Effect effect[]);

//�������ړ����̏Փ�
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void leftClashParticle(float posX, float posY, Effect effect[]);

//�E�����ړ����̏Փ�
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void rightClashParticle(float posX, float posY, Effect effect[]);

#pragma endregion

#pragma region �p�[�e�B�N���̈ړ��Ə��ŏ���


//�g�U�p�[�e�B�N��
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void diffusionParticleMove(Effect effect[], int* displayTime);


//���x�p�[�e�B�N��(�x��)
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̈ړ����x> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void speedParticleMove(Effect effect[], int* displayTime);


//�������p�[�e�B�N��
// <�p�[�e�B�N���𔭐������钆�S�_��X���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̂�Y���W> 
// <�p�[�e�B�N���𔭐������钆�S�_�̈ړ����x> 
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void speedLineParticleMove(Effect effect[], int* displayTime);


//�c��
// <�o�����������p�[�e�B�N���̕ϐ���> 
// <�p�[�e�B�N����\����������t���[����> 
//����͂��邱��
//�o���E���ŁE�ړ����������ׂčs��
void afterImageMove(float posX, float posY, Effect effect[], int* displayTime);

#pragma endregion

#pragma region ��ʌn��

//��ʃt�F�[�h�A�E�g
//���͂���ϐ��͂Ȃ�
void screenFadeOut();

//��ʃt�F�[�h�C��
//���͂���ϐ��͂Ȃ�
void screenFadeIn();

//�t�F�[�h�̕`�揈��
//���͂���ϐ��͂Ȃ�
//�`�揈���ɔz�u���邱��
void screenFadeDraw();

//�I�u�W�F�N�g�̃t�F�[�h�A�E�g
// <�I�u�W�F�N�g�̐F>
// <�I�u�W�F�N�g�̏��ő��x(1(�x��)~5(����)�i�K�Őݒ�)>
//����͂��邱��
void objFadeOut(unsigned int color, int fadeSpeed);

//�V�F�C�N
// <�V�F�C�N�p�̍\����>
// <�v���C���[�̑��x>
//����͂��邱��
//�V�F�C�N���������Ƃ��̓V�F�C�N���鎞�Ԃ���͂��邱��
//���ԋy�уt���O��main.cpp�ŃI�t�܂��͍X�V���邱��
ShakeList shake(ShakeList list, float velX);

#pragma endregion

