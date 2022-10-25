#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>


#pragma region パーティクルの情報・個数・待機時間

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
	Vector2 pos;
	int time;
};

//パーティクルの最大数を設定
const int emitterMax = 120;

//パーティクルを出すときの待機時間
int coolTime = 0;


//パーティクルの情報を設定する構造体
// <パーティクルが表示されているか(フラグ)>
// <X座標,Y座標>
// <X軸の大きさ,Y軸の大きさ>
// <角度>
// <色>
//を設定する
//何か追加要素があれば追加してもよい
typedef struct Effect {
	int isActive;
	Vector2 pos;
	Vector2 size;
	float angle;
	unsigned int color;
};

//エフェクト用の変数を初期化
Effect effect[emitterMax]{};

//落下エフェクトの表示時間の設定
int displayTimeA = 6;
int displayTimeB = 6;
int displayTimeC = 6;
int displayTimeD = 6;

//フェード用の色要素を保存する変数
unsigned int screenColor = 0x00000000;

//シェイク時の座標を保存する変数
Vector2 shakePos{
	0,
	0
};
int shakeTime = 0;

#pragma endregion

#pragma region 乱数と角度

//角度を設定
float theta = {};

//X座標とY座標の移動速度を角度によって変更する際の値を保存する変数
float moveX = {};
float moveY = {};

//乱数を保存する変数
float randamNum = 0;

#pragma endregion

#pragma region パーティクルの速度

//拡散型
//移動速度の基準を設定
float moveSpeedDiffusion = 1.5;
float moveSpeedDiffusionX[emitterMax] = {};
float moveSpeedDiffusionY[emitterMax] = {};

//低速度型
//移動速度の基準を設定
float moveSpeed = 1.5;
float moveSpeedX[emitterMax] = {};
float moveSpeedY[emitterMax] = {};

//速度線型
//移動速度の基準を設定
float moveSpeedLine = 1.5;
float moveSpeedLineX[emitterMax] = {};
float moveSpeedLineY[emitterMax] = {};

//落下型
//移動速度の基準を設定
float moveSpeedlanding = 1.5;
float moveSpeedlandingX[emitterMax] = {};
float moveSpeedlandingY[emitterMax] = {};

//衝突型(左右)
float moveSpeedClash = 1;
float moveSpeedClashX[emitterMax] = {};
float moveSpeedClashY[emitterMax] = {};

#pragma endregion



#pragma region フラグなど



#pragma endregion

#pragma region パーティクルの変数の初期化用関数

//拡散
Effect inisharaizuDiffusion() {

	return Effect{
		false,
		{0,0},
		{6,8},
		0.0f,
		0xFFFFFF77
	};

}

//速度
Effect inisharaizuSpeed() {

	return Effect{
		false,
		{0,0},
		{4,10},
		0.0f,
		0xFF000088
	};

}

//速度線
Effect inisharaizuSpeedLine() {

	return Effect{
		false,
		{0,0},
		{8,1},
		0.0f,
		0xFFFFFFAA
	};

}

//残像
Effect inisharaizuAfterImage() {

	return Effect{
		false,
		{0,0},
		{32,32},
		0.0f,
		0xFFFFFFFF
	};

}

//落下
Effect inisharaizuLanding() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0xFF00FFFF
	};

}

//左衝突
Effect inisharaizuLeftClash() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0xFF0000FF
	};

}

//右衝突
Effect inisharaizuRightClash() {

	return Effect{
		false,
		{0,0},
		{16,16},
		0.0f,
		0x0000FFFF
	};

}

#pragma endregion


#pragma region パーティクルの発生処理(落下と衝突は発生と移動処理が内包されている)

