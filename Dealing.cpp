//牌の画像格納＆数値格納
#include "DxLib.h"
#include <stdlib.h>
#include "Dealing.h"
#include "SceneMgr.h"
#define PI    3.14159265358979323846264
Dealing mDealing;

/******************************
* 初期処理
*******************************/
void Dealing::Dealing_Initialize() {
	mDealing.Draw_Storage();	
	mDealing.Dealing_Storage();		
}

/******************************
* 関数処理
*******************************/
//牌画像格納
void Dealing::Draw_Storage() {
	LoadDivGraph("images/Mans.png", 9, 9, 1, 66, 95, mDealing.Mimage);
	LoadDivGraph("images/Souz.png", 9, 9, 1, 66, 95, mDealing.Simage);
	LoadDivGraph("images/Pinz.png", 9, 9, 1, 66, 96, mDealing.Pimage);
	LoadDivGraph("images/ma-jan4_sufonpai.png", 4, 4, 1, 66, 96, mDealing.Dimage);
	LoadDivGraph("images/ma-jan5_sangenpai.png", 3, 3, 1, 66, 96, mDealing.Saimage);
	LoadDivGraph("images/ma-jan6_akahai.png", 3, 3, 1, 66, 96, mDealing.DoraDraw);

	mDealing.Mounimage = LoadGraph("images/Mountain.png");
}

//牌変数格納
void Dealing::Dealing_Storage() {
	int Dnum = 33;

	//白發中
	for(int i = 2; Dnum >= SangenNumber; i--) {
		mDealing.Sangen[i] = Dnum;
		Dnum--;
	}
	//四風牌
	for(int i = 3; Dnum >= DirectionNumber; i--){
		mDealing.Direction[i] = Dnum;
		Dnum--;
	}
	//索子
	for(int i = 8; Dnum >= SousNumber; i--){
		mDealing.Sous[i] = Dnum;
		Dnum--;
	}
	//筒子
	for(int i = 8; Dnum >= PinsNumber; i--){
		mDealing.Pins[i] = Dnum;
		Dnum--;
	}
	//萬子
	for(int i = 8; Dnum >= MansNumber; i--){
		mDealing.Mans[i] = Dnum;
		Dnum--;
	}
}