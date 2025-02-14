#pragma once
class Delete {
private:

public:
	/**************************
	* 変数処理
	***************************/
	int House[4][50];
	int x[4][6], y[4][4];
	int image;
	float size = 0.35f;
	int size_x = 24;
	int size_y = 34;

	int InitiaX[2]{
		538,682
	};
	int InitiaY[2]{
		432,288
	};

	bool ChangeSwitch;
	int River[4];
	int ImgRiver[4];

	/**************************
	* 関数処理
	***************************/
	void Delete_Initialize();
	void Delete_Update();
	void Delete_Draw();
};
extern Delete mDelete;