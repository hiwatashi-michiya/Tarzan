#include <Novice.h>
#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "Scene.h"
#include "Key.h"

const char kWindowTitle[] = "Wild Tarzan";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Player player({ 200.0f, 200.0f }, { 0.0f, 0.0f }, 10.0f, { 100.0f + 250.0f, 200.0f }, 0xFFFFFFFF, false, TARZAN_GAGE, 0, 0, false);

	Wall wall({ 1000.0f,0.0f }, 720.0f, 20.0f, true, 0xFFFFFFFF, player);

	int scrollX = 0;

	int BGTITLE = Novice::LoadTexture("./Resources/Images/TarzanBG.png");
	int BGSELECT = Novice::LoadTexture("./Resources/Images/TarzanBG_SELECT.png");


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

			if (Key::IsTrigger(DIK_SPACE)) {
				scene = STAGESELECT;
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

			if (Key::IsTrigger(DIK_SPACE)) {
				scene = GAMEPLAY;
			}

			if (Key::IsTrigger(DIK_ESCAPE)) {
				scene = TITLE;
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

			if (Key::IsTrigger(DIK_ESCAPE)) {
				scene = STAGESELECT;
			}

			player.Update(&scrollX);

			wall.Update(scrollX);

			///
			/// ↑更新処理ここまで
			///

			

			///
			/// ↓描画処理ここから
			///

			player.Draw(scrollX);

			wall.Draw(scrollX);

			///
			/// ↑描画処理ここまで
			///

			break;

		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE) && scene == TITLE) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
