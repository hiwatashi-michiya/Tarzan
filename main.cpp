#include <Novice.h>
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"
#include "Floor.h"
#include "Stage.h"
#include "Calc.h"
#include "effect.h"
#include "Easing.h"

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
	int BGSELECT = Novice::LoadTexture("./Resources/Images/BG/ingameBG.png");

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

	// ターザンミュージック
	int TARZANMUSIC = Novice::LoadAudio("./Resources/BGM/TarzanBGM.wav");
	int TARZANMUSICCHECK = -1;

	// 着地音
	int LANDINGSOUND = Novice::LoadAudio("./Resources/SE/landing.wav");
	int LANDINGSOUNDCHECK = -1;

	// 壁にぶつかった音
	int BREAKSOUND = Novice::LoadAudio("./Resources/SE/break.wav");

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
	int PLAYERLANDING = Novice::LoadTexture("./Resources/Images/Player/playerLanding.png");
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
	int BRIGHTWOOD[STAGE_NUMBER];
	//特に使わない
	BRIGHTWOOD[0] = 0;
	//
	BRIGHTWOOD[1] = Novice::LoadTexture("./Resources/Images/UI/stage1select.png");
	BRIGHTWOOD[2] = Novice::LoadTexture("./Resources/Images/UI/stage2select.png");
	BRIGHTWOOD[3] = Novice::LoadTexture("./Resources/Images/UI/stage3select.png");
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

	//ゴール
	int GOAL = Novice::LoadTexture("./Resources/Images/UI/goal.png");

	//ゴールテキスト
	int GOALTEXT = Novice::LoadTexture("./Resources/Images/UI/goaltext.png");

	//選択肢のUI
	int SELECT = Novice::LoadTexture("./Resources/Images/UI/select.png");

	//スペースUI
	int SPACESTART = Novice::LoadTexture("./Resources/Images/UI/spacestart.png");
	int SPACESELECT = Novice::LoadTexture("./Resources/Images/UI/spaceselect.png");

	//タイトルUI
	int TITLETEXT = Novice::LoadTexture("./Resources/Images/UI/title.png");

	//ESC UI

	int ESCBACK = Novice::LoadTexture("./Resources/Images/UI/back.png");

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

	//選択ボタン画像の切り替え
	int drawSelectTimer = 0;

	int drawSelectX = 0;

	//タイトル画像のタイマー
	int drawTitleTimer = 0;

	//ゴール時のタイマー
	int drawGoalTimer = 0;

	//ゴール画像の座標
	int goalX = 0;
	int goalY = 0;
	int goalW = 0;
	int goalH = 0;

	//座標
	float titlePosX = -800.0f;
	float titlePosY = 100.0f;
	//始点
	float startPosX = -800.0f;
	//終点
	float endPosX = 384.0f;

	//イージング
	float t = 0.0f;
	float easingSpeed = 0.01f;
	float number = 0.0f;

	//タイトルの文字が動いているか(フラグ)
	bool isTitleMove = true;

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


	int PLAYERIMAGES[PLAYER_STATE_NUM] = {
		PLAYERIDLE,PLAYERRUN,PLAYERTARZAN,PLAYERSKY,PLAYERLANDING
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
	wall[1][6] = Wall({ 17000.0f,434.0f }, 512, 246, 35.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
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
	wall[3][1] = Wall({ -100.0f,-1000.0f }, 256, 2000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][2] = Wall({ 6250.0f,310.0f }, 500, 1000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][3] = Wall({ 14250.0f,110.0f }, 500, 1000, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][4] = Wall({ 156.0f,610.0f }, 944, 200, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][5] = Wall({ 1700.0f,0.0f }, 1500, 190, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][6] = Wall({ 4200.0f,-2000.0f }, 1500, 1700, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][7] = Wall({ 15500.0f,-200.0f }, 1000, 690, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][8] = Wall({ 16000.0f,500.0f }, 100, 180, 20.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[3][9] = Wall({ 15700.0f,-2000.0f }, 300, 1790, 45.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[3][10] = Wall({ 28000.0f,-2000.0f }, 300, 2100, 35.0f, true, BREAK, 0xFFFFFFFF, player, BREAKWALL);
	wall[3][11] = Wall({ 27500.0f,110.0f }, 4000, 800, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][12] = Wall({ 19000.0f,-2000.0f }, 1000, 1930, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][13] = Wall({ 21875.0f,-2000.0f }, 750, 1880, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][14] = Wall({ 24250.0f,-2000.0f }, 500, 1850, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][15] = Wall({ 26125.0f,-2000.0f }, 250, 1820, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][16] = Wall({ 18500.0f,240.0f }, 2000, 60, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][17] = Wall({ 21500.0f,190.0f }, 1500, 110, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][18] = Wall({ 24000.0f,160.0f }, 1000, 140, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[3][19] = Wall({ 26000.0f,130.0f }, 500, 170, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
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
	floor[1][6] = Floor(17000, 404, 512, 30, NORMAL, 512, 30, 64, 64, NORMALFLOOR, player);
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
	floor[2][14] = Floor(5500, 190, 300, 10, NORMAL, 300, 10, 64, 64, NORMALFLOOR, player);
	floor[2][15] = Floor(10000, 380, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[2][16] = Floor(10500, 430, 1500, 10, NORMAL, 1500, 10, 64, 64, NORMALFLOOR, player);
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
	floor[3][10] = Floor(17000, 200, 1000, 10, NORMAL, 1000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][11] = Floor(18000, 680, 10800, 10, PLAYERACCEL, 10800, 10, 64, 64, ACCELFLOOR, player);
	floor[3][12] = Floor(1700, 190, 1500, 10, CEILING, 1500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][13] = Floor(1700, -10, 1500, 10, PLAYERACCEL, 1500, 10, 64, 64, ACCELFLOOR, player);
	floor[3][14] = Floor(1700, -300, 2550, 10, NORMAL, 2500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][15] = Floor(4200, -300, 1500, 10, CEILING, 1500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][16] = Floor(3700, -10, 2000, 10, PLAYERACCEL, 2000, 10, 64, 64, ACCELFLOOR, player);
	floor[3][17] = Floor(10000, 680, 4250, 10, PLAYERDECEL, 4250, 10, 64, 64, DECELFLOOR, player);
	floor[3][18] = Floor(4000, 680, 2250, 10, PLAYERDECEL, 2250, 10, 64, 64, DECELFLOOR, player);
	floor[3][19] = Floor(8700, -100, 1300, 10, PLAYERACCEL, 1300, 10, 64, 64, ACCELFLOOR, player);
	floor[3][20] = Floor(3700, 0, 2000, 10, CEILING, 2000, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][21] = Floor(8700, -90, 1300, 10, CEILING, 1300, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][22] = Floor(14000, -200, 1500, 10, CEILING, 1500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][23] = Floor(14000, -210, 2500, 10, PLAYERACCEL, 2500, 10, 64, 64, ACCELFLOOR, player);
	floor[3][24] = Floor(15500, 490, 1000, 10, CEILING, 1000, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][25] = Floor(15000, 390, 550, 10, NORMAL, 550, 10, 64, 64, NORMALFLOOR, player);
	floor[3][26] = Floor(16500, 340, 500, 10, NORMAL, 500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][27] = Floor(18500, 230, 2000, 10, NORMAL, 2000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][28] = Floor(21500, 180, 1500, 10, NORMAL, 1500, 10, 64, 64, NORMALFLOOR, player);
	floor[3][29] = Floor(24000, 150, 1000, 10, PLAYERACCEL, 1000, 10, 64, 64, ACCELFLOOR, player);
	floor[3][30] = Floor(26000, 120, 500, 10, PLAYERACCEL, 500, 10, 64, 64, ACCELFLOOR, player);
	floor[3][31] = Floor(27500, 100, 4000, 10, NORMAL, 4000, 10, 64, 64, NORMALFLOOR, player);
	floor[3][32] = Floor(18500, 300, 9000, 10, CEILING, 9000, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][33] = Floor(19000, -70, 1000, 10, CEILING, 1000, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][34] = Floor(21875, -120, 750, 10, CEILING, 750, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][35] = Floor(24250, -150, 500, 10, CEILING, 500, 10, 64, 64, CEILINGFLOOR, player);
	floor[3][36] = Floor(26125, -180, 250, 10, CEILING, 250, 10, 64, 64, CEILINGFLOOR, player);
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

		if (!Novice::IsPlayingAudio(TARZANMUSICCHECK) || TARZANMUSICCHECK == -1) {
			TARZANMUSICCHECK = Novice::PlayAudio(TARZANMUSIC, 1, 0.1f);
		}

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
						//セレクト画面の描画タイマーリセット
						drawSelectTimer = 0;
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

				drawTitleTimer += 1;

				if (drawTitleTimer == 60) {
					drawTitleTimer = 0;
				}

				if (isTitleMove == true) {
					t = Easing::OutElastic(number);

					number += easingSpeed;

					titlePosX = (1 - t) * startPosX + t * endPosX;

					if (number >= 1.0f) {
						isTitleMove = false;
					}
				}

				if (Key::IsTrigger(DIK_SPACE)) {
					sceneChange = true;
					if (!Novice::IsPlayingAudio(SCENECHANGESOUNDCHECK) || SCENECHANGESOUNDCHECK == -1) {
						SCENECHANGESOUNDCHECK = Novice::PlayAudio(SCENECHANGESOUND, 0, 0.5f);
					}
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

			Novice::DrawSprite(titlePosX, titlePosY, TITLETEXT, 1, 1, 0.0f, 0xFFFFFF);

			if (drawTitleTimer < 50) {
				Novice::DrawSprite(640 - 256, 600, SPACESTART, 1, 1, 0, 0xFFFFFFFF);
			}
			
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
						player.stopAudio();
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

						titlePosX = -800.0f;
						titlePosY = 100.0f;
						//始点
						startPosX = -800.0f;
						//終点
						endPosX = 384.0f;

						//イージング
						t = 0.0f;
						easingSpeed = 0.01f;
						number = 0.0f;

						isTitleMove = true;

						scene = nextScene;

					}

				}

			}
			else if (sceneChange == false) {

				drawSelectTimer += 1;

				if (drawSelectTimer == 60) {
					drawSelectTimer = 0;
				}

				if (drawSelectTimer % 15 == 0) {
					drawSelectX += 64;
				}

				if (drawSelectX > 64) {
					drawSelectX = 0;
				}

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
					//タイトル画面の描画タイマーリセット
					drawTitleTimer = 0;
					if (!Novice::IsPlayingAudio(SCENECHANGESOUNDCHECK) || SCENECHANGESOUNDCHECK == -1) {
						SCENECHANGESOUNDCHECK = Novice::PlayAudio(SCENECHANGESOUND, 0, 0.5f);
					}
					nextScene = TITLE;
				}

			}



			///
			/// ↑更新処理ここまで
			///



			///
			/// ↓描画処理ここから
			///

			Novice::DrawSprite(0, 0, BGSELECT, 1, 1, 0, 0x888888FF);

			Novice::DrawQuad(0, 0, 640, 0, 0, 64, 640, 64, 384, 0, 640, 64, SELECTWOOD, 0xFFFFFFFF);

			for (int i = 1; i < STAGE_NUMBER; i++) {

				if (stageSelect == i) {
					Novice::DrawQuad(0, 64 * i, 512, 64 * i, 0, 64 * i + 64, 512, 64 * i + 64, 0, 0, 512, 64, BRIGHTWOOD[i], 0xFFFFFFFF);
					Novice::DrawQuad(544, 64 * i - 32, 608, 64 * i - 32, 544, 64 * i + 96, 608, 64 * i + 96, drawSelectX, 0, 64, 128, SELECT, 0xFFFFFFFF);
				}
				else {
					Novice::DrawQuad(0, 64 * i, 512 - 128, 64 * i, 0, 64 * i + 64, 512 - 128, 64 * i + 64, 128, 0, 512 - 128, 64, WOOD[i], 0xFFFFFFFF);
				}

			}

			if (drawSelectTimer < 50) {
				Novice::DrawSprite(640 - 256, 600, SPACESTART, 1, 1, 0, 0xFFFFFFFF);
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

						player.resetPlayer();

						maxSpeed = 0.0f;

						goalX = 0;
						goalY = 0;
						goalW = 0;
						goalH = 0;

						//ステージの初期化
						for (int a = 0; a < STAGE_NUMBER; a++) {

							for (int b = 0; b < WALL_NUMBER; b++) {

								wall[a][b] = RESET_WALL[a][b];

							}

							for (int b = 0; b < FLOOR_NUMBER; b++) {

								floor[a][b] = RESET_FLOOR[a][b];

							}

						}

						//エフェクトの初期化
						
						isShake = false;
						isPlayerLanding = false;
						for (int i = 0; i < 4; i++) {
							landingBox[i].isActive = false;
						}
						landingBox[0].isActive = false;
						landingBox[1].isActive = false;
						landingBox[2].isActive = false;
						landingBox[3].isActive = false;

						//

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
						//セレクト画面の描画タイマーリセット
						drawSelectTimer = 0;
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

					if (goalW < 512) {
						goalW += 16;
					}

					if (sceneCount < SCENE_TIMER * 2) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 2;
					}

					//キー入力でシーンチェンジを有効にする
					if (sceneCount == SCENE_TIMER * 2) {

						drawGoalTimer += 1;

						if (drawGoalTimer == 60) {
							drawGoalTimer = 0;
						}

						if (Key::IsTrigger(DIK_SPACE)) {
							sceneChange = true;
							if (!Novice::IsPlayingAudio(SCENECHANGESOUNDCHECK) || SCENECHANGESOUNDCHECK == -1) {
								SCENECHANGESOUNDCHECK = Novice::PlayAudio(SCENECHANGESOUND, 0, 0.5f);
							}
							nextScene = STAGESELECT;
							player.stopAudio();
						}

					}

				}
				else {

					if (sceneCount < SCENE_TIMER * 4) {
						sceneCount += 1;
					}

					if (sceneCount % 6 == 0) {
						sceneX += WINDOW_WIDTH;
					}

					if (sceneX > 5120) {
						sceneX = 5120;
					}

					if (sceneCount == SCENE_TIMER * 4) {
						sceneCount = SCENE_TIMER;
						drawGoalTimer = 0;
						scene = nextScene;
					}

				}

			}
			//ゲームプレイ中
			else if (sceneChange == false && isGoal == false) {

				if (Key::IsTrigger(DIK_ESCAPE)) {
					sceneChange = true;
					if (!Novice::IsPlayingAudio(SCENECHANGESOUNDCHECK) || SCENECHANGESOUNDCHECK == -1) {
						SCENECHANGESOUNDCHECK = Novice::PlayAudio(SCENECHANGESOUND, 0, 0.5f);
					}
					nextScene = STAGESELECT;
					player.stopAudio();
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
					wall[stageSelect][i].Update(scroll, BREAKSOUND);
				}

#pragma region エフェクト

				//拡散
				diffusionParticle(player.getPosX(), player.getPosY(), diffusionBox, displayTimeDiffusion);
				diffusionParticleMove(diffusionBox, displayTimeDiffusion);

				afterImage(player.getPosX(), player.getPosY(), afterImageBox, displayTimeAfter);
				afterImageMove(player.getPosX(), player.getPosY(), afterImageBox, displayTimeAfter);

				//地面についたらフラグをオンにする
				if (player.getIsGround() == true) {

					//シェイクさせる
					isShake = true;
				}

				//飛んだらいろいろ初期化
				if (player.getIsGround() == false) {

					//地面についたら着地エフェクトを発生
					isPlayerLanding = true;

					//着地エフェクトを消す
					for (int i = 0; i < 4; i++) {
						landingBox[i].isActive = false;
					}

					//シェイクする時間を再設定
					if (isShake == false) {
						if (shakes.time <= 0) {
							shakes.time = 60;
						}
					}
				}

				//壁に当たったらシェイクのフラグをtrueにする
				for (int i = 0; i < WALL_NUMBER; i++) {

					if (wall[stageSelect][i].getIsHit() == true) {

						isShake = true;
					}
				}

				//落下エフェクト
				//地面についたら着地エフェクトを発生
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


				//シェイク
				if (isShake == true) {

					shakes = shake(shakes, player.getSpeedX());

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

			Novice::DrawQuad(GOAL_LINE[stageSelect] - scroll.x - 16, -1000 - scroll.y, GOAL_LINE[stageSelect] - scroll.x + 16, -1000 - scroll.y,
				GOAL_LINE[stageSelect] - scroll.x - 16, 1048 - scroll.y, GOAL_LINE[stageSelect] - scroll.x + 16, 1048 - scroll.y, 0, 0, 32, 2048, GOAL, 0xFFFFFFFF);

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
			Novice::DrawQuad(195 + 32, 64, 243 + 32, 64, 195 + 32, 112, 243 + 32, 112, 0, 0, 64, 64, DOT, 0xFFFFFFFF);

			//スピード
			Novice::DrawQuad(30, 48, 158, 48, 30, 80, 158, 80, 0, 0, 256, 64, SPEED, 0xFFFFFFFF);

			//スピードの表示
			for (int a = 0; a < 5; a++) {

				divideNumber = 1;

				for (int b = 0; b < 5; b++) {
					divideNumber *= 10;
				}

				for (int c = 0; c < a; c++) {
					divideNumber /= 10;
				}

				drawNumber = AbsoluteValue(drawSpeed) / divideNumber;

				for (int d = 0; d < 10; d++) {

					if (d == drawNumber) {

						if (a < 3) {
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
			Novice::DrawQuad(1095 + 32, 64, 1143 + 32, 64, 1095 + 32, 112, 1143 + 32, 112, 0, 0, 64, 64, REDDOT, 0xFFFFFFFF);

			//スピード
			Novice::DrawQuad(888, 48, 1048, 48, 888, 80, 1048, 80, 0, 0, 320, 64, MAXSPEED, 0xFFFFFFFF);

			//スピードの表示
			for (int a = 0; a < 5; a++) {

				divideNumber = 1;

				for (int b = 0; b < 5; b++) {
					divideNumber *= 10;
				}

				for (int c = 0; c < a; c++) {
					divideNumber /= 10;
				}

				drawNumber = AbsoluteValue(drawMaxSpeed) / divideNumber;

				for (int d = 0; d < 10; d++) {

					if (d == drawNumber) {

						if (a < 3) {
							Novice::DrawQuad(1032 + a * 32, 32, 1096 + a * 32, 32, 1032 + a * 32, 96, 1096 + a * 32, 96, 0, 0, 64, 64, REDNUM[d], 0xFFFFFFFF);
						}
						else {
							Novice::DrawQuad(1048 + a * 32, 32, 1112 + a * 32, 32, 1048 + a * 32, 96, 1112 + a * 32, 96, 0, 0, 64, 64, REDNUM[d], 0xFFFFFFFF);
						}

					}

				}

				drawMaxSpeed = AbsoluteValue(drawMaxSpeed) % divideNumber;

			}

			//ESCBACK
			if (isGoal == false) {
				Novice::DrawSprite(10, 680, ESCBACK, 0.5f, 0.5f, 0, 0xFFFFFFFF);
			}

			//ゴールしたら
			if (isGoal == true) {

				Novice::DrawQuad(640 - 256, 200, 640 + 256, 200, 640 - 256, 200 + 128, 640 + 256, 200 + 128, 0, 0, goalW, 128, GOALTEXT, 0xFFFFFFFF);

				if (drawGoalTimer < 40) {
					Novice::DrawSprite(640 - 256, 600, SPACESELECT, 1, 1, 0, 0xFFFFFFFF);
				}

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
