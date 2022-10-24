#include <Novice.h>
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"
#include "Floor.h"
#include "Stage.h"
#include "Calc.h"

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
	int stageSelect = 1;

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

	int TARZAN = Novice::LoadTexture("./Resources/Images/Player/playerRun.png");

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


#pragma endregion

	//ターザンゲージ
	int GAGE = Novice::LoadTexture("./Resources/Images/UI/gage.png");
	int BACKGAGE = Novice::LoadTexture("./Resources/Images/UI/backgage.png");

	//スピードテキスト
	int SPEED = Novice::LoadTexture("./Resources/Images/UI/speed.png");

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

	float posX = 200.0f;
	float posY = 200.0f;
	float velocityX = 0.0f;

	Player player({ posX, posY }, { velocityX, 0.0f }, { 100.0f + 250.0f, 200.0f },
		0xFFFFFFFF, false, TARZAN_GAGE, 0, 0, false, 0, TARZAN, 0);

	//壁の生成

	Wall wall[STAGE_NUMBER][WALL_NUMBER];
	for (int a = 0; a < STAGE_NUMBER; a++) {

		for (int b = 0; b < WALL_NUMBER; b++) {
			wall[a][b] = Wall({ -10000.0f,-10000.0f }, 0.0f, 0.0f, 100.0f, false, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
		}

	}
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
	wall[1][9] = Wall({ -100.0f,-300.0f }, 256, 1024, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][10] = Wall({ 500.0f,600.0f }, 256, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	wall[1][11] = Wall({ 2000.0f,550.0f }, 256, 300, 15.0f, true, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
	//

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
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < 60) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 60) {

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
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < 60) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 60) {

						scene = nextScene;

					}

				}

			}
			else if (sceneChange == false) {

				if (Key::IsTrigger(DIK_UP) && stageSelect > 1) {
					stageSelect -= 1;
				}

				if (Key::IsTrigger(DIK_DOWN) && stageSelect < 5) {
					stageSelect += 1;
				}

				if (Key::IsTrigger(DIK_SPACE)) {
					sceneChange = true;

					//クリア済みだった場合フラグを元に戻す
					if (isGoal == true) {
						isGoal = false;
					}

					isLoading = 0;
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
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
				//フェードアウト
				else {

					if (sceneCount < 60) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 60) {

						scene = nextScene;

					}

				}

			}
			//ゴールしたら
			else if (isGoal == true) {

				//リザルト表示
				if (sceneChange == false) {

					if (sceneCount < 30) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 2;
					}

					//キー入力でシーンチェンジを有効にする
					if (sceneCount == 30) {

						if (Key::IsTrigger(DIK_RETURN)) {
							sceneChange = true;
							nextScene = STAGESELECT;
						}

					}

				}
				else {

					if (sceneCount < 60) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 2;
					}

					if (sceneCount == 60) {
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

				if (drawTimer % 12 == 0) {

					player.MoveDrawX();

					if (drawTimer >= 60) {
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


			}

			drawSpeed = player.getSpeedX() * 1000;

			if (player.getPosX() > GOAL_LINE[stageSelect]) {
				isGoal = true;
			}


			///
			/// ↑更新処理ここまで
			///



			///
			/// ↓描画処理ここから
			///

			for (int y = 0; y < REPETITION_Y; y++) {

				for (int x = 0; x < REPETITION_X; x++) {
					Novice::DrawQuad(WINDOW_WIDTH * x - scroll.x, -WINDOW_HEIGHT * y - scroll.y,
						WINDOW_WIDTH * x + WINDOW_WIDTH - scroll.x, -WINDOW_HEIGHT * y - scroll.y,
						WINDOW_WIDTH * x - scroll.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y,
						WINDOW_WIDTH * x + WINDOW_WIDTH - scroll.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y,
						0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, INGAMEBG, 0x888888FF);
				}

			}

			if (stageSelect == 1) {
				
				Novice::DrawQuad(500 - scroll.x, 400 - scroll.y, 756 - scroll.x, 400 - scroll.y,
					500 - scroll.x, 656 - scroll.y, 756 - scroll.x, 656 - scroll.y, 0, 0, 256, 256, PRESSINFO, 0xFFFFFFFF);

				Novice::DrawQuad(4700 - scroll.x, 450 - scroll.y, 4956 - scroll.x, 450 - scroll.y,
					4700 - scroll.x, 706 - scroll.y, 4956 - scroll.x, 706 - scroll.y, 0, 0, 256, 256, BREAKINFO, 0xFFFFFFFF);

				Novice::DrawQuad(6000 - scroll.x, 450 - scroll.y, 6256 - scroll.x, 450 - scroll.y,
					6000 - scroll.x, 706 - scroll.y, 6256 - scroll.x, 706 - scroll.y, 0, 0, 256, 256, SLOWINFO, 0xFFFFFFFF);

				Novice::DrawQuad(7000 - scroll.x, -16 - scroll.y, 7256 - scroll.x, -16 - scroll.y,
					7000 - scroll.x, 240 - scroll.y, 7256 - scroll.x, 240 - scroll.y, 0, 0, 256, 256, FASTINFO, 0xFFFFFFFF);

			}

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

			///
			/// ↑描画処理ここまで
			///

			break;

		}

		if (isGoal == true) {

			Novice::DrawBox(0, 0, 1280, 720, 0, clearly, kFillModeSolid);

		}

		if (sceneChange == true) {

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
