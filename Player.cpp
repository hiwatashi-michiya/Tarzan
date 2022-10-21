#include "Player.h"
#include "Stage.h"
#include <Novice.h>
#include "Wall.h"

Player::Player()
	: position({ 100.0f,100.0f }), velocity({ 5.0f,5.0f }), center({ 0.0f,0.0f }),
	color(0xFFFFFFFF), isGrip(false), TarzanGage(TARZAN_GAGE), GripGage(0), unGrip(0), isGround(false), length(0), textureHandle(0)
{

}

Player::Player(Vec2 position, Vec2 velocity, Vec2 center, int color,
	bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround, float length, int textureHandle)
	: position({ position.x,position.y }), velocity({ velocity.x,velocity.y }),
	center({ center.x,center.y }), color(color), isGrip(false), TarzanGage(TARZAN_GAGE),
	GripGage(0), unGrip(unGrip), isGround(isGround), length(length), textureHandle(textureHandle)
{

}

//-----------------------------------

void Player::Update(Vec2* scroll) {

	Move();

	Collision(scroll);

}

void Player::Draw(Vec2 scroll) {

	for (int i = 1; i < 32; i++) {
		Novice::DrawLine(1280 * i - scroll.x, 0 - scroll.y, 1280 * i - scroll.x, 720 - scroll.y, WHITE);
	}

	// ���S
	Novice::DrawEllipse(center.x - scroll.x, (center.y) - scroll.y, 10, 10, 0.0f, GREEN, kFillModeWireFrame);
	// �͂�ł���Ƃ��̃c�^
	if (isGrip) {
		Novice::DrawLine(position.x - scroll.x, (position.y) - scroll.y, center.x - scroll.x, (center.y) - scroll.y, GREEN);
	}
	// �c��̃^�[�U���Q�[�W��\���F
	int color = RED + ((int)(TarzanGage * TARZAN_COLOR) << 16) + ((int)(TarzanGage * TARZAN_COLOR) << 8);
	//Novice::DrawEllipse(position.x - scrollX, (position.y), RADIUS, RADIUS, 0.0f, color, kFillModeSolid);

	if (isGrip) {}
	// �c�^��͂�ł�p�x�ɂ���ĕ`��̊p�x��ς���
	Vec2 ptc = { center.x - position.x,center.y - position.y };
	ptc = { -ptc.y,ptc.x };

	float cos = 1;
	float sin = 1;
	cos = ptc.COSF();
	sin = ptc.SINF();


	Vec2 lotatedLeftTop = { LEFTTOP.x + position.x,LEFTTOP.y + position.y };
	Vec2 lotatedRightTop = { RIGHTTOP.x + position.x,RIGHTTOP.y + position.y };
	Vec2 lotatedLeftBottom = { LEFTBOTTOM.x + position.x,LEFTBOTTOM.y + position.y };
	Vec2 lotatedRightBottom = { RIGHTBOTTOM.x + position.x,RIGHTBOTTOM.y + position.y };

	if (isGrip) {
		lotatedLeftTop.x = LEFTTOP.x * cos - LEFTTOP.y * sin + position.x;
		lotatedLeftTop.y = LEFTTOP.x * sin + LEFTTOP.y * cos + position.y;
		lotatedRightTop.x = RIGHTTOP.x * cos - RIGHTTOP.y * sin + position.x;
		lotatedRightTop.y = RIGHTTOP.x * sin + RIGHTTOP.y * cos + position.y;
		lotatedLeftBottom.x = LEFTBOTTOM.x * cos - LEFTBOTTOM.y * sin + position.x;
		lotatedLeftBottom.y = LEFTBOTTOM.x * sin + LEFTBOTTOM.y * cos + position.y;
		lotatedRightBottom.x = RIGHTBOTTOM.x * cos - RIGHTBOTTOM.y * sin + position.x;
		lotatedRightBottom.y = RIGHTBOTTOM.x * sin + RIGHTBOTTOM.y * cos + position.y;
	}

	// �^�[�U�����摜�ŕ\��
	Novice::DrawQuad(lotatedLeftTop.x - scroll.x, lotatedLeftTop.y - scroll.y, lotatedRightTop.x - scroll.x, lotatedRightTop.y - scroll.y,
		lotatedLeftBottom.x - scroll.x, lotatedLeftBottom.y - scroll.y, lotatedRightBottom.x - scroll.x, lotatedRightBottom.y - scroll.y,
		0, 0, 32, 32, textureHandle, color);
	// ���ɓ����ꏊ��\��
	Novice::DrawEllipse(position.x + velocity.x - scroll.x, (position.y + velocity.y) - scroll.y, RADIUS, RADIUS, 0.0f, 0xFF0000FF, kFillModeWireFrame);

	Novice::ScreenPrintf(0, 0, "%1.2f", position.x);
	Novice::ScreenPrintf(0, 20, "%1.2f", position.y);
	Novice::ScreenPrintf(0, 40, "%1.2f", velocity.x);
	Novice::ScreenPrintf(0, 60, "%1.2f", velocity.y);

}

float Player::KeepMaxSpeed(float maxSpeed) {

	if (velocity.x > maxSpeed) {
		maxSpeed = velocity.x;
	}

	return maxSpeed;

}

//-------------------------------------

