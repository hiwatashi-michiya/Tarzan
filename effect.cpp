#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>


#pragma region �p�[�e�B�N���̏��E���E�ҋ@����

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
	Vector2 pos;
	int time;
};

//�p�[�e�B�N���̍ő吔��ݒ�
const int emitterMax = 120;

//�p�[�e�B�N�����o���Ƃ��̑ҋ@����
int coolTime = 0;


//�p�[�e�B�N���̏���ݒ肷��\����
// <�p�[�e�B�N�����\������Ă��邩(�t���O)>
// <X���W,Y���W>
// <X���̑傫��,Y���̑傫��>
// <�p�x>
// <�F>
//��ݒ肷��
//�����ǉ��v�f������Βǉ����Ă��悢
typedef struct Effect {
	int isActive;
	Vector2 pos;
	Vector2 size;
	float angle;
	unsigned int color;
};

//�G�t�F�N�g�p�̕ϐ���������
Effect effect[emitterMax]{};

//�����G�t�F�N�g�̕\�����Ԃ̐ݒ�
int displayTimeA = 6;
int displayTimeB = 6;
int displayTimeC = 6;
int displayTimeD = 6;

//�t�F�[�h�p�̐F�v�f��ۑ�����ϐ�
unsigned int screenColor = 0x00000000;

//�V�F�C�N���̍��W��ۑ�����ϐ�
Vector2 shakePos{
	0,
	0
};
int shakeTime = 0;

#pragma endregion

#pragma region �����Ɗp�x

//�p�x��ݒ�
float theta = {};

//X���W��Y���W�̈ړ����x���p�x�ɂ���ĕύX����ۂ̒l��ۑ�����ϐ�
float moveX = {};
float moveY = {};

//������ۑ�����ϐ�
float randamNum = 0;

#pragma endregion

#pragma region �p�[�e�B�N���̑��x

//�g�U�^
//�ړ����x�̊��ݒ�
float moveSpeedDiffusion = 1.5;
float moveSpeedDiffusionX[emitterMax] = {};
float moveSpeedDiffusionY[emitterMax] = {};

//�ᑬ�x�^
//�ړ����x�̊��ݒ�
float moveSpeed = 1.5;
float moveSpeedX[emitterMax] = {};
float moveSpeedY[emitterMax] = {};

//���x���^
//�ړ����x�̊��ݒ�
float moveSpeedLine = 1.5;
float moveSpeedLineX[emitterMax] = {};
float moveSpeedLineY[emitterMax] = {};

//�����^
//�ړ����x�̊��ݒ�
float moveSpeedlanding = 1.5;
float moveSpeedlandingX[emitterMax] = {};
float moveSpeedlandingY[emitterMax] = {};

//�Փˌ^(���E)
float moveSpeedClash = 1;
float moveSpeedClashX[emitterMax] = {};
float moveSpeedClashY[emitterMax] = {};

#pragma endregion



#pragma region �t���O�Ȃ�



#pragma endregion

#pragma region �p�[�e�B�N���̕ϐ��̏������p�֐�

//�g�U
Effect inisharaizuDiffusion() {

	return Effect{
		false,
		{0,0},
		{6,8},
		0.0f,
		0xFFFFFF77
	};

}

//���x
Effect inisharaizuSpeed() {

	return Effect{
		false,
		{0,0},
		{4,10},
		0.0f,
		0xFF000088
	};

}

//���x��
Effect inisharaizuSpeedLine() {

	return Effect{
		false,
		{0,0},
		{8,1},
		0.0f,
		0xFFFFFFAA
	};

}

//�c��
Effect inisharaizuAfterImage() {

	return Effect{
		false,
		{0,0},
		{32,32},
		0.0f,
		0xFFFFFFFF
	};

}

//����
Effect inisharaizuLanding() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0xFF00FFFF
	};

}

//���Փ�
Effect inisharaizuLeftClash() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0xFF0000FF
	};

}

//�E�Փ�
Effect inisharaizuRightClash() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0x0000FFFF
	};

}

#pragma endregion


#pragma region �p�[�e�B�N���̔�������(�����ƏՓ˂͔����ƈړ������������Ă���)

