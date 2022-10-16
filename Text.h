#pragma once


class Text
{
public:
	Text();
	Text(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
		int textureHandle, int color, float afterX, float afterY, float speed);


private:

	float x;
	float y;

	float width;
	float height;

	float srcX;
	float srcY;
	float srcW;
	float srcH;

	int textureHandle;
	int color;

	float afterX;
	float afterY;
	float speed;

};

/// <summary>
/// �����ɉ摜���X���C�h������
/// </summary>
/// <param name="x">�ړ��O�����X���W</param>
/// <param name="y">�����Y���W</param>
/// <param name="width">����</param>
/// <param name="height">�c��</param>
/// <param name="srcX">�摜��̕`�悵�����͈͍���X���W</param>
/// <param name="srcY">�摜��̕`�悵�����͈͍���Y���W</param>
/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
/// <param name="color">�F</param>
/// <param name="afterX">�ړ���̍���X���W</param>
/// <param name="speed">�ړ������鑬�x</param>
void SlideLeft(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed);

/// <summary>
/// �E���ɉ摜���X���C�h������
/// </summary>
/// <param name="x">�ړ��O�����X���W</param>
/// <param name="y">�����Y���W</param>
/// <param name="width">����</param>
/// <param name="height">�c��</param>
/// <param name="srcX">�摜��̕`�悵�����͈͍���X���W</param>
/// <param name="srcY">�摜��̕`�悵�����͈͍���Y���W</param>
/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
/// <param name="color">�F</param>
/// <param name="afterX">�ړ���̍���X���W</param>
/// <param name="speed">�ړ������鑬�x</param>
void SlideRight(float x, float y, float width, float height, float srcX, float srcY, float srcW, float srcH,
	int textureHandle, int color, float afterX, float speed);
