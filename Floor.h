#pragma once

const int FLOOR_NUMBER = 10;

class Player;

//enum TYPE {
//	NORMAL,
//	PLAYERACCEL,
//	PLAYERDECEL
//};

class Floor
{
public:
	Floor();
	Floor(float x,float y,float length,float height,float scrW, float scrH, int textureHandle, Player& pPlayer);

	void Update(int scrollX);

	void Draw(int scrollX);

private:

	//当たり判定
	void Collision(int scrollX);

	//座標
	float x;
	float y;

	//長さ
	float length;

	//高さ(画像表示用)
	float height;

	//DrawQuad用
	float scrW;
	float scrH;

	int textureHandle;

	//プレイヤーのポインタ
	Player* pPlayer;

};



