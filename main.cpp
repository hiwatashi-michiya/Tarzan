#include <Novice.h>
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"
#include "Floor.h"
#include "Stage.h"

const char kWindowTitle[] = "Wild Tarzan";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// スクロール値
	Vec2 scroll = { 0,0 };

	//ステージ選択の変数
	int stageSelect = 1;

	//X軸の画像表示の繰り返し回数
	const int REPETITION_X = 32;

	//Y軸の画像表示の繰り返し回数
	const int REPETITION_Y = 4;

	int BGTITLE = Novice::LoadTexture("./Resources/Images/TarzanBG.png");
	int BGSELECT = Novice::LoadTexture("./Resources/Images/TarzanBG_SELECT.png");
	int ACCELFLOOR = Novice::LoadTexture("./Resources/Images/accel.png");
	int DECELFLOOR = Novice::LoadTexture("./Resources/Images/decel.png");
	int UNBREAKWALL = Novice::LoadTexture("./Resources/Images/wall.png");
	int BREAKWALL = Novice::LoadTexture("./Resources/Images/wallbreak.png");
	int GROUND = Novice::LoadTexture("./Resources/Images/ground.png");
	int NORMALFLOOR = Novice::LoadTexture("./Resources/Images/normalfloor.png");
	int CEILINGFLOOR = Novice::LoadTexture("./Resources/Images/ceiling.png");
	int STAGECEILING = Novice::LoadTexture("./Resources/Images/stageceiling.png");
	int INGAMEBG = Novice::LoadTexture("./Resources/Images/ingameBG1.png");
	int UI = Novice::LoadTexture("./Resources/Images/UIsheet.png");
	int GAGE = Novice::LoadTexture("./Resources/Images/gage.png");
	int BACKGAGE = Novice::LoadTexture("./Resources/Images/backgage.png");

	float posX = 200.0f;
	float posY = 200.0f;
	float velocityX = 0.0f;

	Player player({ posX, posY }, { velocityX, 0.0f }, { 100.0f + 250.0f, 200.0f },
		0xFFFFFFFF, false, TARZAN_GAGE, 0, 0, false, 0,BGTITLE);

	Wall wall[STAGE_NUMBER][WALL_NUMBER];
	for (int a = 0; a < STAGE_NUMBER; a++) {

		for (int b = 0; b < WALL_NUMBER; b++) {
			wall[a][b] = Wall({ -10000.0f,-10000.0f }, 0.0f, 0.0f, 100.0f, false, UNBREAK, 0xFFFFFFFF, player, UNBREAKWALL);
		}

	}
	//ステージ1
	wall[1][0] = Wall({ 100.0f,690.0f }, 51200, 64, 15.0f, true, UNBREAK, 0xFFFFFFFF, player,GROUND);
	wall[1][1] = Wall({ 4000.0f,590.0f }, 256, 256, 20.0f, true, UNBREAK, 0xFFFFFFFF, player,UNBREAKWALL);
	wall[1][2] = Wall({ 5000.0f,-344.0f }, 256, 1024, 15.0f, true, BREAK, 0xFFFFFFFF, player,BREAKWALL);
	wall[1][3] = Wall({ 9000.0f,-344.0f }, 256, 1024, 20.0f, true, BREAK, 0xFFFFFFFF, player,BREAKWALL);
	wall[1][4] = Wall({ 12000.0f,-344.0f }, 256, 1024, 25.0f, true, BREAK, 0xFFFFFFFF, player,BREAKWALL);
	wall[1][5] = Wall({ 14000.0f,-344.0f }, 256, 704, 15.0f, true, UNBREAK, 0xFFFFFFFF, player,UNBREAKWALL);
	wall[1][6] = Wall({ 17000.0f,424.0f }, 512, 256, 35.0f, true, BREAK, 0xFFFFFFFF, player,BREAKWALL);
	wall[1][7] = Wall({ 20000.0f,-344.0f }, 256, 824, 15.0f, true, UNBREAK, 0xFFFFFFFF, player,UNBREAKWALL);
	wall[1][8] = Wall({ 23000.0f,-344.0f }, 256, 1024, 30.0f, true, BREAK, 0xFFFFFFFF, player,BREAKWALL);
	wall[1][9] = Wall({ -100.0f,-300.0f }, 256, 1024, 15.0f, true, UNBREAK, 0xFFFFFFFF, player,UNBREAKWALL);



	Floor floor[STAGE_NUMBER][FLOOR_NUMBER];

	//初期化
	for (int a = 0; a < STAGE_NUMBER; a++) {
		for (int b = 0; b < FLOOR_NUMBER; b++) {
			floor[a][b] = Floor(-10000, -10000, 0, 0, NORMAL, 0, 0, 64, 64, NORMALFLOOR, player);
		}
	}

	//ステージ1
	floor[1][0] = Floor(100, 680, 28000, 10, NORMAL, 28000, 10, 64, 64, NORMALFLOOR, player);
	floor[1][1] = Floor(4000, 580, 256, 10, PLAYERACCEL, 256, 10, 64, 64, ACCELFLOOR, player);
	floor[1][2] = Floor(6000, 480, 4000, 10, NORMAL, 4000, 10, 64, 64, NORMALFLOOR, player);
	floor[1][3] = Floor(7000, 230, 2000, 10, PLAYERACCEL, 2000, 10, 64, 64, ACCELFLOOR, player);
	floor[1][4] = Floor(14000, 360, 256, 10, CEILING, 256, 10, 64, 64, CEILINGFLOOR, player);
	floor[1][5] = Floor(20500, 380, 4700, 10, PLAYERACCEL, 4700, 10, 64, 64, ACCELFLOOR, player);
	floor[1][6] = Floor(17000, 404, 512, 20, NORMAL, 512, 20, 64, 64, NORMALFLOOR, player);
	floor[1][7] = Floor(6000, 680, 3000, 10, PLAYERDECEL, 3000, 10, 64, 64, DECELFLOOR, player);
	floor[1][8] = Floor(15000, 300, 1400, 10, NORMAL, 1400, 10, 64, 64, NORMALFLOOR, player);
	floor[1][9] = Floor(20000, 480, 256, 10, CEILING, 256, 10, 64, 64, CEILINGFLOOR, player);
	floor[1][10] = Floor(0, -1440, 28000, 1096, CEILING, 28000, 1096, 64, 64, STAGECEILING, player);

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

				if (nextScene == TITLE) {

					if (sceneCount > 0) {
						sceneCount -= 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
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

				if (nextScene == STAGESELECT) {
					
					if (sceneCount > 0) {
						sceneCount -= 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
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

			///
			/// ↑描画処理ここまで
			///

			break;

		case GAMEPLAY:

			///
			/// ↓更新処理ここから
			///

			if (sceneChange == true && isGoal == false) {

				if (nextScene == GAMEPLAY) {

					if (sceneCount > 0) {
						sceneCount -= 1;
						clearly = 0x0000000F + sceneCount * 4;
					}

					if (sceneCount == 0) {
						sceneChange = false;
					}

				}
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
			else if(isGoal == true) {

				if (sceneChange == false) {

					if (sceneCount < 30) {
						sceneCount += 1;
						clearly = 0x0000000F + sceneCount * 2;
					}

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
			else if (sceneChange == false && isGoal == false) {

				if (Key::IsTrigger(DIK_ESCAPE)) {
					sceneChange = true;
					nextScene = STAGESELECT;
				}

				player.Update(&scroll);

				for (int i = 0; i < FLOOR_NUMBER; i++) {
					floor[stageSelect][i].Update(scroll);
				}
				

				for (int i = 0; i < WALL_NUMBER; i++) {
					wall[stageSelect][i].Update(scroll);
				}

			}

			if (player.getPosX() > GOAL_LINE[0]) {
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
					Novice::DrawQuad(WINDOW_WIDTH* x - scroll.x, -WINDOW_HEIGHT * y - scroll.y,
						WINDOW_WIDTH* x + WINDOW_WIDTH - scroll.x, -WINDOW_HEIGHT * y - scroll.y,
						WINDOW_WIDTH* x - scroll.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y,
						WINDOW_WIDTH* x + WINDOW_WIDTH - scroll.x, -WINDOW_HEIGHT * y + WINDOW_HEIGHT - scroll.y,
						0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, INGAMEBG, 0x888888FF);
				}

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

			Novice::DrawQuad(640 - 256 - 4, 84 - 4, (640 - 256) + 512 + 4, 84 - 4,
				640 - 256 - 4,116 + 4, (640 - 256) + 512 + 4, 116 + 4,
				0, 0, 512, 64, BACKGAGE, 0xFFFFFFFF);

			Novice::DrawQuad(640 - 256, 84, (640 - 256) + (player.getTarzanGage() * 512) / TARZAN_GAGE, 84,
				640 - 256, 116, (640 - 256) + (player.getTarzanGage() * 512) / TARZAN_GAGE, 116,
				0, 0, (player.getTarzanGage() * 512) / TARZAN_GAGE, 64, GAGE, 0xFFFFFFFF);

			///
			/// ↑描画処理ここまで
			///

			break;

		}

		if (sceneChange == true || isGoal == true) {

			Novice::DrawBox(0, 0, 1280, 720, 0, clearly, kFillModeSolid);

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
