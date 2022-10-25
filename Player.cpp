#include "Player.h"
#include "Stage.h"
#include <Novice.h>
#include "Wall.h"

Player::Player()
	: position({ 100.0f,100.0f }), velocity({ 5.0f,5.0f }), center({ 0.0f,0.0f }),
	isGrip(false), TarzanGage(TARZAN_GAGE), GripGage(0), unGrip(0), isGround(false), length(0), drawX(0), state(IDLE)
{

}

Player::Player(Vec2 position, Vec2 velocity, Vec2 center,
	bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround, float length, int textureHandle, int drawX)
	: position({ position.x,position.y }), velocity({ velocity.x,velocity.y }),
	center({ center.x,center.y }), isGrip(false), TarzanGage(TARZAN_GAGE),
	GripGage(0), unGrip(unGrip), isGround(isGround), length(length), drawX(drawX)
{

}

Player::Player(Vec2 pos, int texturehandle[])
{
	position = pos;
	//textureHandle = texturehandle;
	for (int i = 0; i < PLAYER_STATE_NUM; i++) {
		textures[i] = texturehandle[i];
	}

	GripGage = 0;
	TarzanGage = TARZAN_GAGE;
	drawX = 0;
	isGrip = false;
	isGround = false;
	length = 0;
	state = IDLE;
	unGrip = 0;
	loghandle = Novice::LoadTexture("./Resources/Images/Player/log.png");

	soundHandles[0] = Novice::LoadAudio("./Resources/SE/run.wav");
	soundHandles[1] = Novice::LoadAudio("./Resources/SE/landing.wav");
	soundHandles[2] = Novice::LoadAudio("./Resources/SE/creak.wav");
	for (int i = 0; i < 3; i++) {
		soundChecks[i] = -1;
	}
}

//-----------------------------------

void Player::Update(Vec2& scroll) {

	Move();

	Collision(scroll);

}

void Player::Draw(Vec2 scroll) {

	switch (state)
	{
	case IDLE:
		Novice::ScreenPrintf(10, 10, "IDLE");
		break;
	case RUN:
		Novice::ScreenPrintf(10, 10, "RUN");
		break;
	case TARZAN:
		Novice::ScreenPrintf(10, 10, "TARZAN");
		break;
	case JUMP:
		Novice::ScreenPrintf(10, 10, "JUMP");
		break;
	case SKY:
		Novice::ScreenPrintf(10, 10, "SKY");
		break;
	case LANDING:
		Novice::ScreenPrintf(10, 10, "LANDING");
		break;
	default:
		break;
	}

	// 中心
	//Novice::DrawEllipse(center.x - scroll.x, (center.y) - scroll.y, 10, 10, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawSprite(center.x - 16 - scroll.x, center.y - 16 - scroll.y, loghandle, 1, 1, 0.0f, WHITE);
	// 掴んでいるときのツタ
	if (isGrip) {
		Novice::DrawLine(position.x - scroll.x, (position.y) - scroll.y, center.x - scroll.x, (center.y) - scroll.y, GREEN);
	}
	// 残りのターザンゲージを表す色
	int color = 0xFF0000FF + ((int)(TarzanGage * TARZAN_COLOR) << 16) + ((int)(TarzanGage * TARZAN_COLOR) << 8) - (int)(TarzanGage * TARZAN_COLOR);
	//Novice::DrawEllipse(position.x - scrollX, (position.y), RADIUS, RADIUS, 0.0f, color, kFillModeSolid);

	if (isGrip) {}
	// ツタを掴んでる角度によって描画の角度を変える
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

	// ターザンを画像で表示
	Novice::DrawEllipse(position.x - scroll.x, position.y - scroll.y, 16, 16, 0.0f, color, kFillModeSolid);

	if (velocity.x >= 0) {
		Novice::DrawQuad(lotatedLeftTop.x - scroll.x, lotatedLeftTop.y - scroll.y, lotatedRightTop.x - scroll.x, lotatedRightTop.y - scroll.y,
			lotatedLeftBottom.x - scroll.x, lotatedLeftBottom.y - scroll.y, lotatedRightBottom.x - scroll.x, lotatedRightBottom.y - scroll.y,
			drawX, 0, 32, 32, textures[(int)state], WHITE);
	}
	else {
		Novice::DrawQuad(lotatedRightTop.x - scroll.x, lotatedRightTop.y - scroll.y, lotatedLeftTop.x - scroll.x, lotatedLeftTop.y - scroll.y,
			lotatedRightBottom.x - scroll.x, lotatedRightBottom.y - scroll.y, lotatedLeftBottom.x - scroll.x, lotatedLeftBottom.y - scroll.y,
			drawX, 0, 32, 32, textures[(int)state], WHITE);
	}


	// 次に動く場所を表示
	//Novice::DrawEllipse(position.x + velocity.x - scroll.x, (position.y + velocity.y) - scroll.y, RADIUS, RADIUS, 0.0f, 0xFF0000FF, kFillModeWireFrame);

	//Novice::ScreenPrintf(0, 0, "%1.2f", position.x);
	//Novice::ScreenPrintf(0, 20, "%1.2f", position.y);
	//Novice::ScreenPrintf(0, 40, "%1.2f", velocity.x);
	//Novice::ScreenPrintf(0, 60, "%1.2f", velocity.y);

}

float Player::KeepMaxSpeed(float maxSpeed) {

	if (velocity.x > maxSpeed) {
		maxSpeed = velocity.x;
	}

	return maxSpeed;

}