//�g�U�^�p�[�e�B�N��
void diffusionParticle(float posX, float posY, Effect effect[], int* displayTime) {

	int disNum = 0;

	//for���Ńp�[�e�B�N�����Ǘ�
	//1�\�����邲�Ƃ�for���̃��[�v�𔲂���
	for (int i = 0; i < emitterMax; i++) {

		//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
		if (effect[i].isActive == false) {

			//�����ɉ����Ĉړ����������ύX����

			//���W
			effect[i].pos.x = posX;
			effect[i].pos.y = posY;

			randamNum = (rand() % 200) * 0.1;
			theta = (randamNum / 2.0) * M_PI;
			moveX = cosf(theta);
			moveY = sinf(theta);

			moveSpeedDiffusionX[i] = (moveX * moveSpeedDiffusion) / 2;
			moveSpeedDiffusionY[i] = (moveY * -moveSpeedDiffusion) / 2;

			//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
			displayTime[i] = 30;

			//�p�[�e�B�N����\��������
			effect[i].isActive = true;

			//for���̃��[�v�𔲂���
			disNum++;

			if (disNum >= 3) {
				break;
			}

		}
	}
}

//���x�p�[�e�B�N��
void speedParticle(float posX, float posY, float vel, Effect effect[], int* displayTime) {

	int disNum = 0;

	//�ҋ@���Ԃ̌������s��
	if (coolTime > 0) {

		coolTime--;

	}

	//�p�[�e�B�N�����o���Ƃ��̑ҋ@���Ԃ�0�̎��ɏo��������
	if (coolTime == 0) {

		//for���Ńp�[�e�B�N�����Ǘ�
		//1�\�����邲�Ƃ�for���̃��[�v�𔲂���
		for (int i = 0; i < emitterMax; i++) {

			//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
			if (effect[i].isActive == false) {

				//�����ɉ����Ĉړ����������ύX����

				//���W
				effect[i].pos.x = posX;
				effect[i].pos.y = posY + (rand() % 12) - 6;

				if (vel > 0) {
					moveSpeedX[i] = -1;
					moveSpeedY[i] = 0;
				}
				else if (vel < 0) {
					moveSpeedX[i] = 1;
					moveSpeedY[i] = 0;
				}

				//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
				displayTime[i] = 6;

				//�p�[�e�B�N����\��������
				effect[i].isActive = true;

				//for���̃��[�v�𔲂���
				disNum++;

				if (disNum >= 2) {
					break;
				}

			}

			//�ҋ@���Ԃ�ݒ�
			coolTime = 0;

		}

	}
}

//�������p�[�e�B�N��
void speedLineParticle(float posX, float posY, float vel, Effect effect[], int* displayTime) {

	//�ҋ@���Ԃ̌������s��
	if (coolTime > 0) {

		coolTime--;

	}

	//�p�[�e�B�N�����o���Ƃ��̑ҋ@���Ԃ�0�̎��ɏo��������
	if (coolTime == 0) {

		//for���Ńp�[�e�B�N�����Ǘ�
		//1�\�����邲�Ƃ�for���̃��[�v�𔲂���
		for (int i = 0; i < emitterMax; i += 3) {

			//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
			if (effect[i].isActive == false) {

				//�����ɉ����Ĉړ����������ύX����

				//���W
				if (vel > 0) {
					effect[i].pos.x = posX + 32;
					effect[i + 1].pos.x = posX + 32;
					effect[i + 2].pos.x = posX + 32;
				}
				else if (vel < 0) {
					effect[i].pos.x = posX - 32;
					effect[i + 1].pos.x = posX - 32;
					effect[i + 2].pos.x = posX - 32;
				}

				effect[i].pos.y = posY + (rand() % 28) - 7;
				effect[i + 1].pos.y = posY + (rand() % 28) - 14;
				effect[i + 2].pos.y = posY + (rand() % 28) - 21;

				//�ړ���
				if (vel > 0) {
					moveSpeedLineX[i] = -8;
					moveSpeedLineY[i] = 0;
					moveSpeedLineX[i + 1] = -8;
					moveSpeedLineY[i + 1] = 0;
					moveSpeedLineX[i + 2] = -8;
					moveSpeedLineY[i + 2] = 0;
				}
				else if (vel < 0) {
					moveSpeedLineX[i] = 8;
					moveSpeedLineY[i] = 0;
					moveSpeedLineX[i + 1] = 8;
					moveSpeedLineY[i + 1] = 0;
					moveSpeedLineX[i + 2] = 8;
					moveSpeedLineY[i + 2] = 0;
				}

				//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
				displayTime[i] = 5.0f;
				displayTime[i + 1] = 5.0f;
				displayTime[i + 2] = 5.0f;

				//�p�[�e�B�N����\��������
				effect[i].isActive = true;
				effect[i + 1].isActive = true;
				effect[i + 2].isActive = true;

				//for���̃��[�v�𔲂���
				break;
			}

			//�ҋ@���Ԃ�ݒ�
			//coolTime = 0;

		}
	}
}

