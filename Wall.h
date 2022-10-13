#pragma once
#include "Vec2.h"

class Player;

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
	Wall(Vec2 position, float radius, float hitSpeed, bool isAlive, int color, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

	inline float getHitSpeedX() { return hitSpeed; }

private:

	void Collision(int scrollX);

	//壁の位置
	Vec2 position;

	//大きさ
	float radius;

	//耐久力(スピード許容量)
	float hitSpeed;

	//壊れているかどうか
	bool isAlive;

	//色
	int color;

	Player* pPlayer;

};