void Player::stopAudio() {
	for (int i = 0; i < 3; i++)
	{
		Novice::StopAudio(soundChecks[i]);
	}
}

//-------------------------------------

void Player::Move() {


	if (isGround) {
		center.y = position.y - 500;
	}
	// プレイヤーの先を行く
	if (!isGrip) {
		center.x = position.x + VINE_LENGTH;
	}


	// ワンボタン
	if (Novice::CheckHitKey(DIK_SPACE)) {
		//Novice::ScreenPrintf(10, 10, "Pushing SPACE");
		//DrawEllipse(position.X + VINE_LENGTH, 600, 20, 20, WHITE, kFillModeSolid);
		//Novice::DrawLine(position.X, S(position.y), position.X + VINE_LENGTH, S(600), GREEN);

		// あえて捕まらない
		unGrip--;
		if (unGrip <= 0) {
			unGrip = 0;

			// ターザンゲージを減らす
			TarzanGage--;
			if (0 < TarzanGage && !isGround) {
				GripGage++;
				if (300 <= GripGage) {
					GripGage = 300;
				}
				isGrip = true;
				state = TARZAN;

				// ツタにつかまってる音を鳴らす
				if (!Novice::IsPlayingAudio(soundChecks[2]) || soundChecks[2] == -1) {
					soundChecks[2] = Novice::PlayAudio(soundHandles[2], 1, 0.5f);
				}
				else {
					Novice::ResumeAudio(soundChecks[2]);
				}



				// 中心までのベクトルを出す
				Vec2 ptc;
				ptc = { center.x - position.x,center.y - position.y };
				Vec2 normal = ptc.normarize();

				// つかんだ時点での距離を保存
				if (length == 0) {
					length = ptc.length();
				}


				// 中心から垂直なベクトル
				Vec2 ver = { -normal.y,normal.x };// ベクトルを分解する式
				// (s * a.X) + (t * b.X) = X, (s * a.Y) - (t * b.Y) = Y
				// ↑の式めっちゃ変換した
				// 中心のベクトルに垂直なベクトルの倍率
				float t, s;
				t = -(velocity.x * normal.y - velocity.y * normal.x) / (normal.x * ver.y - normal.y * ver.x);
				// 中心への倍率
				s = (velocity.x - t * ver.x) / normal.x;

				//	速度を打ち消す(減衰あり)
				float fixX = -s * normal.x;
				float fixY = -s * normal.y;

				// スカラー
				float scalar = velocity.length();

				// 速度を方向で指定する
				if (t < -0.2f) {
					fixX = -scalar * ver.x;
					fixY = -scalar * ver.y;
				}
				else if (0.2f < t) {
					fixX = scalar * ver.x;
					fixY = scalar * ver.y;
				}

				// 案2
				// 広がった分を中心に向かうベクトルと合成して補正する
				// その分のベクトルを算出
				Vec2 collection = { 0,0 };

				ptc.x = center.x - (position.x + fixX);
				ptc.y = center.y - (position.y + fixY);
				normal = ptc.normarize();


				// 生じた差異
				float diffelence = ptc.length() - length;
				// 半径を戻すベクトル
				collection.x = normal.x * diffelence;
				collection.y = normal.y * diffelence;
				// ベクトルを修正する
				fixX += collection.x;
				fixY += collection.y;

				velocity.x = fixX;
				velocity.y = fixY;

				// 左回りの垂直な線に変える
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
		// 掴んだ時間に応じて加速
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

	if (!isGrip) {
		state = SKY;
	}

	switch (state)
	{
	case IDLE:
		Novice::StopAudio(soundChecks[0]);
		Novice::PauseAudio(soundChecks[2]);
		break;
	case RUN:
		Novice::StopAudio(soundChecks[2]);
		// 音ならない
		if (!Novice::IsPlayingAudio(soundChecks[0]) || soundChecks[0] == -1) {
			soundChecks[0] = Novice::PlayAudio(soundHandles[0], 1, 1.0f);
		}
		break;
	case TARZAN:
		Novice::StopAudio(soundChecks[0]);
		break;
	case JUMP:
		Novice::StopAudio(soundChecks[0]);
		Novice::PauseAudio(soundChecks[2]);
		break;
	case SKY:
		Novice::StopAudio(soundChecks[0]);
		Novice::PauseAudio(soundChecks[2]);
		break;
	case LANDING:
		Novice::StopAudio(soundChecks[0]);
		Novice::PauseAudio(soundChecks[2]);
		if (!Novice::IsPlayingAudio(soundChecks[1]) || soundChecks[1] == -1) {
			soundChecks[1] = Novice::PlayAudio(soundHandles[1], 0, 0.5f);
		}
		break;
	default:
		break;
	}

	// 重力加算
	velocity.y += GRAVITY;
	// 速度を座標に加算
	position.x += velocity.x;
	position.y += velocity.y;


}

void Player::Collision(Vec2& scroll) {

	// 範囲内にする
	// 下側
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
	// 左側
	if (position.x - RADIUS <= 0) {
		position.x = RADIUS;
		velocity.x *= -1;
	}
	// x 値のスクロール
	scroll.x = position.x - 640;
	if (scroll.x <= 0) {
		scroll.x = 0;
	}
	else if (1280 * (32 - 1) <= scroll.x) {
		scroll.x = 1280 * (32 - 1);
	}
	// y 値のスクロール
	scroll.y = position.y - 480;
	if (scroll.y <= -720) {
		scroll.y = -720;
	}
	else if (0 <= scroll.y) {
		scroll.y = 0;
	}
	if (velocity.x == 0) {
		state = IDLE;
	}
}


