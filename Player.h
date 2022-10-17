#pragma once
#include "Vec2.h"


// 重力
const float GRAVITY = 1.0f;
// ツタを打ち出す距離
const int VINE_LENGTH = 250;
// ターザンゲージ
const int TARZAN_GAGE = 300;

// ターザンゲージに対応したカラーコード
const float TARZAN_COLOR = 255 / (float)TARZAN_GAGE;

class Player
{
public:
	Player();
	Player(Vec2 position, Vec2 velocity, float radius, Vec2 center, int color, 
		bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround);

	void Update(int* scrollX);

	void Draw(int scrollX);

	float KeepMaxSpeed(float maxSpeed);

	//---------------- x ------------------

	//X座標の取得
	inline float getPosX() { return position.x; }

	//X速度の取得
	inline float getSpeedX() { return velocity.x; }

	//X速度を反転させる
	inline float setSpeedX() { velocity.x *= -1; return velocity.x; }

	//X速度を加速させる
	inline float accelX() { velocity.x *= 1.001f; return velocity.x; }

	//X速度を減速させる
	inline float decelX() { velocity.x /= 1.005f;	return velocity.x; }

	//---------------- y ------------------

	//Y座標の取得
	inline float getPosY() { return position.y; }

	//Y座標を止める
	inline float setPosY(float y) { position.y = y - radius; return position.y; }

	//Y速度の取得
	inline float getSpeedY() { return velocity.y; }

	//Y速度を0にする
	inline float setSpeedY() { velocity.y = 0; return velocity.y; }

	//------------ その他 -----------------

	//大きさの取得
	inline float getRadius() { return radius; }

	//地面判定かどうかの取得
	inline bool getIsGround() { return isGround; }

	//地面判定にする
	inline bool setIsGround() { isGround = true; return isGround; }

	//ターザンゲージをリセットさせる
	inline int resetTarzanGage() { TarzanGage = 0; return TarzanGage; }

	//ターザンゲージを回復する
	inline int RecoveryTarzanGage() { TarzanGage = TARZAN_GAGE; return TarzanGage; }

private:

	void Move();

	void Collision(int* scrollX);

	

	//座標
	Vec2 position;

	//速度
	Vec2 velocity;

	//半径
	float radius;

	//中心座標
	Vec2 center;

	//色
	int color;

	//つかんでいるかどうかの判定
	bool isGrip;

	// ターザンゲージ
	int TarzanGage;

	// つかまったフレーム
	int GripGage;

	//つかまらないフレーム
	int unGrip;

	// 地面にいるか
	bool isGround;

};

