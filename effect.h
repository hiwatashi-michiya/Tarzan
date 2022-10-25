#pragma once

#include <Novice.h>
#include <math.h>
#include<time.h>
#include "Vec2.h"

//**ベクトルの構造体**//
typedef struct Vector2 {
	float x;
	float y;
};

typedef struct Vector2x2 {
	Vector2 Top;
	Vector2 Bottom;
};

typedef struct ShakeList {
	Vec2 pos;
	int time;
};

//**パーティクルの構造体**//

//パーティクルの最大数を設定
const int emitterMax = 120;

//エフェクト発生地点の設定
// <パーティクルを発生させる状態であるか(フラグ)>
// <X座標,Y座標>
//を設定する
//何か追加要素があれば追加してもよい
typedef struct EffectPoint {
	int isActive;
	Vector2 pos;
	Vector2 vel;
	float acc;
};

//パーティクルの情報を設定する構造体
// <パーティクルが表示されているか(フラグ)>
// <X座標,Y座標>
// <X軸の大きさ,Y軸の大きさ>
// <角度>
// <色>
// <画像>
// <左向きの角座標>
// <右向きの角座標>
//を設定する
//何か追加要素があれば追加してもよい
typedef struct Effect {
	int isActive;
	Vector2 pos;
	Vector2 size;
	float angle;
	unsigned int color;
	int imagesPos;
	Vector2x2 left;
	Vector2x2 right;
};

#pragma region パーティクルの変数の初期化用関数

//拡散
Effect inisharaizuDiffusion();

//速度
Effect inisharaizuSpeed();

//速度線
Effect inisharaizuSpeedLine();

//残像
Effect inisharaizuAfterImage();

//落下
Effect inisharaizuLanding();

//左衝突
Effect inisharaizuLeftClash();

//右衝突
Effect inisharaizuRightClash();

#pragma endregion


#pragma region パーティクルの発生処理(落下時は発生と移動処理が内包されている)

//拡散パーティクル
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void diffusionParticle(float posX, float posY, Effect effect[], int* displayTime);


//速度パーティクル(遅い)
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <パーティクルを発生させる中心点の移動速度> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void speedParticle(float posX, float posY, float vel, Effect effect[], int* displayTime);


//加速線パーティクル
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <パーティクルを発生させる中心点の移動速度> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void speedLineParticle(float posX, float posY, float vel, Effect effect[], int* displayTime);


//残像
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void afterImage(float posX, float posY, Effect effect[], int* displayTime);


//落下時
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void landingParticle(float posX, float posY, Effect effect[]);

//左方向移動時の衝突
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void leftClashParticle(float posX, float posY, Effect effect[]);

//右方向移動時の衝突
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void rightClashParticle(float posX, float posY, Effect effect[]);

#pragma endregion

#pragma region パーティクルの移動と消滅処理


//拡散パーティクル
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void diffusionParticleMove(Effect effect[], int* displayTime);


//速度パーティクル(遅い)
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <パーティクルを発生させる中心点の移動速度> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void speedParticleMove(Effect effect[], int* displayTime);


//加速線パーティクル
// <パーティクルを発生させる中心点のX座標> 
// <パーティクルを発生させる中心点ののY座標> 
// <パーティクルを発生させる中心点の移動速度> 
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void speedLineParticleMove(Effect effect[], int* displayTime);


//残像
// <出現させたいパーティクルの変数名> 
// <パーティクルを表示し続けるフレーム数> 
//を入力すること
//出現・消滅・移動処理をすべて行う
void afterImageMove(float posX, float posY, Effect effect[], int* displayTime);

#pragma endregion

#pragma region 画面系統

//画面フェードアウト
//入力する変数はなし
void screenFadeOut();

//画面フェードイン
//入力する変数はなし
void screenFadeIn();

//フェードの描画処理
//入力する変数はなし
//描画処理に配置すること
void screenFadeDraw();

//オブジェクトのフェードアウト
// <オブジェクトの色>
// <オブジェクトの消滅速度(1(遅い)~5(速い)段階で設定)>
//を入力すること
void objFadeOut(unsigned int color, int fadeSpeed);

//シェイク
// <シェイク用の構造体>
// <プレイヤーの速度>
//を入力すること
//シェイクさせたいときはシェイクする時間を入力すること
//時間及びフラグはmain.cppでオフまたは更新すること
ShakeList shake(ShakeList list, float velX);

#pragma endregion

