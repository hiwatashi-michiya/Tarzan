#pragma once

enum Scene {
	TITLE,
	STAGESELECT,
	GAMEPLAY
};

//���݂̃V�[��
Scene scene = TITLE;

//���̃V�[��
Scene nextScene = GAMEPLAY;

//�V�[���؂�ւ��ɓ��邩�ǂ���
bool sceneChange = false;

//�؂�ւ����̃J�E���g
int sceneCount = 0;

//�����x�ω�
int clearly = 0x0000000F + sceneCount * 4;

//�S�[������
bool isGoal = false;

