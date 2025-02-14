#pragma once
class Player {
private:
	const int MaxTile = 14;

public:
	/*************************
	* 変数処理
	**************************/
	//Player格納
	int Player[4][14];			//牌の数値格納
	int Image[4][14];			//牌の画像格納
	float x[4][14], y[4][14];	//座標
	float w, h;					//当たり判定
	int sx1, sx2, sy1, sy2;		//カーソルとの当たり判定

	//初期処理
	//Player
	float Size[2]{		//手牌画像サイズ
		0.9f, 0.6f
	};		
	float NumSize[2]{			//Xサイズ
		59.4f, 40.0f
	};
	float NumSizeY = 85.5f;		//yサイズ
	int InitiaX[2]{
		240, 930
	};
	int InitiaY[2]{		
		80, 610
	};
		//初期座標
	int Check;					//選んでいる画像浮かせる

	//共通
	int NumX = 1200;
	int NumY  = 45;
	int TransGet = 10;
	int TransX, TransY;

	//牌の処理
	int Get;
	int Del_count;
	bool Change[3];			//Enemy捨てるカウント
	int GetPlayer;			//取得者

/*************************
* 関数処理
**************************/
	void Player_Initialize();
	void Player_Update();
	void Player_Draw();

	//座標処理
	void PlayerTrans();

	//画像格納処理
	void Image_Storage(int Num, int tile);

	//牌とマウスの重なり
	void TileHit(int tile);
};
extern Player mPlayer;