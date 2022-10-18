#pragma once

enum Scene {
	TITLE,
	STAGESELECT,
	GAMEPLAY
};

//現在のシーン
Scene scene = GAMEPLAY;

//次のシーン
Scene nextScene = GAMEPLAY;

//シーン切り替えに入るかどうか
bool sceneChange = false;

//切り替え時のカウント
int sceneCount = 0;

//透明度変化
int clearly = 0x0000000F + sceneCount * 4;

//ゴール判定
bool isGoal = false;

//ゴールライン
int goalLine = 25600;
