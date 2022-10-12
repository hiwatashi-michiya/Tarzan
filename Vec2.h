#pragma once

//struct Vec2
//{
// float x;
// float y;
//}

class Vec2 {

//アクセス範囲 : 外からいじれない
private:


//アクセス範囲 : 外からいじれる、見れる
public:

	float x;
	float y;

	//デフォルトコンストラクタ
	Vec2();

	//引数ありコンストラクタ(多重定義、オーバーロード)
	Vec2(float x, float y);

	Vec2 operator+(const Vec2& other);//Vec2 + Vec2
	Vec2 operator-(const Vec2& other);//Vec2 - Vec2

	const Vec2 operator+=(const Vec2& other);//Vec2 += Vec2
	const Vec2 operator-=(const Vec2& other);//Vec2 -= Vec2

	float length();
	float posX();
	float posY();

	Vec2 normarize();

};