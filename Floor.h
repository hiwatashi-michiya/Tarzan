#pragma once

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
	Floor(float x, float y, float length, float height, int type, float imgLength, float imgHeight,
		float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

private:

	//当たり判定
	void Collision(int scrollX);

	//座標
	float x;
	float y;

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

};



