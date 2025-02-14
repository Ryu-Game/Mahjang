#include <DxLib.h>
#include "Player.h"
#include "Mounten.h"
#include "Dealing.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Input.h"
#include "Delete.h"
#define PI    3.14159265358979323846264

Player mPlayer;

/**************************
* 初期化処理
***************************/
void Player::Player_Initialize() {
	SetFontSize(20);
	//αで親から引くようにする(プロトは自家から引いている)

	//最初引く人
	mPlayer.GetPlayer = mGame.King;

	//位置情報初期化
	mPlayer.PlayerTrans();

	//Y座標をPlayer情報に戻す
	mPlayer.TransY = mgr.SCREEN_HEIGHT - mPlayer.NumY;

	//Player変数初期化
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		for (int tile = 0; tile < mPlayer.MaxTile; tile++) {
			mPlayer.Player[num][tile] = 0;
		}
	}

	//最初の取得情報格納
	mPlayer.Get = mGame.Sugoroku * 2;
	//3牌配るを4回繰り返す
	for (int four = 0; four < 4; four++) {					//4回繰り返す
		for (int num = 0; num < mGame.MaxPlayer; num++) {	//人数分
			for (int count = 0; count < 3; count++) {		//3牌配る
				//数値を取得
				mPlayer.Player[num][count + four * 3] = mMounten.Alltiles[mPlayer.Get];
				//配ったら消す
				mMounten.Alltiles[mPlayer.Get] = -1;
				mMounten.AllImage[mPlayer.Get] = 0;
				mPlayer.Get++;
			}
		}
	}
	//最後に1枚ずつとる
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		mPlayer.Player[num][12] = mMounten.Alltiles[mPlayer.Get];
		//取得したら消す
		mMounten.Alltiles[mPlayer.Get] = -1;
		mMounten.AllImage[mPlayer.Get] = 0;
		mPlayer.Get++;
	}
}

/**************************
* 更新処理
***************************/
void Player::Player_Update() {
	//牌の取得処理
	switch (mPlayer.GetPlayer) {
	case 0:
	case 1:
	case 2:
	case 3:
		mPlayer.Player[mPlayer.GetPlayer][13] = mMounten.Alltiles[mPlayer.Get];
		//取得したら消す
		mMounten.Alltiles[mPlayer.Get] = -1;
		mMounten.AllImage[mPlayer.Get] = 0;
		break;
	}

	//マウス座標
	if (mPlayer.GetPlayer == 0) {
		//牌とマウスの重なり
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			mPlayer.TileHit(i);
			
			//マウスカーソル
			if (mPlayer.sx1 <= iMouseX && mPlayer.sx2 >= iMouseX && mPlayer.sy1 <= iMouseY && mPlayer.sy2 >= iMouseY) {
				mPlayer.Check = i;
				mPlayer.y[mPlayer.GetPlayer][mPlayer.Check] = mPlayer.TransY - 20;
			}
		}
		//牌とマウスが重なっていない時戻す
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			if (i != mPlayer.Check) {
				mPlayer.y[0][i] = mPlayer.TransY;
			}
		}
	}

	//とったら捨てる処理
	switch (mPlayer.GetPlayer) {
	case 0:
		  if (iKeyFlg & MOUSE_INPUT_LEFT) {
			  mDelete.image = mPlayer.Image[mPlayer.GetPlayer][mPlayer.Check];
			  mPlayer.Player[mPlayer.GetPlayer][mPlayer.Check] = mPlayer.Player[mPlayer.GetPlayer][13];
			  mPlayer.Player[0][13] = -1;
			  mDelete.ChangeSwitch = true;
			  mPlayer.Get++;
			  mPlayer.Del_count++;
		  }
		  break;
	case 1:
	case 2:
	case 3:
		//if (mPlayer.Change[mPlayer.GetPlayer - 1] == true) {
			mDelete.image = mPlayer.Image[mPlayer.GetPlayer][13];
			mPlayer.Player[mPlayer.GetPlayer][13] = -1;
			mDelete.ChangeSwitch = true;
			mPlayer.Get++;
			mPlayer.Del_count++;
			mPlayer.GetPlayer++;
			if (mPlayer.GetPlayer == 4) {
				mPlayer.GetPlayer = 0;
			}
		//}
		//else if (mPlayer.Change[mPlayer.GetPlayer - 1] == false) {
		//	mPlayer.Change[mPlayer.GetPlayer - 1] = true;
		//}
			break;
	}
}
/**************************
* 描画処理
***************************/
void Player::Player_Draw() {
	//画像格納
	for (int Num = 0; Num < mGame.MaxPlayer; Num++) {
		for (int tile = 0; tile < mPlayer.MaxTile; tile++) {
			mPlayer.Image_Storage(Num, tile);
		}
	}

	//手配描画処理
	for (int n = 0; n < mGame.MaxPlayer; n++) {
		for (int i = 0; i < 13; i++) {
			switch (n) {
			case 0:	//自家
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[0], PI / 90.0, mPlayer.Image[n][i], false);
				break;
			case 1:	//下家
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], PI / 2, mPlayer.Image[n][i], false);
				break;
			case 2:	//対面
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], PI, mPlayer.Image[n][i], false);
				break;
			case 3:	//上家
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], -(PI / 2), mPlayer.Image[n][i], false);
				break;
			}
		}
	}

	switch (mPlayer.GetPlayer) {
	case 0:
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[0], PI / 90.0, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 1:	//下家
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], PI / 2, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 2:	//対面
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], PI, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 3:	//上家
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], -(PI / 2), mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	}
}