void Player::Move() {


	if (isGround) {
		center.y = position.y - 500;
	}
	// �v���C���[�̐���s��
	if (!isGrip) {
		center.x = position.x + VINE_LENGTH;
	}


	// �����{�^��
	if (Novice::CheckHitKey(DIK_SPACE)) {
		//Novice::ScreenPrintf(10, 10, "Pushing SPACE");
		//DrawEllipse(position.X + VINE_LENGTH, 600, 20, 20, WHITE, kFillModeSolid);
		//Novice::DrawLine(position.X, S(position.y), position.X + VINE_LENGTH, S(600), GREEN);

		// �����ĕ߂܂�Ȃ�
		unGrip--;
		if (unGrip <= 0) {
			unGrip = 0;

			// �^�[�U���Q�[�W�����炷
			TarzanGage--;
			if (0 < TarzanGage && !isGround) {
				GripGage++;
				if (300 <= GripGage) {
					GripGage = 300;
				}
				isGrip = true;

				// ���S�܂ł̃x�N�g�����o��
				Vec2 ptc;
				ptc = { center.x - position.x,center.y - position.y };
				Vec2 normal = ptc.normarize();

				// ���񂾎��_�ł̋�����ۑ�
				if (length == 0) {
					length = ptc.length();
				}


				// ���S���琂���ȃx�N�g��
				Vec2 ver = { -normal.y,normal.x };// �x�N�g���𕪉����鎮
				// (s * a.X) + (t * b.X) = X, (s * a.Y) - (t * b.Y) = Y
				// ���̎��߂�����ϊ�����
				// ���S�̃x�N�g���ɐ����ȃx�N�g���̔{��
				float t, s;
				t = -(velocity.x * normal.y - velocity.y * normal.x) / (normal.x * ver.y - normal.y * ver.x);
				// ���S�ւ̔{��
				s = (velocity.x - t * ver.x) / normal.x;

				//	���x��ł�����(��������)
				float fixX = -s * normal.x;
				float fixY = -s * normal.y;

				// �X�J���[
				float scalar = velocity.length();

				// ���x������Ŏw�肷��
				if (t < -0.2f) {
					fixX = -scalar * ver.x;
					fixY = -scalar * ver.y;
				}
				else if (0.2f < t) {
					fixX = scalar * ver.x;
					fixY = scalar * ver.y;
				}

				// ��2
					// �L���������𒆐S�Ɍ������x�N�g���ƍ������ĕ␳����
					// ���̕��̃x�N�g�����Z�o
				Vec2 collection = { 0,0 };

				ptc.x = center.x - (position.x + fixX);
				ptc.y = center.y - (position.y + fixY);
				normal = ptc.normarize();


				// ����������
				float diffelence = ptc.length() - length;
				// ���a��߂��x�N�g��
				collection.x = normal.x * diffelence;
				collection.y = normal.y * diffelence;
				// �x�N�g�����C������
				fixX += collection.x;
				fixY += collection.y;

				velocity.x = fixX;
				velocity.y = fixY;

				// �����̐����Ȑ��ɕς���
				//velocity.x = -ptc.y * velocity.length();
				//velocity.y = ptc.x * velocity.length();

				//velocity.x += ptc.normarize().x;
				//velocity.y += ptc.normarize().y;


			}
			else if (TarzanGage <= 0) {
				TarzanGage = 0;
				isGrip = false;
			}
			else if (isGround) {
				velocity.y -= 20;
				unGrip = 17;
			}

		}
	}
	else if (!Novice::CheckHitKey(DIK_RETURN) && isGrip) {
		isGrip = false;
		// �͂񂾎��Ԃɉ����ĉ���
		float newV = 1 + GripGage / 400.0f;
		velocity.x *= newV;
		newV = 1 + GripGage / 200.0f;
		if (velocity.y < 0) {
			velocity.y *= newV;
		}
		length = 0;
		GripGage = 0;
	}
	//DrawEllipse(position.X + VINE_LENGTH, 600, 20, 20, WHITE, kFillModeWireFrame);

	// �d�͉��Z
	velocity.y += GRAVITY;
	// ���x�����W�ɉ��Z
	position.x += velocity.x;
	position.y += velocity.y;


}

void Player::Collision(Vec2* scroll) {

	// �͈͓��ɂ���
	// ����
	if (WINDOW_HEIGHT - RADIUS <= position.y) {
		position.y = WINDOW_HEIGHT - RADIUS;
		TarzanGage = TARZAN_GAGE;
		velocity.y = 0;
		isGround = true;
		length = 0;
		isGrip = false;
	}
	else {
		isGround = false;
	}
	// ����
	if (position.x - RADIUS <= 0) {
		position.x = RADIUS;
		velocity.x *= -1;
	}
	// x �l�̃X�N���[��
	(*scroll).x = position.x - 640;
	if ((*scroll).x <= 0) {
		(*scroll).x = 0;
	}
	else if (1280 * (32 - 1) <= (*scroll).x) {
		(*scroll).x = 1280 * (32 - 1);
	}
	// y �l�̃X�N���[��
	(*scroll).y = position.y - 480;
	if ((*scroll).y <= -720) {
		(*scroll).y = -720;
	}
	else if (0 <= (*scroll).y) {
		(*scroll).y = 0;
	}

}


