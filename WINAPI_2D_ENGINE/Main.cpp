#include "WinAPiEngine.h"
//추가
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "ClearScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR lpCmdLine,
						_In_ int nCmdShow)
{
	//WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y, UINT32 width, UINT32 height);
	ENGINE::WinApiEngine engine(hInstance, TEXT("WinAPI 2D Engine"),
		ENGINE::Client_Per_X, ENGINE::Client_Per_Y,
		ENGINE::ClientSize_Width, ENGINE::ClientSize_Height);


	//TODO: 여기애 새로운 씬 등록 및 로드.
	GAME::TitleScene* pTitleScene = new GAME::TitleScene;
	GAME::Stage1Scene* pStage1Scene = new GAME::Stage1Scene;
	GAME::ClearScene* pClearScene = new GAME::ClearScene;

	ENGINE::SceneMgr->RegisterScene("Title", pTitleScene);
	ENGINE::SceneMgr->RegisterScene("Stage1", pStage1Scene);
	ENGINE::SceneMgr->RegisterScene("Clear", pClearScene);

	ENGINE::SceneMgr->LoadScene("Title");
	//ENGINE::SceneMgr->LoadScene("Stage1");

	return engine.Run();
}