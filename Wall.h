#pragma once
#include "Vec2.h"

const int WALL_NUMBER = 1;

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
	/// <param name="radius">横幅</param>
	/// <param name="hitSpeed">どこまでのスピードを耐えられるか</param>
	/// <param name="isAlive">壊れたかどうか</param>
	/// <param name="color">色</param>
	/// <param name="pPlayer">受け渡すポインタ(Playerクラス限定)</param>
	Wall(Vec2 position, float width, float height, float hitSpeed, bool isAlive, 
		int type, int color, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

	inline float getHitSpeedX() { return hitSpeed; }

private:

	void Collision(int scrollX);

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

};



