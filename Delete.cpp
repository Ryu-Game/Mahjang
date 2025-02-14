/***********************
* 河処理
************************/
#include "Delete.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#define PI    3.14159265358979323846264

Delete mDelete;

/***********************
* 初期処理
************************/
void Delete::Delete_Initialize() {
	//河表示初期化
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		for (int i = 0; i < 50; i++) {
			mDelete.House[num][i] = 0;
		}
		mDelete.River[num] = 0;
		mDelete.ImgRiver[num] = 0;
	}

	//座標処理初期化
	for (int num = 0; num < 4; num++) {
		//X座標処理
		for (int i = 0; i < 6; i++) {
			switch (num) {
			case 0:	//X座標
				mDelete.x[num][i] = mDelete.InitiaX[0] + mDelete.size_x * i;
				break;
			case 1:	//Y座標
				mDelete.x[num][i] = mDelete.InitiaY[1] + mDelete.size_x * i;
				break;
			case 2:	//X座標
				mDelete.x[num][i] = mDelete.InitiaX[1] - mDelete.size_x * i;
				break;
			case 3:	//Y座標
				mDelete.x[num][i] = mDelete.InitiaY[0] - mDelete.size_x * i;
				break;
			}
		}
		//Y座標処理
		for (int i = 0; i < 4; i++) {
			switch (num) {
			case 0:	//Y座標
				mDelete.y[num][i] = mDelete.InitiaY[0] + mDelete.size_y * i;
				break;
			case 1:	//X座標
				mDelete.y[num][i] = mDelete.InitiaX[0] - mDelete.size_y * i;
				break;
			case 2:	//Y座標
				mDelete.y[num][i] = mDelete.InitiaY[1] - mDelete.size_y * i;
				break;
			case 3:	//X座標
				mDelete.y[num][i] = mDelete.InitiaX[1] + mDelete.size_y * i;
				break;
			}
		}
	}
}

/***********************
* 更新処理（ゲーム時ループし続ける）
************************/
void Delete::Delete_Update() {
	if (mDelete.ChangeSwitch == true) {

		//Playerが4以上になったらリセット
		if (mPlayer.GetPlayer > 4) {
			mPlayer.GetPlayer = 0;
		}
		mDelete.House[mPlayer.GetPlayer][mDelete.River[mPlayer.GetPlayer]] = mDelete.image;

		mDelete.River[mPlayer.GetPlayer]++;
		mPlayer.GetPlayer++;
		mDelete.ChangeSwitch = false;
	}
}

/***********************
* 描画処理
************************/
void Delete::Delete_Draw() {
	//描画ループする
	for (int num = 0; num < 4; num++) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 6; x++) {
				switch (num) {
				case 0:
					DrawRotaGraph(mDelete.x[num][x], mDelete.y[num][y], mDelete.size, PI / 90.0, mDelete.House[num][mDelete.ImgRiver[num]], false);
					mDelete.ImgRiver[num]++;
					break;
				case 1:
					DrawRotaGraph(mDelete.y[num][y], mDelete.x[num][x], mDelete.size, PI / 2, mDelete.House[num][mDelete.ImgRiver[num]], false);
					mDelete.ImgRiver[num]++;
					break;
				case 2:
					DrawRotaGraph(mDelete.x[num][x], mDelete.y[num][y], mDelete.size, PI, mDelete.House[num][mDelete.ImgRiver[num]], false);
					mDelete.ImgRiver[num]++;
					break;
				case 3:
					DrawRotaGraph(mDelete.y[num][y], mDelete.x[num][x], mDelete.size, -(PI / 2), mDelete.House[num][mDelete.ImgRiver[num]], false);
					mDelete.ImgRiver[num]++;
					break;
				}
			}
		}
	}
	for (int num = 0; num < 4; num++) {
		mDelete.ImgRiver[num] = 0;
	}
}