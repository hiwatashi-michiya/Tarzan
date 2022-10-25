﻿#include <Novice.h>
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"
#include "Floor.h"
#include "Stage.h"
#include "Calc.h"
#include "effect.h"

const char kWindowTitle[] = "Wild Tarzan";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// スクロール値
	Vec2 scroll = { 0,0 };

	//ステージ選択の変数
	int stageSelect = 2;

	//X軸の画像表示の繰り返し回数
	const int REPETITION_X = 32;

	//Y軸の画像表示の繰り返し回数
	const int REPETITION_Y = 4;

	//ロード用の変数
	int isLoading = 0;

	//スピード表示用の変数
	int drawSpeed = 0;

	int drawNumber = 0;

	int divideNumber = 1;

#pragma region BG

	//タイトル画像
	int BGTITLE = Novice::LoadTexture("./Resources/Images/BG/TarzanBG.png");

	//セレクト画像
	int BGSELECT = Novice::LoadTexture("./Resources/Images/BG/TarzanBG_SELECT.png");

	//ゲームプレイ背景
	int INGAMEBG = Novice::LoadTexture("./Resources/Images/BG/ingameBG1.png");

	//シーンチェンジ画像
	int SCENECHANGE = Novice::LoadTexture("./Resources/Images/BG/scenechange.png");
	
	// シーンチェンジ音
	int SCENECHANGESOUND = Novice::LoadAudio("./Resources/SE/sceneChange.wav");
	int SCENECHANGESOUNDCHECK = -1;

	// カーソル移動音
	int SELECTSOUND = Novice::LoadAudio("./Resources/SE/select.wav");
	int SELECTSOUNDCHECK[8];
	for (int i = 0; i < 8; i++)
	{
		SELECTSOUNDCHECK[i] = -1;
	}

	// ステージ決定音
	int DECISIONSOUND = Novice::LoadAudio("./Resources/SE/decision.wav");
	int DECISIONSOUNDCHECK = -1;

#pragma endregion

#pragma region Object

	int ACCELFLOOR = Novice::LoadTexture("./Resources/Images/Object/accel.png");
	int DECELFLOOR = Novice::LoadTexture("./Resources/Images/Object/decel.png");
	int UNBREAKWALL = Novice::LoadTexture("./Resources/Images/Object/wall.png");
	int BREAKWALL = Novice::LoadTexture("./Resources/Images/Object/wallbreak.png");
	int GROUND = Novice::LoadTexture("./Resources/Images/Object/ground.png");
	int NORMALFLOOR = Novice::LoadTexture("./Resources/Images/Object/normalfloor.png");
	int CEILINGFLOOR = Novice::LoadTexture("./Resources/Images/Object/ceiling.png");
	int STAGECEILING = Novice::LoadTexture("./Resources/Images/Object/stageceiling.png");

#pragma endregion

#pragma region Player

	int PLAYERIDLE = Novice::LoadTexture("./Resources/Images/Player/playerIdle.png");
	int PLAYERRUN = Novice::LoadTexture("./Resources/Images/Player/playerRun.png");
	int PLAYERTARZAN = Novice::LoadTexture("./Resources/Images/Player/playerTarzan.png");
	int PLAYERSKY = Novice::LoadTexture("./Resources/Images/Player/playerSky.png");

#pragma endregion

#pragma region UI

#pragma region WOOD

	int SELECTWOOD = Novice::LoadTexture("./Resources/Images/UI/stageselect.png");

	int WOOD[STAGE_NUMBER];

	//特に使わない
	WOOD[0] = 0;
	//
	WOOD[1] = Novice::LoadTexture("./Resources/Images/UI/stage1.png");
	WOOD[2] = Novice::LoadTexture("./Resources/Images/UI/stage2.png");
	WOOD[3] = Novice::LoadTexture("./Resources/Images/UI/stage3.png");
	WOOD[4] = Novice::LoadTexture("./Resources/Images/UI/stage4.png");
	WOOD[5] = Novice::LoadTexture("./Resources/Images/UI/stage5.png");
	int BRIGHTWOOD[STAGE_NUMBER];
	//特に使わない
	BRIGHTWOOD[0] = 0;
	//
	BRIGHTWOOD[1] = Novice::LoadTexture("./Resources/Images/UI/stage1select.png");
	BRIGHTWOOD[2] = Novice::LoadTexture("./Resources/Images/UI/stage2select.png");
	BRIGHTWOOD[3] = Novice::LoadTexture("./Resources/Images/UI/stage3select.png");
	BRIGHTWOOD[4] = Novice::LoadTexture("./Resources/Images/UI/stage4select.png");
	BRIGHTWOOD[5] = Novice::LoadTexture("./Resources/Images/UI/stage5select.png");

#pragma endregion

