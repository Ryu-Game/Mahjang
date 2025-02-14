#include "Mounten.h"
#include "DxLib.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Dealing.h"

#define PI    3.14159265358979323846264

Mounten mMounten;
/******************************
* 初期処理
*******************************/
void Mounten::Mounten_Initialize() {
	mDealing.Dealing_Initialize();

	//牌初期化処理
	for (int kind = mMounten.mKind - 1; kind > 0; kind--) {
		if (kind > mDealing.SangenNumber) {			//三元牌
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Sangen, mDealing.SangenNumber);
			}
		}
		else if (kind > mDealing.DirectionNumber) {	//四風牌
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Direction, mDealing.DirectionNumber);
			}
		}
		else if (kind > mDealing.SousNumber) {		//索子
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Sous, mDealing.SousNumber);
			}
		}
		else if (kind > mDealing.PinsNumber) {		//筒子
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Pins, mDealing.PinsNumber);
			}
		}
		else if (kind >= mDealing.MansNumber) {		//萬子
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Mans, mDealing.MansNumber);
			}
		}
	}
	//画像初期化処理
	for (int tile = 0; tile < mMounten.Mnumber; tile++) {
		mMounten.AllImage[tile] = mDealing.Mounimage;
	}

	//牌をばらばらにする
	//Shuffle();

	//山牌並べる変数初期化
	mMounten.IniMoun = 0;
	//描画画像変数初期化
	mMounten.NumImage = 0;
}

/******************************
* 更新処理
*******************************/
void Mounten::Mounten_Update() {
	unsigned int Cr;
	int moji = 0;
	Cr = GetColor(255, 255, 255);
	/*for (int i = 0; i < mMounten.Mnumber; i++) {
		if (mMounten.AllImage[i] != mDealing.Mounimage) {
			DrawFormatString(0, 20 * moji, Cr, "%d", i);
			moji++;
			DrawFormatString(0, 20 * moji, Cr, "%d", mMounten.Alltiles[i]);
			moji++;

		}
	}*/


	/*Cr = GetColor(0, 0, 255);
	for (int i = 0; i < mMounten.Mnumber; i++) {
		for (int j = i + 1; i < mMounten.Mnumber; j++) {
			if (mMounten.Alltiles[i] == mMounten.Alltiles[j]) {
				DrawFormatString(0, 20 * moji, Cr, "%d", i);
				moji++;
			}
		}
	}*/
}

/******************************
* 描画処理
*******************************/
void Mounten::Mounten_Draw() {
	for (int tile = 0; tile < mMounten.Mnumber; tile++) {
		//次の開始位置
		//*1山出来たら次に移動
		if (tile % (mMounten.Width * mMounten.Height) == 0) {
			if (tile != 0) {
				mMounten.IniMoun++;
			}
		}

		//座標処理
		mMounten.Position(tile);

		//画像処理
		DrawRotaGraph(mMounten.PositionX, mMounten.PositionY, mMounten.Size, mMounten.Rotate, mMounten.AllImage[mMounten.NumImage], false);
	}

	//ずっと出すために初期値に戻す
	mMounten.IniMoun = 0;	
}

/******************************
* 関数処理
*******************************/
//山の座標処理
void Mounten::Position(int tile) {
	switch (mMounten.IniMoun) {
	case 0:	//自家
		mMounten.PositionX = mMounten.NumInitiaX[0] - (mMounten.SizeNum * (tile / mMounten.Height));
		//段差処理
		if (tile % 2 != 0) {	//奇数
			mMounten.PositionY = mgr.SCREEN_HEIGHT - mMounten.InitiaY;
			mMounten.NumImage = --tile;
		}
		else {					//偶数
			mMounten.PositionY = mgr.SCREEN_HEIGHT - mMounten.InitiaY - mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = PI * 2;
		break;

	case 1:	//上家
		mMounten.PositionY = mMounten.NumInitiaY[0] - (mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width));
		//段差処理
		if (tile % 2 != 0) {	//上段
			mMounten.PositionX = mgr.SCREEN_WIDTH - mMounten.InitiaX;
			mMounten.NumImage = --tile;
		}
		else {					//下段
			mMounten.PositionX = mgr.SCREEN_WIDTH - mMounten.InitiaX + mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = PI / 2;
		break;

	case 2:	//対面
		mMounten.PositionX = mMounten.NumInitiaX[1] + (mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width));
		//段差処理
		if (tile % 2 != 0) {	//上段
			mMounten.PositionY = mMounten.InitiaY;
			mMounten.NumImage = --tile;
		}
		else {					//下段
			mMounten.PositionY = mMounten.InitiaY + mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = -PI;
		break;

	case 3:	//下家
		mMounten.PositionY = mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width) + mMounten.NumInitiaY[1];
		//段差処理
		if (tile % 2 != 0) {	//上段
			mMounten.PositionX = mMounten.InitiaX;
			mMounten.NumImage = --tile;
		}
		else {					//下段
			mMounten.PositionX = mMounten.InitiaX - mMounten.Step;
			mMounten.NumImage = ++tile;
		}
		mMounten.Rotate = -(PI / 2);
		break;
	}
}

//牌の初期化処理
void Mounten::InitiaComp(int kind, int tile, int DataHouse[], int number) {
	mMounten.Alltiles[kind * 4 + tile] = DataHouse[kind - number];
}

//シャッフル処理
void Mounten::Shuffle() {
	int tmp, image;	//元の変数値格納
	int rand;		//ランダム数値格納

	unsigned int Cr;
	int moji = 0;
	Cr = GetColor(255, 255, 255);

	//配列を入れ替え
	for (int i = mMounten.Mnumber - 1; i > 0; i--) {
		//ランダム取得
		rand = GetRand(mMounten.Mnumber - 1);

		//配列にランダムを格納
		tmp = mMounten.Alltiles[rand];
		mMounten.Alltiles[rand] = mMounten.Alltiles[i];
		mMounten.Alltiles[i] = tmp;

		//画像格納
		image = mMounten.AllImage[rand];
		mMounten.AllImage[rand] = mMounten.AllImage[i];
		mMounten.AllImage[i] = image;
	}
}