#include "DxLib.h"
//#include "Game.h"
#include "Input.h"
int iOldKey;	//前回の入力キー
int iNowKey;	//今回の入力キー
int iKeyFlg;	//入力キー情報

int iMouseX;
int iMouseY;

void InputKey(void) {
	//入力キー取得
	iOldKey = iNowKey;
	iNowKey = GetMouseInput();
	iKeyFlg = iNowKey & ~iOldKey;
}