#include "Key.h"
#include<Novice.h>

Key::Key()
{
}

void Key::Update() {

	// �L�[���͂��󂯎��
	memcpy(preKeys, keys, 256);//�ЂƂO�̃L�[���͂Ɉڂ�
	Novice::GetHitKeyStateAll(keys);//keys(���݂̃L�[���͂̔z��)���X�V����

}


bool Key::IsTrigger(int key) {

	if (preKeys[key] == 0 && keys[key] != 0) {
		return true;
	}

	return false;

}

bool Key::IsPress(int key) {

	if (keys[key] != 0) {
		return true;
	}

	return false;

}

char Key::keys[256] = { 0 };
char Key::preKeys[256] = { 0 };
