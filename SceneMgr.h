#pragma once

typedef enum {
	eScene_Title,
	eScene_Game,
	eScene_End,

	eScene_None,
}eScene;

class Scene_Mgr {
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	int backImage;
};

void SceneMgr_Initialize();
void SceneMgr_Finalize();
void SceneMgr_Update();
void SceneMgr_Draw();

void SceneMgr_ChangeScene(eScene nextScene);


extern Scene_Mgr mgr;