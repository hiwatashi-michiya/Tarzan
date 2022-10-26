#pragma once
#include "Vec2.h"


// プレイヤーの状態を分ける
enum PLAYERSTATE {
	IDLE,
	RUN,
	TARZAN,
	JUMP,
	SKY,
	LANDING
};

// プレイヤーの状態
const int PLAYER_STATE_NUM = 6;


// 重力
const float GRAVITY = 1.0f;
// ツタを打ち出す距離
const int VINE_LENGTH = 250;
// ターザンゲージ
const int TARZAN_GAGE = 300;

// ターザンゲージに対応したカラーコード
const float TARZAN_COLOR = 255 / (float)TARZAN_GAGE;

// 半径(当たり判定は円)
const int RADIUS = 16;

// 四隅の点
const Vec2 LEFTTOP = { -RADIUS,-RADIUS };
const Vec2 RIGHTTOP = { RADIUS - 1,-RADIUS };
const Vec2 LEFTBOTTOM = { -RADIUS,RADIUS - 1 };
const Vec2 RIGHTBOTTOM = { RADIUS - 1,RADIUS - 1 };

class Player
{
public:
	Player();
	Player(Vec2 position, Vec2 velocity, Vec2 center,
		bool isGrip, int TarzanGage, int GripGage, int unGrip, bool isGround, float length, int textureHandle, int drawX);

	Player(Vec2 pos, int texturehandle[]);

	void Update(Vec2& scroll);

	void Draw(Vec2 scroll);

	float KeepMaxSpeed(float maxSpeed);

	//---------------- x ------------------

	//X座標の取得
	inline float getPosX() { return position.x; }

	//X速度の取得
	inline float getSpeedX() { return velocity.x; }

	//X速度の取得(負の値)
	inline float getReverseSpeedX() { return -velocity.x; }

	//X速度を反転させる
	inline float setSpeedX() { velocity.x *= -1; return velocity.x; }

	//X速度を0にする
	inline float setSpeed0X() { velocity.x = 0; return velocity.x; }

	//X速度を加速させる
	inline float accelX() {

		if (velocity.x > 0) {
			if (velocity.x < 50) {
				velocity.x *= 1.005f;
			}
		}
		else {
			if (velocity.x > -50) {
				velocity.x *= 1.005f;
			}
		}
		
		return velocity.x;
	}

	//X速度を減速させる
	inline float decelX() { velocity.x /= 1.005f;	return velocity.x; }

	//---------------- y ------------------

	//Y座標の取得
	inline float getPosY() { return position.y; }

	//Y座標を止める
	inline float setPosY(float y) { position.y = y - RADIUS; return position.y; }

	//Y座標を止める(下判定)
	inline float setUnderPosY(float y) { position.y = y + RADIUS; return position.y; }

	//Y速度の取得
	inline float getSpeedY() { return velocity.y; }

	//Y速度を0にする
	inline float setSpeedY() { velocity.y = 0; return velocity.y; }

	//------------ その他 -----------------

	//大きさの取得
	inline float getRadius() { return RADIUS; }

	//地面判定かどうかの取得
	inline bool getIsGround() { return isGround; }

	//地面判定にする
	inline bool setIsGround() { isGround = true; unGrip = 0; return isGround; }
	
	//ターザンゲージの取得
	inline int getTarzanGage() { return TarzanGage; }

	//ターザンゲージをリセットさせる
	inline int resetTarzanGage() { TarzanGage = 0; return TarzanGage; }

	//ターザンゲージを回復する
	inline int RecoveryTarzanGage() { TarzanGage = TARZAN_GAGE; return TarzanGage; }

	//グリップフラグを戻す
	inline bool setIsGrip() { isGrip = false; return isGrip; }

	//距離を0にする
	inline bool setLength() { length = 0; return length; }

	//画像を動かす
	inline int MoveDrawX() { drawX += 32; return drawX; }

	//画像の位置を0に戻す
	inline int resetDrawX() { drawX = 0; return drawX; }

	//drawXの取得
	inline int getDrawX() { return drawX; }

	//ポジションリセット
	inline Vec2 resetPosition() { position = { 200.0f,500.0f }; return position; }

	//センターリセット
	inline Vec2 resetCenter() { center = { center.x = position.x + VINE_LENGTH ,center.y = position.y - 500 }; return center; }

	//プレイヤーの初期化
	inline void resetPlayer() {
		position = { 200.0f,500.0f };
		GripGage = 0;
		TarzanGage = TARZAN_GAGE;
		drawX = 0;
		isGrip = false;
		isGround = false;
		length = 0;
		state = IDLE;
		unGrip = 0;
		center.y = position.y - 500;
		center.x = position.x + VINE_LENGTH;
		velocity = { 0.0f,0.0f };
	}

	// すべての音を止める
	void stopAudio();

private:

	void Move();

	void Collision(Vec2& scroll);



	//座標
	Vec2 position;

	//速度
	Vec2 velocity;

	//中心座標
	Vec2 center;

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

	//距離
	float length;

	//画像
	int textureHandle;

	//画像描画の位置
	int drawX;

	// 画像をまとめたもの(実装出来れば配列にする)
	int textures[PLAYER_STATE_NUM];

	// どの画像を出すか(どの処理をするか)
	PLAYERSTATE state;

	// 丸太の画像
	int loghandle;



	// 音を鳴らすための変数
	// 0: 走る
	// 1: 着地
	// 2: ツタつかまり
	int soundHandles[3];
	int soundChecks[3];



};

