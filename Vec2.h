#pragma once

//struct Vec2
//{
// float x;
// float y;
//}

class Vec2 {

	//�A�N�Z�X�͈� : �O���炢����Ȃ�
private:


	//�A�N�Z�X�͈� : �O���炢�����A�����
public:

	float x;
	float y;

	//�f�t�H���g�R���X�g���N�^
	Vec2();

	//��������R���X�g���N�^(���d��`�A�I�[�o�[���[�h)
	Vec2(float x, float y);

	Vec2 operator+(const Vec2& other);//Vec2 + Vec2
	Vec2 operator-(const Vec2& other);//Vec2 - Vec2

	const Vec2 operator+=(const Vec2& other);//Vec2 += Vec2
	const Vec2 operator-=(const Vec2& other);//Vec2 -= Vec2

	float length();
	float posX();
	float posY();

	Vec2 normarize();

	/// <summary>
	/// ���W����͂��Ċp�x���o��
	/// </summary>
	/// <returns>���߂����W�A���l</returns>
	float ATAN2();

	/// <summary>
	/// �P�ʉ~��� x �l
	/// </summary>
	/// <returns>�x�N�g���̃��W�A�����Z�o���A x �l��Ԃ�</returns>
	float COSF();

	/// <summary>
	/// �P�ʉ~��� y �l
	/// </summary>
	/// <returns>�x�N�g���̃��W�A�����Z�o���A y �l��Ԃ�</returns>
	float SINF();

};