/**************************
* 関数処理
***************************/
//画像格納処理
void Player::Image_Storage(int num, int tile) {
	//三元牌
	if (mDealing.SangenNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 3; j++) {
			if (mDealing.Sangen[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Saimage[j];
				break;
			}
		}
	}
	//四風牌
	else if (mDealing.DirectionNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 4; j++) {
			if (mDealing.Direction[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Dimage[j];
				break;
			}
		}
	}
	//索子
	else if (mDealing.SousNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Sous[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Simage[j];
				break;
			}
		}
	}
	//筒子
	else if (mDealing.PinsNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Pins[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Pimage[j];
				break;
			}
		}
	}
	//萬子
	else if (mDealing.MansNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Mans[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Mimage[j];
				break;
			}
		}

	}
}

//座標処理
void Player::PlayerTrans() {
	//Player位置情報(当たり判定＆描画座標)
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		//各Playerの初期座標
		switch (num) {
		case 0:
			mPlayer.TransX = mPlayer.InitiaX[0];
			mPlayer.TransY = mgr.SCREEN_HEIGHT - mPlayer.NumY;
			break;
		case 1:
			mPlayer.TransX = mgr.SCREEN_WIDTH - mPlayer.NumX;
			mPlayer.TransY = mPlayer.InitiaY[0];
			break;
		case 2:
			mPlayer.TransX = mPlayer.InitiaX[1];
			mPlayer.TransY = mPlayer.NumY;
			break;
		case 3:
			mPlayer.TransX = mPlayer.NumX;
			mPlayer.TransY = mPlayer.InitiaY[1];
			break;
		}

		//手配座標
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			if (i != 13) {
				switch (num) {		//0～12牌並べる
				case 0:	//自家
					mPlayer.x[num][i] = mPlayer.NumSize[0] * i + mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 1:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.NumSize[1] * i + mPlayer.TransY;
					break;
				case 2:
					mPlayer.x[num][i] = mPlayer.TransX - mPlayer.NumSize[1] * i ;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 3:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY - mPlayer.NumSize[1] * i;
					break;
				}
			}
			else {
				switch (num) {		//13番目は離れて並べる
				case 0:	//自家
					mPlayer.x[num][i] = mPlayer.NumSize[0] * i + mPlayer.TransX + mPlayer.TransGet;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 1:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.NumSize[1] * i + mPlayer.TransY + mPlayer.TransGet;
					break;
				case 2:
					mPlayer.x[num][i] = mPlayer.TransX - mPlayer.NumSize[1] * i - mPlayer.TransGet;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 3:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY - mPlayer.NumSize[1] * i - mPlayer.TransGet;
					break;
				}
			}
		}
	}
	mPlayer.w = mPlayer.NumSize[0];	//幅
	mPlayer.h = mPlayer.NumSizeY;	//高さ

}

//マウス処理
void Player::TileHit(int tile) {
	mPlayer.sx1 = mPlayer.x[0][tile] - 30;
	mPlayer.sx2 = mPlayer.sx1 + mPlayer.w;
	mPlayer.sy1 = mPlayer.y[0][tile] - 20;
	mPlayer.sy2 = mPlayer.sy1 + mPlayer.h;
}