//�c��
void afterImage(float posX, float posY, Effect effect[], int* displayTime) {


	//�ҋ@���Ԃ̌������s��
	if (coolTime > 0) {

		coolTime--;

	}

	//�p�[�e�B�N�����o���Ƃ��̑ҋ@���Ԃ�0�̎��ɏo��������
	if (coolTime == 0) {

		//for���Ńp�[�e�B�N�����Ǘ�
			//1�\�����邲�Ƃ�for���̃��[�v�𔲂���
		for (int i = 0; i < emitterMax; i++) {

			//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
			if (effect[i].isActive == false) {

				//�����ɉ����Ĉړ����������ύX����

				//���W
				effect[i].pos.x = posX;
				effect[i].pos.y = posY;

				//�c���̓����x��ύX
				effect[i].color = 0x555555FF;

				//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
				displayTime[i] = 30;

				//�p�[�e�B�N����\��������
				effect[i].isActive = true;

				//for���̃��[�v�𔲂���
				break;
			}

			//�ҋ@���Ԃ�ݒ�
			coolTime = 2;

		}
	}
}

//������
void landingParticle(float posX, float posY, Effect effect[]) {

	//�\������
	//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
	if (effect[0].isActive == false) {

		//���W
		//0
		effect[0].pos.x = posX;
		effect[0].pos.y = posY + 12.0f;
		//1
		effect[1].pos.x = posX;
		effect[1].pos.y = posY + 12.0f;
		//2
		effect[2].pos.x = posX;
		effect[2].pos.y = posY + 12.0f;
		//3
		effect[3].pos.x = posX;
		effect[3].pos.y = posY + 12.0f;

		//�ړ���
		//0
		moveSpeedlandingX[0] = -4;
		moveSpeedlandingY[0] = -0.5;
		//1
		moveSpeedlandingX[1] = -3;
		moveSpeedlandingY[1] = -0.25;
		//2
		moveSpeedlandingX[2] = 3;
		moveSpeedlandingY[2] = -0.25;
		//3
		moveSpeedlandingX[3] = 4;
		moveSpeedlandingY[3] = -0.5;

		//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//�p�[�e�B�N����\��������
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//�ړ�����
	//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
	if (effect[3].isActive == true) {

		//�p�[�e�B�N���̕\�����Ԃ�����������
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//�p�[�e�B�N����������Ɉ�葬�x�ňړ�������
		//�p�[�e�B�N�����Ƃ�x���̈ړ����s��
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
		if (displayTimeD <= 0.0f) {

			//�p�[�e�B�N�����\���ɂ���
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

//�������ړ����̏Փ�
void leftClashParticle(float posX, float posY, Effect effect[]) {

	//�\������
	//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
	if (effect[0].isActive == false) {

		//���W
		//0
		effect[0].pos.x = posX - 12.0f;
		effect[0].pos.y = posY;
		//1
		effect[1].pos.x = posX - 12.0f;
		effect[1].pos.y = posY;
		//2
		effect[2].pos.x = posX - 12.0f;
		effect[2].pos.y = posY;
		//3
		effect[3].pos.x = posX - 12.0f;
		effect[3].pos.y = posY;

		//�ړ���
		//0
		moveSpeedlandingX[0] = 1;
		moveSpeedlandingY[0] = -4;
		//1
		moveSpeedlandingX[1] = 1.5;
		moveSpeedlandingY[1] = -3;
		//2
		moveSpeedlandingX[2] = 1.5;
		moveSpeedlandingY[2] = 3;
		//3
		moveSpeedlandingX[3] = 2;
		moveSpeedlandingY[3] = 4;

		//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//�p�[�e�B�N����\��������
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//�ړ�����
	//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
	if (effect[3].isActive == true) {

		//�p�[�e�B�N���̕\�����Ԃ�����������
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//�p�[�e�B�N����������Ɉ�葬�x�ňړ�������
		//�p�[�e�B�N�����Ƃ�x���̈ړ����s��
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
		if (displayTimeD <= 0.0f) {

			//�p�[�e�B�N�����\���ɂ���
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

//�E�����ړ����̏Փ�
void rightClashParticle(float posX, float posY, Effect effect[]) {

	//�\������
	//i�Ԗڂ̃p�[�e�B�N������\���ł���Ε\������
	if (effect[0].isActive == false) {

		//���W
		//0
		effect[0].pos.x = posX + 12.0f;
		effect[0].pos.y = posY;
		//1
		effect[1].pos.x = posX + 12.0f;
		effect[1].pos.y = posY;
		//2
		effect[2].pos.x = posX + 12.0f;
		effect[2].pos.y = posY;
		//3
		effect[3].pos.x = posX + 12.0f;
		effect[3].pos.y = posY;

		//�ړ���
		//0
		moveSpeedlandingX[0] = -0.5;
		moveSpeedlandingY[0] = -4;
		//1
		moveSpeedlandingX[1] = -0.25;
		moveSpeedlandingY[1] = -3;
		//2
		moveSpeedlandingX[2] = -0.25;
		moveSpeedlandingY[2] = 3;
		//3
		moveSpeedlandingX[3] = -0.5;
		moveSpeedlandingY[3] = 4;

		//�p�[�e�B�N����\���������鎞�Ԃ�ݒ�
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//�p�[�e�B�N����\��������
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//�ړ�����
	//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
	if (effect[3].isActive == true) {

		//�p�[�e�B�N���̕\�����Ԃ�����������
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//�p�[�e�B�N����������Ɉ�葬�x�ňړ�������
		//�p�[�e�B�N�����Ƃ�x���̈ړ����s��
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
		if (displayTimeD <= 0.0f) {

			//�p�[�e�B�N�����\���ɂ���
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

#pragma endregion


#pragma region �p�[�e�B�N���̈ړ��Ə��ŏ���

//�g�U�^�p�[�e�B�N��
void diffusionParticleMove(Effect effect[], int* displayTime) {

	//for���ŕ����Ǘ�
	for (int i = 0; i < emitterMax; i++) {
		//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
		if (effect[i].isActive == true) {

			//�p�[�e�B�N���̕\�����Ԃ�����������
			displayTime[i]--;

			//�p�[�e�B�N������葬�x�ňړ�������
			effect[i].pos.x += moveSpeedDiffusionX[i];
			effect[i].pos.y += moveSpeedDiffusionY[i];


			//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
			if (displayTime[i] <= 0.0f) {

				//�p�[�e�B�N�����\���ɂ���
				effect[i].isActive = false;

			}
		}
	}
}

//���x�p�[�e�B�N��
void speedParticleMove(Effect effect[], int* displayTime) {

	//for���ŕ����Ǘ�
	for (int i = 0; i < emitterMax; i++) {
		//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
		if (effect[i].isActive == true) {

			//�p�[�e�B�N���̕\�����Ԃ�����������
			displayTime[i]--;

			//�p�[�e�B�N����������Ɉ�葬�x�ňړ�������
			//�p�[�e�B�N�����Ƃ�x���̈ړ����s��
			effect[i].pos.x += moveSpeedX[i];
			effect[i].pos.y += moveSpeedY[i];


			//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
			if (displayTime[i] <= 0.0f) {

				//�p�[�e�B�N�����\���ɂ���
				effect[i].isActive = false;

			}
		}
	}
}

//�������p�[�e�B�N��
void speedLineParticleMove(Effect effect[], int* displayTime) {

	//for���ŕ����Ǘ�
	for (int i = 0; i < emitterMax; i++) {

		//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
		if (effect[i].isActive == true) {

			//�p�[�e�B�N���̕\�����Ԃ�����������
			displayTime[i]--;

			//�p�[�e�B�N����������Ɉ�葬�x�ňړ�������
			//�p�[�e�B�N�����Ƃ�x���̈ړ����s��
			effect[i].pos.x += moveSpeedLineX[i];
			effect[i].pos.y += moveSpeedLineY[i];


			//�p�[�e�B�N���̏o����A���Ԍo�߂ŏ��ł�����
			if (displayTime[i] <= 0.0f) {

				//�p�[�e�B�N�����\���ɂ���
				effect[i].isActive = false;

			}
		}

	}
}

//�c��
void afterImageMove(float posX, float posY, Effect effect[], int* displayTime) {

	//for���ŕ����Ǘ�
	for (int i = 0; i < emitterMax; i++) {
		//i�Ԗڂ̃p�[�e�B�N�����\������Ă���ꍇ�A�ړ�����
		if (effect[i].isActive == true) {

			//�p�[�e�B�N���̕\�����Ԃ�����������
			displayTime[i]--;

			//�c���̓����x��ύX
			effect[i].color -= 0x11;

			//�p�[�e�B�N���̏o����A�����ɂȂ�������ł�����
			if (effect[i].color <= 0x55555500) {

				//�p�[�e�B�N�����\���ɂ���
				effect[i].isActive = false;

			}
		}

	}
}

#pragma endregion


#pragma region ��ʌn��

//��ʂ̃t�F�[�h�A�E�g
void screenFadeOut() {


	if (screenColor > 0x00000000) {

		screenColor -= 0x11;
	}

}

//��ʃt�F�[�h�C��
void screenFadeIn() {

	if (screenColor < 0x000000FF) {

		screenColor += 0x11;
	}
}

//�t�F�[�h�̕`�揈��
void screenFadeDraw() {

	Novice::DrawBox(
		0, 0,
		1280, 720,
		0.0f,
		screenColor,
		kFillModeSolid
	);

}

//�I�u�W�F�N�g�̃t�F�[�h�A�E�g
void objFadeOut(unsigned int color, int fadeSpeed) {

	//�����ɂȂ�܂œ����x��������
	switch (fadeSpeed) {

	case 1:

		if (color != 0xFFFFFF00) {

			color -= 0x05;

		}

		break;

	case 2:

		if (color != 0xFFFFFF00) {

			color -= 0x0A;

		}

		break;

	case 3:

		if (color != 0xFFFFFF00) {

			color -= 0x11;

		}

		break;

	case 4:

		if (color != 0xFFFFFF00) {

			color -= 0x22;

		}

		break;

	case 5:

		if (color != 0xFFFFFF00) {

			color -= 0x33;

		}

		break;
	}

}

//�V�F�C�N
ShakeList shake(ShakeList list) {

	if (list.time > 0) {

		list.time--;

		if (list.time > 30) {
			return ShakeList{
				rand() % 80 - 40.0f,
				rand() % 80 - 40.0f,
				list.time -1,
			};
		}

		if (list.time > 25) {
			return ShakeList{
				rand() % 60 - 40.0f,
				rand() % 60 - 40.0f,
				list.time - 1,
			};
		}

		if (list.time > 20) {
			return ShakeList{
				rand() % 50 - 20.0f,
				rand() % 50 - 20.0f,
				list.time - 1,
			};
		}

		else if (list.time > 15) {
			return ShakeList{
			rand() % 40 - 10.0f,
			rand() % 40 - 10.0f,
			list.time - 1,
			};
		}

		if (list.time > 10) {
			return ShakeList{
				rand() % 20 - 10.0f,
				rand() % 20 - 10.0f,
				list.time - 1,
			};
		}

		else if (list.time > 5) {
			return ShakeList{
			rand() % 10 - 4.0f,
			rand() % 10 - 4.0f,
			list.time -1,
			};
		}

		else if (list.time > 0) {
			return ShakeList{
			rand() % 5 - 2.0f,
			rand() % 5 - 2.0f,
			list.time - 1,
			};
		}

		if (list.time == 0) {
			return ShakeList{
			0.0f,
			0.0f,
			0,
			};
		}
	}
}


#pragma endregion