#include "SceneMgr.h"
#include "DxLib.h"
#include "Game.h"
Scene_Mgr mgr;

//現シーンの管理変数（初期シーン設定）
static eScene mScene = eScene_Game;
//次シーンの管理変数
static eScene mNextScene = eScene_None;

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

//Scene：初期化処理
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//Scene：終了処理
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//Scene：更新処理
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {
		//現在のシーンの終了処理実行
		SceneMgr_FinalizeModule(mScene);
		//次のシーンを現在のシーンをセット
		mScene = mNextScene;
		//現在のシーンを初期化
		SceneMgr_InitializeModule(mScene);
	}
	switch (mScene) {
	case eScene_Game:
		Game_Update();
		break;
	}
}

//Scene：描画処理
void SceneMgr_Draw() {
	switch (mScene) {
	case eScene_Game:
		//背景画像描画
		DrawGraph(0, 0, mgr.backImage, false);
		Game_Draw();
		break;
	}
}

//引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;
}

//引数 Scene モジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {
	case eScene_Game:
		mgr.backImage = LoadGraph("images/zyantaku.jpg");
		Game_Initialize();
		break;
	}
}

//引数 Scene モジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {
	case eScene_Game:
		Game_Finalize();
		break;
	}
}