#pragma region NUM

	//数字
	int NUM[10];
	NUM[0] = Novice::LoadTexture("./Resources/Images/UI/0.png");
	NUM[1] = Novice::LoadTexture("./Resources/Images/UI/1.png");
	NUM[2] = Novice::LoadTexture("./Resources/Images/UI/2.png");
	NUM[3] = Novice::LoadTexture("./Resources/Images/UI/3.png");
	NUM[4] = Novice::LoadTexture("./Resources/Images/UI/4.png");
	NUM[5] = Novice::LoadTexture("./Resources/Images/UI/5.png");
	NUM[6] = Novice::LoadTexture("./Resources/Images/UI/6.png");
	NUM[7] = Novice::LoadTexture("./Resources/Images/UI/7.png");
	NUM[8] = Novice::LoadTexture("./Resources/Images/UI/8.png");
	NUM[9] = Novice::LoadTexture("./Resources/Images/UI/9.png");

	int REDNUM[10];
	REDNUM[0] = Novice::LoadTexture("./Resources/Images/UI/0_red.png");
	REDNUM[1] = Novice::LoadTexture("./Resources/Images/UI/1_red.png");
	REDNUM[2] = Novice::LoadTexture("./Resources/Images/UI/2_red.png");
	REDNUM[3] = Novice::LoadTexture("./Resources/Images/UI/3_red.png");
	REDNUM[4] = Novice::LoadTexture("./Resources/Images/UI/4_red.png");
	REDNUM[5] = Novice::LoadTexture("./Resources/Images/UI/5_red.png");
	REDNUM[6] = Novice::LoadTexture("./Resources/Images/UI/6_red.png");
	REDNUM[7] = Novice::LoadTexture("./Resources/Images/UI/7_red.png");
	REDNUM[8] = Novice::LoadTexture("./Resources/Images/UI/8_red.png");
	REDNUM[9] = Novice::LoadTexture("./Resources/Images/UI/9_red.png");

	//ドット
	int DOT = Novice::LoadTexture("./Resources/Images/UI/dot.png");
	int REDDOT = Novice::LoadTexture("./Resources/Images/UI/dot_red.png");


#pragma endregion

	//ターザンゲージ
	int GAGE = Novice::LoadTexture("./Resources/Images/UI/gage.png");
	int BACKGAGE = Novice::LoadTexture("./Resources/Images/UI/backgage.png");

	//スピードテキスト
	int SPEED = Novice::LoadTexture("./Resources/Images/UI/speed.png");
	int MAXSPEED = Novice::LoadTexture("./Resources/Images/UI/maxspeed.png");

	//UI表示を見やすくする画像
	int UI = Novice::LoadTexture("./Resources/Images/UI/UIsheet.png");

	//チュートリアル用のUI
	int PRESSINFO = Novice::LoadTexture("./Resources/Images/UI/press.png");
	int BREAKINFO = Novice::LoadTexture("./Resources/Images/UI/break.png");
	int SLOWINFO = Novice::LoadTexture("./Resources/Images/UI/slow.png");
	int FASTINFO = Novice::LoadTexture("./Resources/Images/UI/fast.png");

#pragma endregion

	//画像を動かすタイマー
	int drawTimer = 0;

	//シーンチェンジ時の画像を動かす変数
	int sceneX = 0;

	//シーン切り替えにかかる時間
	const int SCENE_TIMER = 30;

	//最大速度の保存
	float maxSpeed = 0.0f;

	int drawMaxSpeed = 0;

#pragma region パーティクルの変数の宣言・定義

	//拡散
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect diffusionBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		diffusionBox[i] = inisharaizuDiffusion();

	};

	//速度
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect SpeedBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		SpeedBox[i] = inisharaizuSpeed();

	};

	//加速線
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect SpeedLineBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		SpeedLineBox[i] = inisharaizuSpeedLine();

	};

	//残像
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect afterImageBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		afterImageBox[i] = inisharaizuAfterImage();

	};

	//落下
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect landingBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		landingBox[i] = inisharaizuLanding();

	};

	//左衝突
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect	leftClashBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		leftClashBox[i] = inisharaizuLeftClash();

	};

	//右衝突
	//for文を用いてパーティクル一つ一つの変数を初期化
	Effect rightClashBox[emitterMax]{};
	for (int i = 0; i < emitterMax; i++) {

		rightClashBox[i] = inisharaizuRightClash();

	};

	ShakeList shakes{};

	int displayTimeAfter[emitterMax]{};
	int displayTimeDiffusion[emitterMax]{};
	int displayTimeLine[emitterMax]{};


	bool isPlayerLanding = false;
	bool isShake = false;


