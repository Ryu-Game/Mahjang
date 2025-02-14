#pragma once
/******************************
* 牌格納
*******************************/
class Dealing {
private:

public:
	//牌初期番号
	const int MansNumber = 0;
	const int PinsNumber = 9;
	const int SousNumber = 18;
	const int DirectionNumber = 27;
	const int SangenNumber = 31;

	//牌格納
	int Mans[9];
	int Pins[9];
	int Sous[9];
	int Direction[4];
	int Sangen[3];
	int Dora;

	//牌画像格納
	int Mimage[9];		//萬子
	int Pimage[9];		//筒子
	int Simage[9];		//索子
	int Dimage[4];		//四風牌
	int Saimage[3];		//白發中
	int Mounimage;		//画像変数

	int DoraDraw[5];	//ドラ表示変数

	//関数処理
	void Dealing_Initialize();

	void Draw_Storage();	//牌画像格納
	void Dealing_Storage();	//牌変数格納

};

extern Dealing mDealing;