//拡散型パーティクル
void diffusionParticle(float posX, float posY, Effect effect[], int* displayTime) {

	int disNum = 0;

	//for文でパーティクルを管理
	//1つ表示するごとにfor文のループを抜ける
	for (int i = 0; i < emitterMax; i++) {

		//i番目のパーティクルが非表示であれば表示する
		if (effect[i].isActive == false) {

			//乱数に応じて移動する方向を変更する

			//座標
			effect[i].pos.x = posX;
			effect[i].pos.y = posY;

			randamNum = (rand() % 200) * 0.1;
			theta = (randamNum / 2.0) * M_PI;
			moveX = cosf(theta);
			moveY = sinf(theta);

			moveSpeedDiffusionX[i] = (moveX * moveSpeedDiffusion) / 2;
			moveSpeedDiffusionY[i] = (moveY * -moveSpeedDiffusion) / 2;

			//パーティクルを表示し続ける時間を設定
			displayTime[i] = 30;

			//パーティクルを表示させる
			effect[i].isActive = true;

			//for文のループを抜ける
			disNum++;

			if (disNum >= 3) {
				break;
			}

		}
	}
}

//速度パーティクル
void speedParticle(float posX, float posY, float vel, Effect effect[], int* displayTime) {

	int disNum = 0;

	//待機時間の減少を行う
	if (coolTime > 0) {

		coolTime--;

	}

	//パーティクルを出すときの待機時間が0の時に出現させる
	if (coolTime == 0) {

		//for文でパーティクルを管理
		//1つ表示するごとにfor文のループを抜ける
		for (int i = 0; i < emitterMax; i++) {

			//i番目のパーティクルが非表示であれば表示する
			if (effect[i].isActive == false) {

				//乱数に応じて移動する方向を変更する

				//座標
				effect[i].pos.x = posX;
				effect[i].pos.y = posY + (rand() % 12) - 6;

				if (vel > 0) {
					moveSpeedX[i] = -1;
					moveSpeedY[i] = 0;
				}
				else if (vel < 0) {
					moveSpeedX[i] = 1;
					moveSpeedY[i] = 0;
				}

				//パーティクルを表示し続ける時間を設定
				displayTime[i] = 6;

				//パーティクルを表示させる
				effect[i].isActive = true;

				//for文のループを抜ける
				disNum++;

				if (disNum >= 2) {
					break;
				}

			}

			//待機時間を設定
			coolTime = 0;

		}

	}
}

//加速線パーティクル
void speedLineParticle(float posX, float posY, float vel, Effect effect[], int* displayTime) {

	//待機時間の減少を行う
	if (coolTime > 0) {

		coolTime--;

	}

	//パーティクルを出すときの待機時間が0の時に出現させる
	if (coolTime == 0) {

		//for文でパーティクルを管理
		//1つ表示するごとにfor文のループを抜ける
		for (int i = 0; i < emitterMax; i += 3) {

			//i番目のパーティクルが非表示であれば表示する
			if (effect[i].isActive == false) {

				//乱数に応じて移動する方向を変更する

				//座標
				if (vel > 0) {
					effect[i].pos.x = posX + 32;
					effect[i + 1].pos.x = posX + 32;
					effect[i + 2].pos.x = posX + 32;
				}
				else if (vel < 0) {
					effect[i].pos.x = posX - 32;
					effect[i + 1].pos.x = posX - 32;
					effect[i + 2].pos.x = posX - 32;
				}

				effect[i].pos.y = posY + (rand() % 28) - 7;
				effect[i + 1].pos.y = posY + (rand() % 28) - 14;
				effect[i + 2].pos.y = posY + (rand() % 28) - 21;

				//移動量
				if (vel > 0) {
					moveSpeedLineX[i] = -8;
					moveSpeedLineY[i] = 0;
					moveSpeedLineX[i + 1] = -8;
					moveSpeedLineY[i + 1] = 0;
					moveSpeedLineX[i + 2] = -8;
					moveSpeedLineY[i + 2] = 0;
				}
				else if (vel < 0) {
					moveSpeedLineX[i] = 8;
					moveSpeedLineY[i] = 0;
					moveSpeedLineX[i + 1] = 8;
					moveSpeedLineY[i + 1] = 0;
					moveSpeedLineX[i + 2] = 8;
					moveSpeedLineY[i + 2] = 0;
				}

				//パーティクルを表示し続ける時間を設定
				displayTime[i] = 5.0f;
				displayTime[i + 1] = 5.0f;
				displayTime[i + 2] = 5.0f;

				//パーティクルを表示させる
				effect[i].isActive = true;
				effect[i + 1].isActive = true;
				effect[i + 2].isActive = true;

				//for文のループを抜ける
				break;
			}

			//待機時間を設定
			//coolTime = 0;

		}
	}
}

