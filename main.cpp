#include <Novice.h>
#include "Map.h"
#include "Player.h"
#include "Wall.h"

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


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player.Update(&scrollX);

		wall.Update(scrollX);

		///
		/// ↑更新処理ここまで
		///

		player.Draw(scrollX);

		wall.Draw(scrollX);

		///
		/// ↓描画処理ここから
		///

		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
