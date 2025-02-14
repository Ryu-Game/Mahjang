#include <DxLib.h>
#include "Player.h"
#include "Mounten.h"
#include "Dealing.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Input.h"
#include "Delete.h"
#define PI    3.14159265358979323846264

Player mPlayer;

/**************************
* ����������
***************************/
void Player::Player_Initialize() {
	SetFontSize(20);
	//���Őe��������悤�ɂ���(�v���g�͎��Ƃ�������Ă���)

	//�ŏ������l
	mPlayer.GetPlayer = mGame.King;

	//�ʒu��񏉊���
	mPlayer.PlayerTrans();

	//Y���W��Player���ɖ߂�
	mPlayer.TransY = mgr.SCREEN_HEIGHT - mPlayer.NumY;

	//Player�ϐ�������
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		for (int tile = 0; tile < mPlayer.MaxTile; tile++) {
			mPlayer.Player[num][tile] = 0;
		}
	}

	//�ŏ��̎擾���i�[
	mPlayer.Get = mGame.Sugoroku * 2;
	//3�v�z���4��J��Ԃ�
	for (int four = 0; four < 4; four++) {					//4��J��Ԃ�
		for (int num = 0; num < mGame.MaxPlayer; num++) {	//�l����
			for (int count = 0; count < 3; count++) {		//3�v�z��
				//���l���擾
				mPlayer.Player[num][count + four * 3] = mMounten.Alltiles[mPlayer.Get];
				//�z���������
				mMounten.Alltiles[mPlayer.Get] = -1;
				mMounten.AllImage[mPlayer.Get] = 0;
				mPlayer.Get++;
			}
		}
	}
	//�Ō��1�����Ƃ�
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		mPlayer.Player[num][12] = mMounten.Alltiles[mPlayer.Get];
		//�擾���������
		mMounten.Alltiles[mPlayer.Get] = -1;
		mMounten.AllImage[mPlayer.Get] = 0;
		mPlayer.Get++;
	}
}

/**************************
* �X�V����
***************************/
void Player::Player_Update() {
	//�v�̎擾����
	switch (mPlayer.GetPlayer) {
	case 0:
	case 1:
	case 2:
	case 3:
		mPlayer.Player[mPlayer.GetPlayer][13] = mMounten.Alltiles[mPlayer.Get];
		//�擾���������
		mMounten.Alltiles[mPlayer.Get] = -1;
		mMounten.AllImage[mPlayer.Get] = 0;
		break;
	}

	//�}�E�X���W
	if (mPlayer.GetPlayer == 0) {
		//�v�ƃ}�E�X�̏d�Ȃ�
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			mPlayer.TileHit(i);
			
			//�}�E�X�J�[�\��
			if (mPlayer.sx1 <= iMouseX && mPlayer.sx2 >= iMouseX && mPlayer.sy1 <= iMouseY && mPlayer.sy2 >= iMouseY) {
				mPlayer.Check = i;
				mPlayer.y[mPlayer.GetPlayer][mPlayer.Check] = mPlayer.TransY - 20;
			}
		}
		//�v�ƃ}�E�X���d�Ȃ��Ă��Ȃ����߂�
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			if (i != mPlayer.Check) {
				mPlayer.y[0][i] = mPlayer.TransY;
			}
		}
	}

	//�Ƃ�����̂Ă鏈��
	switch (mPlayer.GetPlayer) {
	case 0:
		  if (iKeyFlg & MOUSE_INPUT_LEFT) {
			  mDelete.image = mPlayer.Image[mPlayer.GetPlayer][mPlayer.Check];
			  mPlayer.Player[mPlayer.GetPlayer][mPlayer.Check] = mPlayer.Player[mPlayer.GetPlayer][13];
			  mPlayer.Player[0][13] = -1;
			  mDelete.ChangeSwitch = true;
			  mPlayer.Get++;
			  mPlayer.Del_count++;
		  }
		  break;
	case 1:
	case 2:
	case 3:
		//if (mPlayer.Change[mPlayer.GetPlayer - 1] == true) {
			mDelete.image = mPlayer.Image[mPlayer.GetPlayer][13];
			mPlayer.Player[mPlayer.GetPlayer][13] = -1;
			mDelete.ChangeSwitch = true;
			mPlayer.Get++;
			mPlayer.Del_count++;
			mPlayer.GetPlayer++;
			if (mPlayer.GetPlayer == 4) {
				mPlayer.GetPlayer = 0;
			}
		//}
		//else if (mPlayer.Change[mPlayer.GetPlayer - 1] == false) {
		//	mPlayer.Change[mPlayer.GetPlayer - 1] = true;
		//}
			break;
	}
}
/**************************
* �`�揈��
***************************/
void Player::Player_Draw() {
	//�摜�i�[
	for (int Num = 0; Num < mGame.MaxPlayer; Num++) {
		for (int tile = 0; tile < mPlayer.MaxTile; tile++) {
			mPlayer.Image_Storage(Num, tile);
		}
	}

	//��z�`�揈��
	for (int n = 0; n < mGame.MaxPlayer; n++) {
		for (int i = 0; i < 13; i++) {
			switch (n) {
			case 0:	//����
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[0], PI / 90.0, mPlayer.Image[n][i], false);
				break;
			case 1:	//����
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], PI / 2, mPlayer.Image[n][i], false);
				break;
			case 2:	//�Ζ�
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], PI, mPlayer.Image[n][i], false);
				break;
			case 3:	//���
				DrawRotaGraph(mPlayer.x[n][i], mPlayer.y[n][i], mPlayer.Size[1], -(PI / 2), mPlayer.Image[n][i], false);
				break;
			}
		}
	}

	switch (mPlayer.GetPlayer) {
	case 0:
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[0], PI / 90.0, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 1:	//����
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], PI / 2, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 2:	//�Ζ�
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], PI, mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	case 3:	//���
		DrawRotaGraph(mPlayer.x[mPlayer.GetPlayer][13], mPlayer.y[mPlayer.GetPlayer][13], mPlayer.Size[1], -(PI / 2), mPlayer.Image[mPlayer.GetPlayer][13], false);
		break;
	}
}

