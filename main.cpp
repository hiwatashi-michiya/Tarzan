#include <Novice.h>
#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"
#include "Floor.h"

const char kWindowTitle[] = "Wild Tarzan";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int scrollX = 0;

	int BGTITLE = Novice::LoadTexture("./Resources/Images/TarzanBG.png");
	int BGSELECT = Novice::LoadTexture("./Resources/Images/TarzanBG_SELECT.png");
	int ACCELFLOOR = Novice::LoadTexture("./Resources/Images/accel.png");
	int DECELFLOOR = Novice::LoadTexture("./Resources/Images/decel.png");
	int FLOOR = Novice::LoadTexture("./Resources/Images/floor.png");

	Player player({ 150.0f, 200.0f }, { 0.0f, 0.0f }, 10.0f, { 100.0f + 250.0f, 200.0f },
		0xFFFFFFFF, false, TARZAN_GAGE, 0, 0, false, 0);

	Wall wall[WALL_NUMBER];
	wall[0] = Wall({ 1000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[1] = Wall({ 4000.0f,0.0f }, 200, 720, 20.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[2] = Wall({ 9000.0f,0.0f }, 200, 720, 25.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[3] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[4] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[5] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[6] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[7] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[8] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);
	wall[9] = Wall({ 100000.0f,0.0f }, 200, 720, 15.0f, true, BREAK, 0xFFFFFFFF, player);

	Floor floor[FLOOR_NUMBER];
	for (int i = 0; i < FLOOR_NUMBER; i++) {

		if (i % 3 == 0) {
			floor[i] = Floor(1000 * (i + 1), (680 - (i * 60.0f)), 5000, 10, NORMAL, 5000, 10, 256, 64, BGSELECT, player);
		}

		if (i % 3 == 1) {
			floor[i] = Floor(1000 * (i + 1), (680 - (i * 60.0f)), 5000, 10, PLAYERACCEL, 5000, 10, 256, 64, ACCELFLOOR, player);
		}

		if (i % 3 == 2) {
			floor[i] = Floor(1000 * (i + 1), (680 - (i * 60.0f)), 5000, 10, PLAYERDECEL, 5000, 10, 256, 64, DECELFLOOR, player);
		}

		if (i > 2) {
			floor[i] = Floor(1000 * (i + 1), (680 - (i * 60.0f)), 0, 0, NORMAL, 0, 0, 256, 64, ACCELFLOOR, player);
		}

	}

	Floor ceiling[FLOOR_NUMBER];

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

				player.Update(&scrollX);

				for (int i = 0; i < FLOOR_NUMBER; i++) {
					floor[i].Update(scrollX);
					/*ceiling[i].Update(scrollX);*/
				}
				

				for (int i = 0; i < WALL_NUMBER; i++) {
					wall[i].Update(scrollX);
				}

			}

			if (player.getPosX() > goalLine) {
				isGoal = true;
			}
			

			///
			/// ↑更新処理ここまで
			///

			

			///
			/// ↓描画処理ここから
			///

			player.Draw(scrollX);

			for (int i = 0; i < FLOOR_NUMBER; i++) {
				floor[i].Draw(scrollX);
				/*ceiling[i].Draw(scrollX);*/
			}

			for (int i = 0; i < WALL_NUMBER; i++) {
				wall[i].Draw(scrollX);
			}

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
