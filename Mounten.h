#pragma once
class Mounten {
private:
	//”’l
	const int Mnumber = 136;	//”v‚Ì”
	const int mKind = 34;		//”v‚Ìí—Ş
	const int Width = 17;		//R”v‚Ì1—ñ:17
	const int Height = 2;		//R”v2’i

	//•`‰æ
	const float Size = 0.35f;	//•`‰æƒTƒCƒY
	const int SizeNum = 24;		//”v‚Ì‘å‚«‚³

	//À•W
	const int InitiaX = 870;	//‰ŠúX
	const int InitiaY = 130;	//‰ŠúY
	//”v‚ÌNumInitiaXÀ•W(”v1ŒÂ‚ÌÀ•WŒvZ)
	const int NumInitiaX[2]{
		834, 450
	};
	//”v‚ÌNumInitiaYÀ•W
	const int NumInitiaY[2]{
		554, 168
	};
	const int Step = 10;		//R”v‚Ì’i·

public:
	//”’l
	int Alltiles[136];			//‘S”v
	int IniMoun;				//Å‰‚ÌR”v

	int PositionX, PositionY;	//À•WŒvZŠi”[
	double Rotate;				//Šp“x

	//•`‰æ
	int AllImage[136];			//‰æ‘œŠi”[
	int NumImage;				//•Ï”‰æ‘œ

	//ŠÖ”ˆ—
	void Mounten_Initialize();	//‰Šú‰»ˆ—
	void Mounten_Update();		//XVˆ—
	void Mounten_Draw();		//•`‰æˆ—
	//void Mounten_Finalize();	//I—¹ˆ—

	void Position(int tile);

	void Shuffle();				//ƒVƒƒƒbƒtƒ‹ˆ—

	//”v‚Ì‰Šú‰»ˆ—
	void InitiaComp(int kind, int tile, int DataHouse[], int number);
};

extern Mounten mMounten;