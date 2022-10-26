#pragma once
#include "Vec2.h"

const int WALL_NUMBER = 50;

class Player;

enum WALLTYPE {
	BREAK,
	UNBREAK
};

class Wall
{

public:

	Wall();
	/// <summary>
	/// 壁のパラメーター
	/// </summary>
	/// <param name="position">{X座標, Y座標}</param>
	/// <param name="width">横幅</param>
	/// /// <param name="height">縦幅</param>
	/// <param name="hitSpeed">どこまでのスピードを耐えられるか</param>
	/// <param name="isAlive">壊れたかどうか</param>
	/// /// <param name="type">壁の種類</param>
	/// <param name="color">色</param>
	/// <param name="pPlayer">受け渡すポインタ(Playerクラス限定)</param>
	Wall(Vec2 position, float width, float height, float hitSpeed, bool isAlive, 
		int type, int color, Player& pPlayer, int textureHandle);

	void Update(Vec2 scroll);

	void Draw(Vec2 scroll);

	inline float getHitSpeedX() { return hitSpeed; }

	inline bool getIsHit() { return isHit; }

private:

	void Collision(Vec2 scroll);

	//壁の位置
	Vec2 position;

	//横幅
	float width;

	//縦幅
	float height;

	//耐久力(スピード許容量)
	float hitSpeed;

	//壊れているかどうか
	bool isAlive;

	//壁の種類
	int type;

	//色
	int color;

	Player* pPlayer;

	//画像
	int textureHandle;

	//当たったかどうか
	bool isHit;

	//描画範囲座標を動かす
	int drawTime = 0;
	int scrX = 0;
	
	//数字のリソース
	int NUM[10];

	//数字表示の処理関数
	int drawNumber;

	int divideNumber;

	int drawHitSpeed;

};