#pragma endregion

	/*Player player({ posX, posY }, { velocityX, 0.0f }, { 100.0f + 250.0f, 200.0f },
		0xFFFFFFFF, false, TARZAN_GAGE, 0, 0, false, 0, TARZAN, 0);*/

	int PLAYERIMAGES[PLAYER_STATE_NUM] = {
		PLAYERIDLE,PLAYERRUN,PLAYERTARZAN,0,PLAYERSKY
	};

	Vec2 pos = { 200.0f,500.0f };
	Player player(pos, PLAYERIMAGES);

	//壁の生成

	Wall wall[STAGE_NUMBER][WALL_NUMBER];
	for (int a = 0; a < STAGE_NUMBER; a++) {

		for (int b = 0; b < WALL_NUMBER; b++) {
			wall[a][b] = Wall({ -10000.0f,-10000.0f }, 0.0f, 0.0f, 100.0f, false, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
		}

	}

#pragma region stage1
	//ステージ1
	wall[1][0] = Wall({ 100.0f,690.0f }, 51200, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, GROUND);
	wall[1][1] = Wall({ 4000.0f,590.0f }, 256, 256, 20.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][2] = Wall({ 5000.0f,-344.0f }, 256, 1024, 15.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[1][3] = Wall({ 9000.0f,-344.0f }, 256, 1024, 20.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[1][4] = Wall({ 12000.0f,-344.0f }, 256, 1024, 25.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[1][5] = Wall({ 14000.0f,-344.0f }, 256, 704, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][6] = Wall({ 17000.0f,424.0f }, 512, 256, 35.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[1][7] = Wall({ 20000.0f,-344.0f }, 256, 824, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][8] = Wall({ 23000.0f,-344.0f }, 256, 1024, 30.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[1][9] = Wall({ -100.0f,-344.0f }, 256, 1124, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][10] = Wall({ 500.0f,600.0f }, 256, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][11] = Wall({ 2000.0f,550.0f }, 256, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	//
#pragma endregion
#pragma region stage2
	//ステージ2
	wall[2][0] = Wall({ 100.0f,690.0f }, 50000, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, GROUND);
	wall[2][1] = Wall({ -100.0f,-1000.0f }, 256, 2000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][2] = Wall({ 10000.0f,390.0f }, 500, 90, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][3] = Wall({ 13000.0f,510.0f }, 1000, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][4] = Wall({ 15000.0f,510.0f }, 1000, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][5] = Wall({ 600.0f,590.0f }, 300, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][6] = Wall({ 11000.0f,-90.0f }, 4000, 80, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][7] = Wall({ 6000.0f,0.0f }, 2500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][8] = Wall({ 2250.0f,590.0f }, 500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[2][9] = Wall({ 7000.0f,200.0f }, 300, 480, 25.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[2][10] = Wall({ 7000.0f,-1000.0f }, 300, 990, 30.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[2][11] = Wall({ 11000.0f,0.0f }, 300, 680, 30.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[2][12] = Wall({ 14000.0f,-1000.0f }, 300, 900, 40.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[2][13] = Wall({ 19000.0f,-1000.0f }, 300, 1680, 35.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	//
#pragma endregion
#pragma region stage3
	//ステージ3
	wall[3][0] = Wall({ 100.0f,690.0f }, 50000, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, GROUND);
	wall[3][1] = Wall({ -100.0f,-400.0f }, 256, 2000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][2] = Wall({ 6250.0f,310.0f }, 500, 1000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][3] = Wall({ 14250.0f,110.0f }, 500, 1000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][4] = Wall({ 156.0f,610.0f }, 944, 200, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][5] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][6] = Wall({ 4200.0f,-2000.0f }, 1500, 1700, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][7] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][8] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][9] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][10] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][11] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	//
#pragma endregion
#pragma region stage4
	//ステージ4
	wall[4][0] = Wall({ 100.0f,690.0f }, 50000, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, GROUND);
	wall[4][1] = Wall({ -100.0f,-400.0f }, 256, 2000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	//
#pragma endregion
#pragma region stage5
	//ステージ5
	wall[5][0] = Wall({ 100.0f,690.0f }, 50000, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, GROUND);
	wall[5][1] = Wall({ -100.0f,-400.0f }, 256, 2000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	//
#pragma endregion

	//初期化用
	Wall RESET_WALL[STAGE_NUMBER][WALL_NUMBER];

	for (int a = 0; a < STAGE_NUMBER; a++) {

		for (int b = 0; b < WALL_NUMBER; b++) {
			RESET_WALL[a][b] = wall[a][b];
		}

	}

	//床、天井の生成

	Floor floor[STAGE_NUMBER][FLOOR_NUMBER];

	//初期化
	for (int a = 0; a < STAGE_NUMBER; a++) {
		for (int b = 0; b < FLOOR_NUMBER; b++) {
			floor[a][b] = Floor(-10000, -10000, 0, 0, NORMAL, 0, 0, 64, 64, NORMALFLOOR, player);
		}
	}

#pragma region stage1

	//ステージ1
	floor[1][0] = Floor(100, 680, 28000, 10, NORMAL, 28000, 10, 64, 64, NORMALFLOOR, player);
	floor[1][1] = Floor(4000, 580, 256, 10, NORMAL, 256, 10, 64, 64, NORMALFLOOR, player);
	floor[1][2] = Floor(6000, 480, 4000, 10, NORMAL, 4000, 10, 64, 64, NORMALFLOOR, player);
	floor[1][3] = Floor(7000, 230, 2000, 10, PLAYERACCEL, 2000, 10, 64, 64, ACCELFLOOR, player);
	floor[1][4] = Floor(14000, 360, 256, 10, CEILING, 256, 10, 64, 64, CEILINGFLOOR, player);
	floor[1][5] = Floor(20500, 380, 4700, 10, PLAYERACCEL, 4700, 10, 64, 64, ACCELFLOOR, player);
	floor[1][6] = Floor(17000, 404, 512, 20, NORMAL, 512, 20, 64, 64, NORMALFLOOR, player);
	floor[1][7] = Floor(6000, 680, 3000, 10, PLAYERDECEL, 3000, 10, 64, 64, DECELFLOOR, player);
	floor[1][8] = Floor(15000, 300, 1400, 10, NORMAL, 1400, 10, 64, 64, NORMALFLOOR, player);
	floor[1][9] = Floor(20000, 480, 256, 10, CEILING, 256, 10, 64, 64, CEILINGFLOOR, player);
	floor[1][10] = Floor(0, -1440, 28000, 1096, CEILING, 28000, 1096, 64, 64, STAGECEILING, player);
	floor[1][11] = Floor(500, 590, 256, 10, NORMAL, 256, 10, 64, 64, NORMALFLOOR, player);
	floor[1][12] = Floor(2000, 540, 256, 10, NORMAL, 256, 10, 64, 64, NORMALFLOOR, player);
	//

#pragma endregion
#pragma region stage2

	//ステージ2
	floor[2][0] = Floor(100, 680, 50000, 10, NORMAL, 50000, 10, 64, 64, NORMALFLOOR, player);
	floor[2][1] = Floor(0, -2000, 50000, 1000, CEILING, 50000, 1000, 64, 64, STAGECEILING, player);
	floor[2][2] = Floor(600, 580, 300, 10, NORMAL, 300, 10, 64, 64, NORMALFLOOR, player);
	floor[2][3] = Floor(1200, 450, 300, 10, NORMAL, 300, 10, 64, 64, NORMALFLOOR, player);
	floor[2][4] = Floor(2250, 580, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[2][5] = Floor(4000, 550, 600, 10, NORMAL, 600, 10, 64, 64, NORMALFLOOR, player);
	floor[2][6] = Floor(5100, 550, 2900, 10, NORMAL, 2900, 10, 64, 64, NORMALFLOOR, player);
	floor[2][7] = Floor(1200, 460, 300, 10, CEILING, 300, 10, 64, 64, CEILINGFLOOR, player);
	floor[2][8] = Floor(2000, 360, 1000, 10, PLAYERACCEL, 1000, 10, 64, 64, ACCELFLOOR, player);
	floor[2][9] = Floor(2000, 370, 1000, 10, CEILING, 1000, 10, 64, 64, CEILINGFLOOR, player);
	floor[2][10] = Floor(6000, -10, 2500, 10, PLAYERACCEL, 2500, 10, 64, 64, ACCELFLOOR, player);
	floor[2][11] = Floor(6000, 190, 2500, 10, CEILING, 2500, 10, 64, 64, CEILINGFLOOR, player);
	floor[2][12] = Floor(3500, 130, 1000, 10, PLAYERACCEL, 1000, 10, 64, 64, ACCELFLOOR, player);
	floor[2][13] = Floor(5000, 50, 500, 10, PLAYERACCEL, 500, 10, 64, 64, ACCELFLOOR, player);
	floor[2][14] = Floor(5500, 190, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[2][15] = Floor(10000, 380, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[2][16] = Floor(10500, 480, 1500, 10, NORMAL, 1500, 10, 64, 64, NORMALFLOOR, player);
	floor[2][17] = Floor(13000, 500, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[2][18] = Floor(15000, 500, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[2][19] = Floor(4000, 680, 600, 10, PLAYERDECEL, 600, 10, 64, 64, DECELFLOOR, player);
	floor[2][20] = Floor(14000, 680, 1000, 10, PLAYERDECEL, 1000, 10, 64, 64, DECELFLOOR, player);
	floor[2][21] = Floor(17000, 400, 1000, 10, PLAYERACCEL, 1000, 10, 64, 64, ACCELFLOOR, player);
	floor[2][22] = Floor(18000, 450, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[2][23] = Floor(18000, 680, 1000, 10, PLAYERDECEL, 1000, 10, 64, 64, DECELFLOOR, player);
	floor[2][24] = Floor(10000, 480, 500, 10, CEILING, 500, 10, 64, 64, CEILINGFLOOR, player);
	floor[2][25] = Floor(11000, -100, 4000, 10, PLAYERACCEL, 4000, 10, 64, 64, ACCELFLOOR, player);
	floor[2][26] = Floor(11000, -10, 4000, 10, CEILING, 4000, 10, 64, 64, CEILINGFLOOR, player);
	floor[2][27] = Floor(9000, -50, 1500, 10, PLAYERACCEL, 1500, 10, 64, 64, ACCELFLOOR, player);
	//

#pragma endregion
#pragma region stage3

	//ステージ3
	floor[3][0] = Floor(100, 680, 50000, 10, NORMAL, 50000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][1] = Floor(0, -3000, 50000, 1000, CEILING, 50000, 1000, 64, 64, STAGECEILING, player);
	floor[3][2] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][3] = Floor(100, 200, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][4] = Floor(100, -300, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][5] = Floor(1700, 500, 1500, 10, NORMAL, 1500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][6] = Floor(6000, 300, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][7] = Floor(7000, 500, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][8] = Floor(8000, 300, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][9] = Floor(14000, 100, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][10] = Floor(17000, 200, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][11] = Floor(18000, 400, 2000, 10, PLAYERDECEL, 2000, 10, 64, 64, DECELFLOOR, player);
	floor[3][12] = Floor(1700, 190, 1500, 10, CEILING, 1500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][13] = Floor(1700, -10, 1500, 10, PLAYERACCEL, 1500, 10, 64, 64, ACCELFLOOR, player);
	floor[3][14] = Floor(1700, -300, 2500, 10, NORMAL, 2500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][15] = Floor(4200, -300, 500, 10, CEILING, 500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][16] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][17] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][18] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][19] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][20] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][21] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][22] = Floor(100, 600, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	//

#pragma endregion
#pragma region stage4
	//ステージ4
	floor[4][0] = Floor(100, 680, 50000, 10, NORMAL, 50000, 10, 64, 64, NORMALFLOOR, player);
	floor[4][1] = Floor(0, -2000, 50000, 1000, CEILING, 50000, 1000, 64, 64, STAGECEILING, player);
	floor[4][2] = Floor(600, 580, 300, 10, NORMAL, 300, 10, 64, 64, NORMALFLOOR, player);
	//
#pragma endregion
#pragma region stage5
	//ステージ5
	floor[5][0] = Floor(100, 680, 50000, 10, NORMAL, 50000, 10, 64, 64, NORMALFLOOR, player);
	floor[5][1] = Floor(0, -2000, 50000, 1000, CEILING, 50000, 1000, 64, 64, STAGECEILING, player);
	floor[5][2] = Floor(600, 580, 300, 10, NORMAL, 300, 10, 64, 64, NORMALFLOOR, player);
	//
#pragma endregion

	//初期化用
	Floor RESET_FLOOR[STAGE_NUMBER][FLOOR_NUMBER];

	for (int a = 0; a < STAGE_NUMBER; a++) {
		for (int b = 0; b < FLOOR_NUMBER; b++) {
			RESET_FLOOR[a][b] = floor[a][b];
		}
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		Key::Update();

		switch (scene) {

		case TITLE:

			///
			/// ↓更新処理ここから
			///

			if (sceneChange == true) {

				//フェードイン
				if (nextScene == TITLE) {

					if (sceneCount > 0) {
						sceneCount -= 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX -= WINDOW_WIDTH;
					}

					if (sceneX < 0) {
						sceneX = 0;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < SCENE_TIMER) {
						sceneCount += 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX += WINDOW_WIDTH;
					}

					if (sceneX > 5120) {
						sceneX = 5120;
					}

					if (sceneCount == SCENE_TIMER) {

						scene = nextScene;

					}

				}

			}
			else if (sceneChange == false) {

				if (Key::IsTrigger(DIK_SPACE)) {
					sceneChange = true;
					nextScene = STAGESELECT;
				}

			}

			///
			/// ↑更新処理ここまで
			///



			///
			/// ↓描画処理ここから
			///

			Novice::DrawSprite(0, 0, BGTITLE, 1, 1, 0, 0xFFFFFFFF);

			///
			/// ↑描画処理ここまで
			///

			break;

		case STAGESELECT:

			///
			/// ↓更新処理ここから
			///

			if (sceneChange == true) {

				//フェードイン
				if (nextScene == STAGESELECT) {

					if (sceneCount > 0) {
						sceneCount -= 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX -= WINDOW_WIDTH;
					}

					if (sceneX < 0) {
						sceneX = 0;
					}

					if (sceneCount == 0) {
						sceneChange = false;
						isGoal = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < SCENE_TIMER) {
						sceneCount += 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX += WINDOW_WIDTH;
					}

					if (sceneX > 5120) {
						sceneX = 5120;
					}

					if (sceneCount == SCENE_TIMER) {

						scene = nextScene;

					}

				}

			}
			else if (sceneChange == false) {

				if (Key::IsTrigger(DIK_UP) && stageSelect > 1) {
					stageSelect -= 1;
					for (int i = 0; i < 8; i++) {
						if (!Novice::IsPlayingAudio(SELECTSOUNDCHECK[i]) || SELECTSOUNDCHECK[i] == -1) {
							SELECTSOUNDCHECK[i] = Novice::PlayAudio(SELECTSOUND, 0, 0.5f);
							break;
						}

					}
				}

				if (Key::IsTrigger(DIK_DOWN) && stageSelect < STAGE_NUMBER - 1) {
					stageSelect += 1;
					for (int i = 0; i < 8; i++) {
						if (!Novice::IsPlayingAudio(SELECTSOUNDCHECK[i]) || SELECTSOUNDCHECK[i] == -1) {
							SELECTSOUNDCHECK[i] = Novice::PlayAudio(SELECTSOUND, 0, 0.5f);
							break;
						}

					}
				}

				if (Key::IsTrigger(DIK_SPACE)) {
					sceneChange = true;
					isLoading = 0;
					if (!Novice::IsPlayingAudio(DECISIONSOUNDCHECK) || DECISIONSOUNDCHECK == -1) {
						DECISIONSOUNDCHECK = Novice::PlayAudio(DECISIONSOUND, 0, 0.5f);
					}
					if (!Novice::IsPlayingAudio(SCENECHANGESOUNDCHECK) || SCENECHANGESOUNDCHECK == -1) {
						SCENECHANGESOUNDCHECK = Novice::PlayAudio(SCENECHANGESOUND, 0, 0.5f);
					}
					nextScene = GAMEPLAY;
				}

				if (Key::IsTrigger(DIK_ESCAPE)) {
					sceneChange = true;
					nextScene = TITLE;
				}

			}



			///
			/// ↑更新処理ここまで
			///



			///
			/// ↓描画処理ここから
			///

			Novice::DrawSprite(0, 0, BGSELECT, 1, 1, 0, 0xFFFFFFFF);

			Novice::DrawQuad(0, 0, 640, 0, 0, 64, 640, 64, 384, 0, 640, 64, SELECTWOOD, 0xFFFFFFFF);

			for (int i = 1; i < STAGE_NUMBER; i++) {

				if (stageSelect == i) {
					Novice::DrawQuad(0, 64 * i, 512, 64 * i, 0, 64 * i + 64, 512, 64 * i + 64, 0, 0, 512, 64, BRIGHTWOOD[i], 0xFFFFFFFF);
				}
				else {
					Novice::DrawQuad(0, 64 * i, 512 - 128, 64 * i, 0, 64 * i + 64, 512 - 128, 64 * i + 64, 128, 0, 512 - 128, 64, WOOD[i], 0xFFFFFFFF);
				}

			}

			///
			/// ↑描画処理ここまで
			///

			break;

		case GAMEPLAY:

			///
			/// ↓更新処理ここから
			///

			//シーンチェンジが有効になったら
			if (sceneChange == true && isGoal == false) {

				//フェードイン
				if (nextScene == GAMEPLAY) {

					if (isLoading == 0) {

						scroll = { 0.0f,0.0f };

						//プレイヤーの初期化
						player.resetPosition();

						player.setSpeed0X();

						player.RecoveryTarzanGage();

						player.setSpeedY();

						player.resetCenter();

						maxSpeed = 0.0f;

						//ステージの初期化
						for (int a = 0; a < STAGE_NUMBER; a++) {

							for (int b = 0; b < WALL_NUMBER; b++) {

								wall[a][b] = RESET_WALL[a][b];

							}

							for (int b = 0; b < FLOOR_NUMBER; b++) {

								floor[a][b] = RESET_FLOOR[a][b];

							}

						}

						isLoading = 1;

					}

					if (sceneCount > 0) {
						sceneCount -= 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX -= WINDOW_WIDTH;
					}

					if (sceneX < 0) {
						sceneX = 0;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < SCENE_TIMER) {
						sceneCount += 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX += WINDOW_WIDTH;
					}

					if (sceneX > 5120) {
						sceneX = 5120;
					}

					if (sceneCount == SCENE_TIMER) {

						scene = nextScene;

					}

				}

			}
			//ゴールしたら
			else if (isGoal == true) {

				//リザルト表示
				if (sceneChange == false) {

					if (sceneCount < SCENE_TIMER) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					//キー入力でシーンチェンジを有効にする
					if (sceneCount == SCENE_TIMER) {

						if (Key::IsTrigger(DIK_SPACE)) {
							sceneChange = true;
							nextScene = STAGESELECT;
						}

					}

				}
				else {

					if (sceneCount < SCENE_TIMER * 2) {
						sceneCount += 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX += WINDOW_WIDTH;
					}

					if (sceneX > 5120) {
						sceneX = 5120;
					}

					if (sceneCount == SCENE_TIMER * 2) {
						sceneCount = SCENE_TIMER;
						scene = nextScene;
					}

				}

			}
			//ゲームプレイ中
			else if (sceneChange == false && isGoal == false) {

				if (Key::IsTrigger(DIK_ESCAPE)) {
					sceneChange = true;
					nextScene = STAGESELECT;
				}

#pragma region DrawTimer

				drawTimer += 1;

				if (drawTimer % 6 == 0) {

					player.MoveDrawX();

					if (player.getDrawX() > 128) {
						player.resetDrawX();
					}
				}

				if (drawTimer >= 60) {
					drawTimer = 0;
				}

#pragma endregion

				player.Update(scroll);

				for (int i = 0; i < FLOOR_NUMBER; i++) {
					floor[stageSelect][i].Update(scroll);
				}


				for (int i = 0; i < WALL_NUMBER; i++) {
					wall[stageSelect][i].Update(scroll);
				}

#pragma region エフェクト

				//拡散
				diffusionParticle(player.getPosX(), player.getPosY(), diffusionBox, displayTimeDiffusion);
				diffusionParticleMove(diffusionBox, displayTimeDiffusion);

				//残像
				/*for (int i = 0; i < emitterMax; i++) {

					if (afterImageBox[i].isActive == false) {

						afterImageBox[i].left.Top.x = player.getPosX() - 16;
						afterImageBox[i].left.Top.y = player.getPosY() - 16;
						afterImageBox[i].left.Bottom.x = player.getPosX() - 16;
						afterImageBox[i].left.Bottom.y = player.getPosY() + 16;
						afterImageBox[i].right.Top.x = player.getPosX() + 16;
						afterImageBox[i].right.Top.y = player.getPosY() - 16;
						afterImageBox[i].right.Bottom.x = player.getPosX() + 16;
						afterImageBox[i].right.Bottom.y = player.getPosY() + 16;

						afterImageBox[i].imagesPos = player.getDrawX();

						break;
					}
				}*/

				afterImage(player.getPosX(), player.getPosY(), afterImageBox, displayTimeAfter);
				afterImageMove(player.getPosX(), player.getPosY(), afterImageBox, displayTimeAfter);

				//地面についたらフラグをオンにする
				if (player.getIsGround() == true) {

					isShake = true;
				}

				//飛んだらいろいろ初期化
				if (player.getIsGround() == false) {

					isPlayerLanding = true;

					for (int i = 0; i < 4; i++) {
						landingBox[i].isActive = false;
					}

					if (isShake == false) {
						if (shakes.time <= 0) {
							shakes.time = 60;
						}
					}
				}

				//地面についたらフラグをオンにする
				if (player.getIsGround() == true) {
					if (isPlayerLanding == true) {

						landingParticle(player.getPosX(), player.getPosY(), landingBox);

						if (landingBox[0].isActive == false) {

							landingBox[1].isActive = false;
							landingBox[2].isActive = false;
							landingBox[3].isActive = false;

							isPlayerLanding = false;
						}
					}
				}

				if (isShake == true) {

					shakes = shake(shakes);

					if (shakes.time == 0) {

						isShake = false;

					}
				}
			

#pragma endregion

				if (player.getPosX() > GOAL_LINE[stageSelect]) {
					isGoal = true;
					player.stopAudio();
				}

			}

			//最大速度を更新
			if ( AbsoluteValuef(player.getSpeedX()) > AbsoluteValuef(maxSpeed)) {
				maxSpeed = player.getSpeedX();
			}

			//速度を表示できるようにintに変換
			drawMaxSpeed = maxSpeed * 1000;

			drawSpeed = player.getSpeedX() * 1000;

			///
			/// ↑更新処理ここまで
			///



			///
			/// ↓描画処理ここから
			///

			for (int y = 0; y < REPETITION_Y; y++) {

				for (int x = 0; x < REPETITION_X; x++) {
					Novice::DrawQuad(WINDOW_WIDTH * x - scroll.x + shakes.pos.x, -WINDOW_HEIGHT * y - scroll.y + shakes.pos.y,
						WINDOW_WIDTH * x + WINDOW_WIDTH - scroll.x + shakes.pos.x, -WINDOW_HEIGHT * y - scroll.y + shakes.pos.y,
						WINDOW_WIDTH * x - scroll.x + shakes.pos.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y + shakes.pos.y,
						WINDOW_WIDTH * x + WINDOW_WIDTH - scroll.x + shakes.pos.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y + shakes.pos.y,
						0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, INGAMEBG, 0x888888FF);
				}

			}

			if (stageSelect == 1) {
				
				//チュートリアルUIの表示
				Novice::DrawQuad(500 - scroll.x, 400 - scroll.y, 756 - scroll.x, 400 - scroll.y,
					500 - scroll.x, 656 - scroll.y, 756 - scroll.x, 656 - scroll.y, 0, 0, 256, 256, PRESSINFO, 0xFFFFFFFF);

				Novice::DrawQuad(4700 - scroll.x, 450 - scroll.y, 4956 - scroll.x, 450 - scroll.y,
					4700 - scroll.x, 706 - scroll.y, 4956 - scroll.x, 706 - scroll.y, 0, 0, 256, 256, BREAKINFO, 0xFFFFFFFF);

				Novice::DrawQuad(6000 - scroll.x, 450 - scroll.y, 6256 - scroll.x, 450 - scroll.y,
					6000 - scroll.x, 706 - scroll.y, 6256 - scroll.x, 706 - scroll.y, 0, 0, 256, 256, SLOWINFO, 0xFFFFFFFF);

				Novice::DrawQuad(7000 - scroll.x, -16 - scroll.y, 7256 - scroll.x, -16 - scroll.y,
					7000 - scroll.x, 240 - scroll.y, 7256 - scroll.x, 240 - scroll.y, 0, 0, 256, 256, FASTINFO, 0xFFFFFFFF);

			}

#pragma region パーティクルの描画処理

			//拡散する方
			for (int i = 0; i < emitterMax; i++) {

				if (diffusionBox[i].isActive == true) {

					Novice::DrawBox(
						diffusionBox[i].pos.x - diffusionBox[i].size.x / 2 - scroll.x,
						diffusionBox[i].pos.y - diffusionBox[i].size.y / 2 - scroll.y,
						diffusionBox[i].size.x,
						diffusionBox[i].size.y,
						0.0f,
						diffusionBox[i].color,
						kFillModeSolid
					);

				}

			}

			//速度
			for (int i = 0; i < emitterMax; i++) {

				if (SpeedBox[i].isActive == true) {

					Novice::DrawBox(
						SpeedBox[i].pos.x - SpeedBox[i].size.x / 2 - afterImageBox[i].size.x / 2 - scroll.x,
						SpeedBox[i].pos.y - SpeedBox[i].size.y / 2 - afterImageBox[i].size.x / 2 - scroll.y,
						SpeedBox[i].size.x,
						SpeedBox[i].size.y,
						0.0f,
						SpeedBox[i].color,
						kFillModeSolid
					);

				}

			}


			//残像
			for (int i = 0; i < emitterMax; i++) {

				if (player.getIsGround() == true) {

					if (afterImageBox[i].isActive == true) {

						Novice::DrawQuad(
							afterImageBox[i].pos.x - afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y - afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x + afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y - afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x - afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y + afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x + afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y + afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].imagesPos,
							0,
							32,
							32,
							PLAYERRUN,
							afterImageBox[i].color
						);


					}
				}

				if (player.getIsGround() == false) {

					if (afterImageBox[i].isActive == true) {

						Novice::DrawQuad(
							afterImageBox[i].pos.x - afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y - afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x + afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y - afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x - afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y + afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].pos.x + afterImageBox[i].size.x / 2 - scroll.x,
							afterImageBox[i].pos.y + afterImageBox[i].size.y / 2 - scroll.y,
							afterImageBox[i].imagesPos,
							0,
							32,
							32,
							PLAYERTARZAN,
							afterImageBox[i].color
						);


					}
				}



			}

			//落下
			for (int i = 0; i < emitterMax; i++) {

				if (landingBox[i].isActive == true) {

					Novice::DrawBox(
						landingBox[i].pos.x - landingBox[i].size.x / 2 - scroll.x,
						landingBox[i].pos.y - landingBox[i].size.y / 2 - scroll.y,
						landingBox[i].size.x,
						landingBox[i].size.y,
						landingBox[i].angle,
						landingBox[i].color,
						kFillModeSolid
					);

				}

			}

			//左衝突
			for (int i = 0; i < emitterMax; i++) {

				if (leftClashBox[i].isActive == true) {

					Novice::DrawBox(
						leftClashBox[i].pos.x - leftClashBox[i].size.x / 2,
						leftClashBox[i].pos.y - leftClashBox[i].size.y / 2,
						leftClashBox[i].size.x,
						leftClashBox[i].size.y,
						leftClashBox[i].angle,
						leftClashBox[i].color,
						kFillModeSolid
					);

				}

			}

			//右衝突
			for (int i = 0; i < emitterMax; i++) {

				if (rightClashBox[i].isActive == true) {

					Novice::DrawBox(
						rightClashBox[i].pos.x - rightClashBox[i].size.x / 2,
						rightClashBox[i].pos.y - rightClashBox[i].size.y / 2,
						rightClashBox[i].size.x,
						rightClashBox[i].size.y,
						rightClashBox[i].angle,
						rightClashBox[i].color,
						kFillModeSolid
					);

				}

			}


			//加速線 
			for (int i = 0; i < emitterMax; i++) {

				if (SpeedLineBox[i].isActive == true) {

					Novice::DrawQuad(
						SpeedLineBox[i].pos.x - SpeedLineBox[i].size.x / 2 - scroll.x,
						SpeedLineBox[i].pos.y - SpeedLineBox[i].size.y / 2 - scroll.y,
						SpeedLineBox[i].pos.x + SpeedLineBox[i].size.x / 2 - scroll.x,
						SpeedLineBox[i].pos.y - SpeedLineBox[i].size.y / 2 - scroll.y,
						SpeedLineBox[i].pos.x - SpeedLineBox[i].size.x / 2 - scroll.x,
						SpeedLineBox[i].pos.y + SpeedLineBox[i].size.y / 2 - scroll.y,
						SpeedLineBox[i].pos.x + SpeedLineBox[i].size.x / 2 - scroll.x,
						SpeedLineBox[i].pos.y + SpeedLineBox[i].size.y / 2 - scroll.y,
						0,
						0,
						64,
						64,
						0,
						SpeedLineBox[i].color
					);

				}

			}

#pragma endregion

			player.Draw(scroll);

			for (int i = 0; i < FLOOR_NUMBER; i++) {
				floor[stageSelect][i].Draw(scroll);
			}

			for (int i = 0; i < WALL_NUMBER; i++) {
				wall[stageSelect][i].Draw(scroll);
			}

			//ここからUIの表示
			Novice::DrawSprite(0, 0, UI, 1, 1, 0.0f, 0xFFFFFFFF);

			//ターザンゲージ
			Novice::DrawQuad(640 - 256 - 4, 84 - 4, (640 - 256) + 512 + 4, 84 - 4,
				640 - 256 - 4, 116 + 4, (640 - 256) + 512 + 4, 116 + 4,
				0, 0, 512, 64, BACKGAGE, 0xFFFFFFFF);

			Novice::DrawQuad(640 - 256, 84, (640 - 256) + (player.getTarzanGage() * 512) / TARZAN_GAGE, 84,
				640 - 256, 116, (640 - 256) + (player.getTarzanGage() * 512) / TARZAN_GAGE, 116,
				0, 0, (player.getTarzanGage() * 512) / TARZAN_GAGE, 64, GAGE, 0xFFFFFFFF);

			//ドット
			Novice::DrawQuad(195, 64, 243, 64, 195, 112, 243, 112, 0, 0, 64, 64, DOT, 0xFFFFFFFF);

			//スピード
			Novice::DrawQuad(30, 48, 158, 48, 30, 80, 158, 80, 0, 0, 256, 64, SPEED, 0xFFFFFFFF);

			//スピードの表示
			for (int a = 0; a < 5; a++) {

				divideNumber = 1;

				for (int b = 0; b < 4; b++) {
					divideNumber *= 10;
				}

				for (int c = 0; c < a; c++) {
					divideNumber /= 10;
				}

				drawNumber = AbsoluteValue(drawSpeed) / divideNumber;

				for (int d = 0; d < 10; d++) {

					if (d == drawNumber) {

						if (a < 2) {
							Novice::DrawQuad(132 + a * 32, 32, 196 + a * 32, 32, 132 + a * 32, 96, 196 + a * 32, 96, 0, 0, 64, 64, NUM[d], 0xFFFFFFFF);
						}
						else {
							Novice::DrawQuad(148 + a * 32, 32, 212 + a * 32, 32, 148 + a * 32, 96, 212 + a * 32, 96, 0, 0, 64, 64, NUM[d], 0xFFFFFFFF);
						}

					}

				}

				drawSpeed = AbsoluteValue(drawSpeed) % divideNumber;

			}

			//----------------最大速度の表示------------------

			//ドット
			Novice::DrawQuad(1095, 64, 1143, 64, 1095, 112, 1143, 112, 0, 0, 64, 64, REDDOT, 0xFFFFFFFF);

			//スピード
			Novice::DrawQuad(888, 48, 1048, 48, 888, 80, 1048, 80, 0, 0, 320, 64, MAXSPEED, 0xFFFFFFFF);

			//スピードの表示
			for (int a = 0; a < 5; a++) {

				divideNumber = 1;

				for (int b = 0; b < 4; b++) {
					divideNumber *= 10;
				}

				for (int c = 0; c < a; c++) {
					divideNumber /= 10;
				}

				drawNumber = AbsoluteValue(drawMaxSpeed) / divideNumber;

				for (int d = 0; d < 10; d++) {

					if (d == drawNumber) {

						if (a < 2) {
							Novice::DrawQuad(1032 + a * 32, 32, 1096 + a * 32, 32, 1032 + a * 32, 96, 1096 + a * 32, 96, 0, 0, 64, 64, REDNUM[d], 0xFFFFFFFF);
						}
						else {
							Novice::DrawQuad(1048 + a * 32, 32, 1112 + a * 32, 32, 1048 + a * 32, 96, 1112 + a * 32, 96, 0, 0, 64, 64, REDNUM[d], 0xFFFFFFFF);
						}

					}

				}

				drawMaxSpeed = AbsoluteValue(drawMaxSpeed) % divideNumber;

			}

			///
			/// ↑描画処理ここまで
			///

			break;

		}

		if (isGoal == true) {

			Novice::DrawBox(0, 0, 1280, 720, 0, clearly, kFillModeSolid);

		}

		if (sceneChange == true) {

			Novice::DrawQuad(0, 0, 1280, 0, 0, 720, 1280, 720, sceneX, 0, 1280, 720, SCENECHANGE, 0xFFFFFFFF);

		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE) && scene == TITLE && sceneChange == false) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
