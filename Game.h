#pragma once

class Game {
public:
	int MaxPlayer = 4;
	int PlayerPoint[4];	//Player点数
	int King;
	bool Start;			//次のゲーム開始判定
	int Sugoroku;		//どこから区切るか決める

	int timecount, count;
};
/******************************
* 関数処理
*******************************/
void Game_Initialize();	
void Game_Finalize();	
void Game_Update();		
void Game_Draw();		

extern Game mGame;