/**************************
* �֐�����
***************************/
//�摜�i�[����
void Player::Image_Storage(int num, int tile) {
	//�O���v
	if (mDealing.SangenNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 3; j++) {
			if (mDealing.Sangen[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Saimage[j];
				break;
			}
		}
	}
	//�l���v
	else if (mDealing.DirectionNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 4; j++) {
			if (mDealing.Direction[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Dimage[j];
				break;
			}
		}
	}
	//���q
	else if (mDealing.SousNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Sous[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Simage[j];
				break;
			}
		}
	}
	//���q
	else if (mDealing.PinsNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Pins[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Pimage[j];
				break;
			}
		}
	}
	//�ݎq
	else if (mDealing.MansNumber <= mPlayer.Player[num][tile]) {
		for (int j = 0; j < 9; j++) {
			if (mDealing.Mans[j] == mPlayer.Player[num][tile]) {
				mPlayer.Image[num][tile] = mDealing.Mimage[j];
				break;
			}
		}

	}
}

//���W����
void Player::PlayerTrans() {
	//Player�ʒu���(�����蔻�聕�`����W)
	for (int num = 0; num < mGame.MaxPlayer; num++) {
		//�ePlayer�̏������W
		switch (num) {
		case 0:
			mPlayer.TransX = mPlayer.InitiaX[0];
			mPlayer.TransY = mgr.SCREEN_HEIGHT - mPlayer.NumY;
			break;
		case 1:
			mPlayer.TransX = mgr.SCREEN_WIDTH - mPlayer.NumX;
			mPlayer.TransY = mPlayer.InitiaY[0];
			break;
		case 2:
			mPlayer.TransX = mPlayer.InitiaX[1];
			mPlayer.TransY = mPlayer.NumY;
			break;
		case 3:
			mPlayer.TransX = mPlayer.NumX;
			mPlayer.TransY = mPlayer.InitiaY[1];
			break;
		}

		//��z���W
		for (int i = 0; i < mPlayer.MaxTile; i++) {
			if (i != 13) {
				switch (num) {		//0�`12�v���ׂ�
				case 0:	//����
					mPlayer.x[num][i] = mPlayer.NumSize[0] * i + mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 1:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.NumSize[1] * i + mPlayer.TransY;
					break;
				case 2:
					mPlayer.x[num][i] = mPlayer.TransX - mPlayer.NumSize[1] * i ;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 3:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY - mPlayer.NumSize[1] * i;
					break;
				}
			}
			else {
				switch (num) {		//13�Ԗڂ͗���ĕ��ׂ�
				case 0:	//����
					mPlayer.x[num][i] = mPlayer.NumSize[0] * i + mPlayer.TransX + mPlayer.TransGet;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 1:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.NumSize[1] * i + mPlayer.TransY + mPlayer.TransGet;
					break;
				case 2:
					mPlayer.x[num][i] = mPlayer.TransX - mPlayer.NumSize[1] * i - mPlayer.TransGet;
					mPlayer.y[num][i] = mPlayer.TransY;
					break;
				case 3:
					mPlayer.x[num][i] = mPlayer.TransX;
					mPlayer.y[num][i] = mPlayer.TransY - mPlayer.NumSize[1] * i - mPlayer.TransGet;
					break;
				}
			}
		}
	}
	mPlayer.w = mPlayer.NumSize[0];	//��
	mPlayer.h = mPlayer.NumSizeY;	//����

}

//�}�E�X����
void Player::TileHit(int tile) {
	mPlayer.sx1 = mPlayer.x[0][tile] - 30;
	mPlayer.sx2 = mPlayer.sx1 + mPlayer.w;
	mPlayer.sy1 = mPlayer.y[0][tile] - 20;
	mPlayer.sy2 = mPlayer.sy1 + mPlayer.h;
}