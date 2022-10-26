#pragma once
#include "Vec2.h"

const int FLOOR_NUMBER = 50;

class Player;

enum FLOORTYPE {
	NORMAL,
	PLAYERACCEL,
	PLAYERDECEL,
	CEILING
};

class Floor
{
public:
	Floor();
	Floor(float posX, float posY, float length, float height, int type, float imgLength, float imgHeight,
		float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(Vec2 scroll);

	void Draw(Vec2 scroll);

private:

	//当たり判定
	void Collision(Vec2 scroll);

	//座標
	float posX;
	float posY;

	//判定長さ
	float length;

	//判定高さ
	float height;

	int type;

	//画像長さ
	float imgLength;

	//画像高さ
	float imgHeight;

	//DrawQuad用
	float scrW;
	float scrH;

	int textureHandle;

	//プレイヤーのポインタ
	Player* pPlayer;

	//描画範囲座標を動かす
	int drawTime = 0;
	int scrX = 0;

};



