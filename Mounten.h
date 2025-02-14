#pragma once
class Mounten {
private:
	//���l
	const int Mnumber = 136;	//�v�̐�
	const int mKind = 34;		//�v�̎��
	const int Width = 17;		//�R�v��1��:17
	const int Height = 2;		//�R�v2�i

	//�`��
	const float Size = 0.35f;	//�`��T�C�Y
	const int SizeNum = 24;		//�v�̑傫��

	//���W
	const int InitiaX = 870;	//����X
	const int InitiaY = 130;	//����Y
	//�v��NumInitiaX���W(�v1�̍��W�v�Z)
	const int NumInitiaX[2]{
		834, 450
	};
	//�v��NumInitiaY���W
	const int NumInitiaY[2]{
		554, 168
	};
	const int Step = 10;		//�R�v�̒i��

public:
	//���l
	int Alltiles[136];			//�S�v
	int IniMoun;				//�ŏ��̎R�v

	int PositionX, PositionY;	//���W�v�Z�i�[
	double Rotate;				//�p�x

	//�`��
	int AllImage[136];			//�摜�i�[
	int NumImage;				//�ϐ��摜

	//�֐�����
	void Mounten_Initialize();	//����������
	void Mounten_Update();		//�X�V����
	void Mounten_Draw();		//�`�揈��
	//void Mounten_Finalize();	//�I������

	void Position(int tile);

	void Shuffle();				//�V���b�t������

	//�v�̏���������
	void InitiaComp(int kind, int tile, int DataHouse[], int number);
};

extern Mounten mMounten;