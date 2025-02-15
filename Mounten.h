#pragma once
class Mounten {
private:
	//数値
	const int Mnumber = 136;	//牌の数
	const int mKind = 34;		//牌の種類
	const int Width = 17;		//山牌の1列:17
	const int Height = 2;		//山牌2段

	//描画
	const float Size = 0.35f;	//描画サイズ
	const int SizeNum = 24;		//牌の大きさ

	//座標
	const int InitiaX = 870;	//初期X
	const int InitiaY = 130;	//初期Y
	//牌のNumInitiaX座標(牌1個の座標計算)
	const int NumInitiaX[2]{
		834, 450
	};
	//牌のNumInitiaY座標
	const int NumInitiaY[2]{
		554, 168
	};
	const int Step = 10;		//山牌の段差

public:
	//数値
	int Alltiles[136];			//全牌
	int IniMoun;				//最初の山牌

	int PositionX, PositionY;	//座標計算格納
	double Rotate;				//角度

	//描画
	int AllImage[136];			//画像格納
	int NumImage;				//変数画像

	//関数処理
	void Mounten_Initialize();	//初期化処理
	void Mounten_Update();		//更新処理
	void Mounten_Draw();		//描画処理
	//void Mounten_Finalize();	//終了処理

	void Position(int tile);

	void Shuffle();				//シャッフル処理

	//牌の初期化処理
	void InitiaComp(int kind, int tile, int DataHouse[], int number);
};

extern Mounten mMounten;