//残像
void afterImage(float posX, float posY, Effect effect[], int* displayTime) {


	//待機時間の減少を行う
	if (coolTime > 0) {

		coolTime--;

	}

	//パーティクルを出すときの待機時間が0の時に出現させる
	if (coolTime == 0) {

		//for文でパーティクルを管理
			//1つ表示するごとにfor文のループを抜ける
		for (int i = 0; i < emitterMax; i++) {

			//i番目のパーティクルが非表示であれば表示する
			if (effect[i].isActive == false) {

				//乱数に応じて移動する方向を変更する

				//座標
				effect[i].pos.x = posX;
				effect[i].pos.y = posY;

				//残像の透明度を変更
				effect[i].color = 0x555555FF;

				//パーティクルを表示し続ける時間を設定
				displayTime[i] = 30;

				//パーティクルを表示させる
				effect[i].isActive = true;

				//for文のループを抜ける
				break;
			}

			//待機時間を設定
			coolTime = 2;

		}
	}
}

//落下時
void landingParticle(float posX, float posY, Effect effect[]) {

	//表示処理
	//i番目のパーティクルが非表示であれば表示する
	if (effect[0].isActive == false) {

		//座標
		//0
		effect[0].pos.x = posX;
		effect[0].pos.y = posY + 12.0f;
		//1
		effect[1].pos.x = posX;
		effect[1].pos.y = posY + 12.0f;
		//2
		effect[2].pos.x = posX;
		effect[2].pos.y = posY + 12.0f;
		//3
		effect[3].pos.x = posX;
		effect[3].pos.y = posY + 12.0f;

		//移動量
		//0
		moveSpeedlandingX[0] = -4;
		moveSpeedlandingY[0] = -0.5;
		//1
		moveSpeedlandingX[1] = -3;
		moveSpeedlandingY[1] = -0.25;
		//2
		moveSpeedlandingX[2] = 3;
		moveSpeedlandingY[2] = -0.25;
		//3
		moveSpeedlandingX[3] = 4;
		moveSpeedlandingY[3] = -0.5;

		//パーティクルを表示し続ける時間を設定
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//パーティクルを表示させる
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//移動処理
	//i番目のパーティクルが表示されている場合、移動する
	if (effect[3].isActive == true) {

		//パーティクルの表示時間を減少させる
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//パーティクルを上方向に一定速度で移動させる
		//パーティクルごとにx軸の移動も行う
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//パーティクルの出現後、時間経過で消滅させる
		if (displayTimeD <= 0.0f) {

			//パーティクルを非表示にする
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

//左方向移動時の衝突
void leftClashParticle(float posX, float posY, Effect effect[]) {

	//表示処理
	//i番目のパーティクルが非表示であれば表示する
	if (effect[0].isActive == false) {

		//座標
		//0
		effect[0].pos.x = posX - 12.0f;
		effect[0].pos.y = posY;
		//1
		effect[1].pos.x = posX - 12.0f;
		effect[1].pos.y = posY;
		//2
		effect[2].pos.x = posX - 12.0f;
		effect[2].pos.y = posY;
		//3
		effect[3].pos.x = posX - 12.0f;
		effect[3].pos.y = posY;

		//移動量
		//0
		moveSpeedlandingX[0] = 1;
		moveSpeedlandingY[0] = -4;
		//1
		moveSpeedlandingX[1] = 1.5;
		moveSpeedlandingY[1] = -3;
		//2
		moveSpeedlandingX[2] = 1.5;
		moveSpeedlandingY[2] = 3;
		//3
		moveSpeedlandingX[3] = 2;
		moveSpeedlandingY[3] = 4;

		//パーティクルを表示し続ける時間を設定
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//パーティクルを表示させる
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//移動処理
	//i番目のパーティクルが表示されている場合、移動する
	if (effect[3].isActive == true) {

		//パーティクルの表示時間を減少させる
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//パーティクルを上方向に一定速度で移動させる
		//パーティクルごとにx軸の移動も行う
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//パーティクルの出現後、時間経過で消滅させる
		if (displayTimeD <= 0.0f) {

			//パーティクルを非表示にする
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

//右方向移動時の衝突
void rightClashParticle(float posX, float posY, Effect effect[]) {

	//表示処理
	//i番目のパーティクルが非表示であれば表示する
	if (effect[0].isActive == false) {

		//座標
		//0
		effect[0].pos.x = posX + 12.0f;
		effect[0].pos.y = posY;
		//1
		effect[1].pos.x = posX + 12.0f;
		effect[1].pos.y = posY;
		//2
		effect[2].pos.x = posX + 12.0f;
		effect[2].pos.y = posY;
		//3
		effect[3].pos.x = posX + 12.0f;
		effect[3].pos.y = posY;

		//移動量
		//0
		moveSpeedlandingX[0] = -0.5;
		moveSpeedlandingY[0] = -4;
		//1
		moveSpeedlandingX[1] = -0.25;
		moveSpeedlandingY[1] = -3;
		//2
		moveSpeedlandingX[2] = -0.25;
		moveSpeedlandingY[2] = 3;
		//3
		moveSpeedlandingX[3] = -0.5;
		moveSpeedlandingY[3] = 4;

		//パーティクルを表示し続ける時間を設定
		displayTimeA = 10;
		displayTimeB = 10;
		displayTimeC = 10;
		displayTimeD = 10;


		//パーティクルを表示させる
		effect[0].isActive = true;
		effect[1].isActive = true;
		effect[2].isActive = true;
		effect[3].isActive = true;

	}


	//移動処理
	//i番目のパーティクルが表示されている場合、移動する
	if (effect[3].isActive == true) {

		//パーティクルの表示時間を減少させる
		displayTimeA--;
		displayTimeB--;
		displayTimeC--;
		displayTimeD--;

		//パーティクルを上方向に一定速度で移動させる
		//パーティクルごとにx軸の移動も行う
		//0
		effect[0].pos.x += moveSpeedlandingX[0];
		effect[0].pos.y += moveSpeedlandingY[0];
		//1
		effect[1].pos.x += moveSpeedlandingX[1];
		effect[1].pos.y += moveSpeedlandingY[1];
		//2
		effect[2].pos.x += moveSpeedlandingX[2];
		effect[2].pos.y += moveSpeedlandingY[2];
		//3
		effect[3].pos.x += moveSpeedlandingX[3];
		effect[3].pos.y += moveSpeedlandingY[3];

		//パーティクルの出現後、時間経過で消滅させる
		if (displayTimeD <= 0.0f) {

			//パーティクルを非表示にする
			effect[0].isActive = false;
			effect[1].isActive = false;
			effect[2].isActive = false;
			effect[3].isActive = false;

		}

	}
}

#pragma endregion


#pragma region パーティクルの移動と消滅処理

//拡散型パーティクル
void diffusionParticleMove(Effect effect[], int* displayTime) {

	//for文で複数管理
	for (int i = 0; i < emitterMax; i++) {
		//i番目のパーティクルが表示されている場合、移動する
		if (effect[i].isActive == true) {

			//パーティクルの表示時間を減少させる
			displayTime[i]--;

			//パーティクルを一定速度で移動させる
			effect[i].pos.x += moveSpeedDiffusionX[i];
			effect[i].pos.y += moveSpeedDiffusionY[i];


			//パーティクルの出現後、時間経過で消滅させる
			if (displayTime[i] <= 0.0f) {

				//パーティクルを非表示にする
				effect[i].isActive = false;

			}
		}
	}
}

//速度パーティクル
void speedParticleMove(Effect effect[], int* displayTime) {

	//for文で複数管理
	for (int i = 0; i < emitterMax; i++) {
		//i番目のパーティクルが表示されている場合、移動する
		if (effect[i].isActive == true) {

			//パーティクルの表示時間を減少させる
			displayTime[i]--;

			//パーティクルを上方向に一定速度で移動させる
			//パーティクルごとにx軸の移動も行う
			effect[i].pos.x += moveSpeedX[i];
			effect[i].pos.y += moveSpeedY[i];


			//パーティクルの出現後、時間経過で消滅させる
			if (displayTime[i] <= 0.0f) {

				//パーティクルを非表示にする
				effect[i].isActive = false;

			}
		}
	}
}

//加速線パーティクル
void speedLineParticleMove(Effect effect[], int* displayTime) {

	//for文で複数管理
	for (int i = 0; i < emitterMax; i++) {

		//i番目のパーティクルが表示されている場合、移動する
		if (effect[i].isActive == true) {

			//パーティクルの表示時間を減少させる
			displayTime[i]--;

			//パーティクルを上方向に一定速度で移動させる
			//パーティクルごとにx軸の移動も行う
			effect[i].pos.x += moveSpeedLineX[i];
			effect[i].pos.y += moveSpeedLineY[i];


			//パーティクルの出現後、時間経過で消滅させる
			if (displayTime[i] <= 0.0f) {

				//パーティクルを非表示にする
				effect[i].isActive = false;

			}
		}

	}
}

//残像
void afterImageMove(float posX, float posY, Effect effect[], int* displayTime) {

	//for文で複数管理
	for (int i = 0; i < emitterMax; i++) {
		//i番目のパーティクルが表示されている場合、移動する
		if (effect[i].isActive == true) {

			//パーティクルの表示時間を減少させる
			displayTime[i]--;

			//残像の透明度を変更
			effect[i].color -= 0x11;

			//パーティクルの出現後、透明になったら消滅させる
			if (effect[i].color <= 0x55555500) {

				//パーティクルを非表示にする
				effect[i].isActive = false;

			}
		}

	}
}

#pragma endregion


#pragma region 画面系統

//画面のフェードアウト
void screenFadeOut() {


	if (screenColor > 0x00000000) {

		screenColor -= 0x11;
	}

}

//画面フェードイン
void screenFadeIn() {

	if (screenColor < 0x000000FF) {

		screenColor += 0x11;
	}
}

//フェードの描画処理
void screenFadeDraw() {

	Novice::DrawBox(
		0, 0,
		1280, 720,
		0.0f,
		screenColor,
		kFillModeSolid
	);

}

//オブジェクトのフェードアウト
void objFadeOut(unsigned int color, int fadeSpeed) {

	//透明になるまで透明度をあげる
	switch (fadeSpeed) {

	case 1:

		if (color != 0xFFFFFF00) {

			color -= 0x05;

		}

		break;

	case 2:

		if (color != 0xFFFFFF00) {

			color -= 0x0A;

		}

		break;

	case 3:

		if (color != 0xFFFFFF00) {

			color -= 0x11;

		}

		break;

	case 4:

		if (color != 0xFFFFFF00) {

			color -= 0x22;

		}

		break;

	case 5:

		if (color != 0xFFFFFF00) {

			color -= 0x33;

		}

		break;
	}

}

//シェイク
ShakeList shake(ShakeList list) {

	if (list.time > 0) {

		list.time--;

		if (list.time > 30) {
			return ShakeList{
				rand() % 80 - 40.0f,
				rand() % 80 - 40.0f,
				list.time -1,
			};
		}

		if (list.time > 25) {
			return ShakeList{
				rand() % 60 - 40.0f,
				rand() % 60 - 40.0f,
				list.time - 1,
			};
		}

		if (list.time > 20) {
			return ShakeList{
				rand() % 50 - 20.0f,
				rand() % 50 - 20.0f,
				list.time - 1,
			};
		}

		else if (list.time > 15) {
			return ShakeList{
			rand() % 40 - 10.0f,
			rand() % 40 - 10.0f,
			list.time - 1,
			};
		}

		if (list.time > 10) {
			return ShakeList{
				rand() % 20 - 10.0f,
				rand() % 20 - 10.0f,
				list.time - 1,
			};
		}

		else if (list.time > 5) {
			return ShakeList{
			rand() % 10 - 4.0f,
			rand() % 10 - 4.0f,
			list.time -1,
			};
		}

		else if (list.time > 0) {
			return ShakeList{
			rand() % 5 - 2.0f,
			rand() % 5 - 2.0f,
			list.time - 1,
			};
		}

		if (list.time == 0) {
			return ShakeList{
			0.0f,
			0.0f,
			0,
			};
		}
	}
}


#pragma endregion