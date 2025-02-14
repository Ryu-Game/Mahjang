#pragma once
class Player {
private:
	const int MaxTile = 14;

public:
	/*************************
	* �ϐ�����
	**************************/
	//Player�i�[
	int Player[4][14];			//�v�̐��l�i�[
	int Image[4][14];			//�v�̉摜�i�[
	float x[4][14], y[4][14];	//���W
	float w, h;					//�����蔻��
	int sx1, sx2, sy1, sy2;		//�J�[�\���Ƃ̓����蔻��

	//��������
	//Player
	float Size[2]{		//��v�摜�T�C�Y
		0.9f, 0.6f
	};		
	float NumSize[2]{			//X�T�C�Y
		59.4f, 40.0f
	};
	float NumSizeY = 85.5f;		//y�T�C�Y
	int InitiaX[2]{
		240, 930
	};
	int InitiaY[2]{		
		80, 610
	};
		//�������W
	int Check;					//�I��ł���摜��������

	//����
	int NumX = 1200;
	int NumY  = 45;
	int TransGet = 10;
	int TransX, TransY;

	//�v�̏���
	int Get;
	int Del_count;
	bool Change[3];			//Enemy�̂Ă�J�E���g
	int GetPlayer;			//�擾��

/*************************
* �֐�����
**************************/
	void Player_Initialize();
	void Player_Update();
	void Player_Draw();

	//���W����
	void PlayerTrans();

	//�摜�i�[����
	void Image_Storage(int Num, int tile);

	//�v�ƃ}�E�X�̏d�Ȃ�
	void TileHit(int tile);
};
extern Player mPlayer;