#include "Mounten.h"
#include "DxLib.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Dealing.h"

#define PI    3.14159265358979323846264

Mounten mMounten;
/******************************
* ��������
*******************************/
void Mounten::Mounten_Initialize() {
	mDealing.Dealing_Initialize();

	//�v����������
	for (int kind = mMounten.mKind - 1; kind > 0; kind--) {
		if (kind > mDealing.SangenNumber) {			//�O���v
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Sangen, mDealing.SangenNumber);
			}
		}
		else if (kind > mDealing.DirectionNumber) {	//�l���v
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Direction, mDealing.DirectionNumber);
			}
		}
		else if (kind > mDealing.SousNumber) {		//���q
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Sous, mDealing.SousNumber);
			}
		}
		else if (kind > mDealing.PinsNumber) {		//���q
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Pins, mDealing.PinsNumber);
			}
		}
		else if (kind >= mDealing.MansNumber) {		//�ݎq
			for (int tile = 0; tile < 4; tile++) {
				mMounten.InitiaComp(kind, tile, mDealing.Mans, mDealing.MansNumber);
			}
		}
	}
	//�摜����������
	for (int tile = 0; tile < mMounten.Mnumber; tile++) {
		mMounten.AllImage[tile] = mDealing.Mounimage;
	}

	//�v���΂�΂�ɂ���
	//Shuffle();

	//�R�v���ׂ�ϐ�������
	mMounten.IniMoun = 0;
	//�`��摜�ϐ�������
	mMounten.NumImage = 0;
}

/******************************
* �X�V����
*******************************/
void Mounten::Mounten_Update() {
	unsigned int Cr;
	int moji = 0;
	Cr = GetColor(255, 255, 255);
	/*for (int i = 0; i < mMounten.Mnumber; i++) {
		if (mMounten.AllImage[i] != mDealing.Mounimage) {
			DrawFormatString(0, 20 * moji, Cr, "%d", i);
			moji++;
			DrawFormatString(0, 20 * moji, Cr, "%d", mMounten.Alltiles[i]);
			moji++;

		}
	}*/


	/*Cr = GetColor(0, 0, 255);
	for (int i = 0; i < mMounten.Mnumber; i++) {
		for (int j = i + 1; i < mMounten.Mnumber; j++) {
			if (mMounten.Alltiles[i] == mMounten.Alltiles[j]) {
				DrawFormatString(0, 20 * moji, Cr, "%d", i);
				moji++;
			}
		}
	}*/
}

/******************************
* �`�揈��
*******************************/
void Mounten::Mounten_Draw() {
	for (int tile = 0; tile < mMounten.Mnumber; tile++) {
		//���̊J�n�ʒu
		//*1�R�o�����玟�Ɉړ�
		if (tile % (mMounten.Width * mMounten.Height) == 0) {
			if (tile != 0) {
				mMounten.IniMoun++;
			}
		}

		//���W����
		mMounten.Position(tile);

		//�摜����
		DrawRotaGraph(mMounten.PositionX, mMounten.PositionY, mMounten.Size, mMounten.Rotate, mMounten.AllImage[mMounten.NumImage], false);
	}

	//�����Əo�����߂ɏ����l�ɖ߂�
	mMounten.IniMoun = 0;	
}

/******************************
* �֐�����
*******************************/
//�R�̍��W����
void Mounten::Position(int tile) {
	switch (mMounten.IniMoun) {
	case 0:	//����
		mMounten.PositionX = mMounten.NumInitiaX[0] - (mMounten.SizeNum * (tile / mMounten.Height));
		//�i������
		if (tile % 2 != 0) {	//�
			mMounten.PositionY = mgr.SCREEN_HEIGHT - mMounten.InitiaY;
			mMounten.NumImage = --tile;
		}
		else {					//����
			mMounten.PositionY = mgr.SCREEN_HEIGHT - mMounten.InitiaY - mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = PI * 2;
		break;

	case 1:	//���
		mMounten.PositionY = mMounten.NumInitiaY[0] - (mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width));
		//�i������
		if (tile % 2 != 0) {	//��i
			mMounten.PositionX = mgr.SCREEN_WIDTH - mMounten.InitiaX;
			mMounten.NumImage = --tile;
		}
		else {					//���i
			mMounten.PositionX = mgr.SCREEN_WIDTH - mMounten.InitiaX + mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = PI / 2;
		break;

	case 2:	//�Ζ�
		mMounten.PositionX = mMounten.NumInitiaX[1] + (mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width));
		//�i������
		if (tile % 2 != 0) {	//��i
			mMounten.PositionY = mMounten.InitiaY;
			mMounten.NumImage = --tile;
		}
		else {					//���i
			mMounten.PositionY = mMounten.InitiaY + mMounten.Step;
			mMounten.NumImage = ++tile;
		}

		mMounten.Rotate = -PI;
		break;

	case 3:	//����
		mMounten.PositionY = mMounten.SizeNum * ((tile / mMounten.Height) % mMounten.Width) + mMounten.NumInitiaY[1];
		//�i������
		if (tile % 2 != 0) {	//��i
			mMounten.PositionX = mMounten.InitiaX;
			mMounten.NumImage = --tile;
		}
		else {					//���i
			mMounten.PositionX = mMounten.InitiaX - mMounten.Step;
			mMounten.NumImage = ++tile;
		}
		mMounten.Rotate = -(PI / 2);
		break;
	}
}

//�v�̏���������
void Mounten::InitiaComp(int kind, int tile, int DataHouse[], int number) {
	mMounten.Alltiles[kind * 4 + tile] = DataHouse[kind - number];
}

//�V���b�t������
void Mounten::Shuffle() {
	int tmp, image;	//���̕ϐ��l�i�[
	int rand;		//�����_�����l�i�[

	unsigned int Cr;
	int moji = 0;
	Cr = GetColor(255, 255, 255);

	//�z������ւ�
	for (int i = mMounten.Mnumber - 1; i > 0; i--) {
		//�����_���擾
		rand = GetRand(mMounten.Mnumber - 1);

		//�z��Ƀ����_�����i�[
		tmp = mMounten.Alltiles[rand];
		mMounten.Alltiles[rand] = mMounten.Alltiles[i];
		mMounten.Alltiles[i] = tmp;

		//�摜�i�[
		image = mMounten.AllImage[rand];
		mMounten.AllImage[rand] = mMounten.AllImage[i];
		mMounten.AllImage[i] = image;
	}
}