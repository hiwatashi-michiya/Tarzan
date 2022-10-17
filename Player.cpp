#include "Player.h"
#include "Map.h"
#include <Novice.h>
#include "Wall.h"

Player::Player()
	: position({ 100.0f,100.0f }), velocity({ 5.0f,5.0f }), radius(30), center({0.0f,0.0f}),
	color(0xFFFFFFFF), isGrip(false), TarzanGage(TARZAN_GAGE), GripGage(0), unGrip(0),isGround(false)
{

}

Player::Player(Vec2 position, Vec2 velocity, float radius, Vec2 center, int color, 
	bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround)
	: position({ position.x,position.y }), velocity({ velocity.x,velocity.y }), radius(radius),
	center({ center.x,center.y }), color(color), isGrip(false), TarzanGage(TARZAN_GAGE), 
	GripGage(0), unGrip(unGrip), isGround(isGround)
{

}

//-----------------------------------

void Player::Update(int* scrollX) {

	Move();

	Collision(scrollX);

}

void Player::Draw(int scrollX) {

	for (int i = 1; i < 32; i++) {
		Novice::DrawLine(1280 * i - scrollX, 0, 1280 * i - scrollX, 720, WHITE);
	}


	Novice::DrawEllipse(center.x - scrollX, (center.y), 10, 10, 0.0f, GREEN, kFillModeWireFrame);
	if (isGrip) {
		Novice::DrawLine(position.x - scrollX, (position.y), center.x - scrollX, (center.y), GREEN);
	}
	int color = RED + ((int)(TarzanGage * TARZAN_COLOR) << 16) + ((int)(TarzanGage * TARZAN_COLOR) << 8);
	Novice::DrawEllipse(position.x - scrollX, (position.y), radius, radius, 0.0f, color, kFillModeSolid);
	Novice::DrawEllipse(position.x + velocity.x - scrollX, (position.y + velocity.y), radius, radius, 0.0f, 0xFF0000FF, kFillModeWireFrame);

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
				isGrip = true;

				// 中心までのベクトルを出す
				Vec2 PtC;
				PtC = { center.x - position.x,center.y - position.y };
				PtC = PtC.normarize();


				// 左回りの垂直な線に変える
				velocity.x = -PtC.y * velocity.length();
				velocity.y = PtC.x * velocity.length();

				velocity.x += PtC.normarize().x;
				velocity.y += PtC.normarize().y;


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
		float newV = 1 + GripGage / 500.0f;
		velocity.x *= newV;
		GripGage = 0;
	}
	//DrawEllipse(position.X + VINE_LENGTH, 600, 20, 20, WHITE, kFillModeWireFrame);

	// 重力加算
	velocity.y += GRAVITY;
	// 速度を座標に加算
	position.x += velocity.x;
	position.y += velocity.y;
	

}

void Player::Collision(int* scrollX) {

	// 範囲内にする
	// 下側
	if (WINDOW_HEIGHT - radius <= position.y) {
		position.y = WINDOW_HEIGHT - radius;
		TarzanGage = TARZAN_GAGE;
		velocity.y = 0;
		isGround = true;
	}
	else {
		isGround = false;
	}
	// 左側
	if (position.x - radius <= 0) {
		position.x = radius;
		velocity.x *= -1;
	}
	*scrollX = position.x - 640;
	if (*scrollX <= 0) {
		*scrollX = 0;
	}
	else if (1280 * (32 - 1) <= *scrollX) {
		*scrollX = 1280 * (32 - 1);
	}

}


