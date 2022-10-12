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
	Player(Vec2 position, Vec2 velocity, float radius, Vec2 center, int color, bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround);

	void Update(int* scrollX);

	void Draw(int scrollX);

	inline float getPosX() { return position.x; }

	inline float getSpeedX() { return velocity.x; }

	inline float getRadius() { return radius; }

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

