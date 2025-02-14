#include "DxLib.h"
#include "Game.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Dealing.h"
#include "Mounten.h"
#include "Player.h"
#include "Delete.h"

Game mGame;

/******************************
* 初期処理
*******************************/
void Game_Initialize() {
	//親を決める
	mGame.King = 0;
	//mGame.King = GetRand(3);	//ランダムで親を決める
	//Player初期ポイント
	for (int i = 0; i < 4; i++) {
		mGame.PlayerPoint[i] = 25,000;
	}
	mGame.Start = true;
	mGame.timecount = 0;
	mGame.count = 0;
}

/******************************
* 終了処理
*******************************/
void Game_Finalize() {

}

/******************************
* 更新処理
*******************************/
void Game_Update() {
	//ゲーム開始処理
	if (mGame.Start == true) {
		//双六でどこから区切るかを決める
		//mGame.Sugoroku = GetRand(10);
		//mGame.Sugoroku += 2;
		mGame.Sugoroku = 7;
		mMounten.Mounten_Initialize();
		mPlayer.Player_Initialize();
		mDelete.Delete_Initialize();

		mGame.Start = false;
	}
	//ゲーム終了処理
	else if (mGame.Start == false) {
		mMounten.Mounten_Update();
		GetMousePoint(&iMouseX, &iMouseY);	//ゲーム処理でマウス座標を取得する
		mPlayer.Player_Update();
		mDelete.Delete_Update();
	}
	unsigned int Cr;
	int moji = 0;
	Cr = GetColor(255, 255, 255);
	mGame.timecount++;
	if (mGame.timecount % 60 == 0) {
		mGame.count++;
	}
	DrawFormatString(0, 20 * moji, Cr, "%d", mGame.count);
	//Escキーで強制終了
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		DxLib_End();
	}
}

/******************************
* 描画処理
*******************************/
void Game_Draw() {

	mMounten.Mounten_Draw();
	mPlayer.Player_Draw();
	mDelete.Delete_Draw();
}