#pragma once

// �C���X�^���X���̕K�v�Ȃ�
// Easing �I�u�W�F�N�g��;�@�̂悤�ɏ����Ȃ��ėǂ�

/*�@�C�[�W���O�`�[�g�V�[�g�Q�Ɓi����[1]����E��[30]�ɂ����āj�@*/

///		�g�����F�ᕶ(Use�֐��g��Ȃ��ق�)
///		if(�t���O == true){
///			T = Easing::EaseInSine(num);		//Easing(�N���X��)::EaseInSine(�N���X���ϐ���)
///			num += spd;
///			pos_x = (1 - T) * �n�_ + T * �I�_;
///			pos_y = (1 - T) * �n�_ + T * �I�_;
///			if(num >= 1.0f){
///				�t���O = false;
///			}
///		}

///		�g�����F�ᕶ
///		if(�t���O == true) {
///			// Easing(�N���X��)::EaseInSine(�N���X���ϐ���)
///			if(Use(�����������|�W�V����, �X�^�[�g�ʒl,�I���ʒu,Easing::�C�[�W���O�^�C�v,�A�C�[�W���O�̃X�s�[�h, ���`�ۊǗp�̒l)){
///				�t���O = false;
///			}
///		}

class Easing {
public:
	static enum Type {
		kInSine = 0,
		kOutSine,
		kInOutSine,
		kInQuad,
		kOutQuad,
		kInOutQuad,
		kInCubic,
		kOutCubic,
		kInOutCubic,
		kInQuart,
		kOutQuart,
		kInOutQuart,
		kInQuint,
		kOutQuint,
		kInOutQuint,
		kInExpo,
		kOutExpo,
		kInOutExpo,
		kInCirc,
		kOutCirc,
		kInOutCirc,
		kInBack,
		kOutBack,
		kInOutBack,
		kInElastic,
		kOutElastic,
		kInOutElastic,
		kInBounce,
		kOutBounce,
		kInOutBounce
	} type;

	/*
	�C�[�W���O

	�������F�C�[�W���O�������|�W�V�����@X�@�������F�C�[�W���O�������|�W�V�����@Y�@
	��O�����F�X�^�[�g�|�W�V�����@�@�@�@X  �@��l�����F�X�^�[�g�|�W�V�����@�@�@�@Y�@
	��܈����F�G���h�|�W�V�����@�@�@�@�@X�@��܈����F�G���h�|�W�V�����@�@�@�@�@Y
	�掵�����F�C�[�W���O�̃^�C�v(�ڂ����̓C�[�W���O�`�[�g�V�[�g���Q��) URL��https://easings.net/ja#
	�攪�����F�C�[�W���O�̃X�s�[�h
	�攪�����F���`�ۊǗp�̐���(0�`�P�͈̔͊O�̐����������0�ɏ����������)

	�߂�l�F�P�F�C�[�W���O�I���
	�@�@�@�@0 : �C�[�W���O��
	*/
	static bool Use(float& PosX, float& PosY, const float& startPosX, const float& startPosY, const float& endPosX, const float& endPosY, Type type, float spd, float& num);
	/*
	�C�[�W���O

	�������F�C�[�W���O�������|�W�V����
	�������F�X�^�[�g�|�W�V����
	��O�����F�G���h�|�W�V����
	��l�����F�C�[�W���O�̃^�C�v(�ڂ����̓C�[�W���O�`�[�g�V�[�g���Q��) URL��https://easings.net/ja#
	��܈����F�C�[�W���O�̃X�s�[�h
	��Z�����F���`�ۊǗp�̐���(0�`�P�͈̔͊O�̐����������0�ɏ����������)

	�߂�l�F�P�F�C�[�W���O�I���
	�@�@�@�@0 : �C�[�W���O��
	*/
	static bool Use(float& Pos, const float& startPos, const float& endPos, Type type, float spd, float& num);



	///
	///�ȉ��C�[�W���O�`�[�g�V�[�g�ۃp�N��
	/// �����̓C�[�W���O�`�[�g�V�[�g�̏��Ԃɏ���
	/// Use�֐���������Ȃ��Ƃ��͈ȉ��̊֐����g���Ă�������
	/// �g�p��͏�
	/// 

	//	1��
	static float InSine(float x);
	//	2
	static float OutSine(float x);
	//	3
	static float InOutSine(float x);
	//	4
	static float InQuad(float x);
	//	5
	static float OutQuad(float x);
	//	6
	static  float InOutQuad(float x);
	//	7
	static  float InCubic(float x);
	//	8
	static  float OutCubic(float x);
	//	9
	static float InOutCubic(float x);
	//	10
	static float InQuart(float x);
	//	11
	static float OutQuart(float x);
	//	12
	static float InOutQuart(float x);
	//	13
	static float InQuint(float x);
	//	14
	static float OutQuint(float x);
	//	15
	static float InOutQuint(float x);
	//	16
	static float InExpo(float x);
	//	17
	static float OutExpo(float x);
	//	18
	static float InOutExpo(float x);
	//	19
	static float InCirc(float x);
	//	20
	static float OutCirc(float x);
	//	21
	static float InOutCirc(float x);
	//	22
	static float InBack(float x);
	//	23
	static float OutBack(float x);
	//	24
	static float InOutBack(float x);
	//	25
	static float InElastic(float x);
	//	26
	static float OutElastic(float x);
	//	27
	static float InOutElastic(float x);
	//	28
	static float InBounce(float x);
	//	29
	static float OutBounce(float x);
	//	30
	static float InOutBounce(float x);

private:
	static void EaseType(const float& num, float& T, Type type);
};