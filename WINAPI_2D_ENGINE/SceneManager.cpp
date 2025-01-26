#include "SceneManager.h"
#include "TimeManager.h"
//인풋매니저 클래스 작성후 헤더 추가
#include "InputManager.h"
//리소스 매너지 클래스 작성후 헤더 추가
#include "ResourceManager.h"
//UI 매니저 클래스 작성후 헤더 추가
#include "UIManager.h"

namespace ENGINE
{
	SceneManager::~SceneManager() { Release(); }

	VOID SceneManager::Initialize(HWND hWnd, UINT32 width, UINT32 height)
	{
		if (!hWnd) return; //윈도우 핸들이 생성되지 않으면 반환

		this->hWnd = hWnd;
		this->width = width;
		this->height = height;
		hDC = GetDC(hWnd);
		//WINAPI 복습 할것
		hBackDC = CreateCompatibleDC(hDC);
		TimeMgr->Initialize(FPS); //FPS : EngineMecro::ENGINE::enum::FPS
		InputMgr->Initialize();
		ResourceMgr->Initialize();
		UIMgr->Initialize();
	}

	VOID SceneManager::Release()
	{
		currScene = NULL;

		//해제는 할당의 역순 
		UIMgr->Destroy();
		ResourceMgr->Destroy();
		InputMgr->Destroy();
		TimeMgr-> Destroy();
		for (std::pair<std::string, Scene*>scene : scenes) REL_DEL(scene.second);
		scenes.clear();
		DeleteObject(hBackDC);
		ReleaseDC(hWnd, hDC);
	}

	VOID SceneManager::Render()
	{
		if (!TimeMgr->Update()) return;

		if (currScene)
		{
			Update();
			Draw();

			InputMgr->Update();
		}
		SetScene();
	}

	VOID SceneManager::SetScene()
	{
		//다음 씬이 비어있는경우 종료
		if (nextScene.empty()) return;

		//현재 씬이 존재한다면 현재씬을 릴리즈 및 리소스 초기화
		if (currScene)
		{ 
			//릴리즈 순서는 할당의 역순
			currScene->Release();
			UIMgr->Clear();
			ResourceMgr->Clear();
		}

		//현재 씬을 다음씬으로 선언
		currScene = scenes[nextScene];
		//현재 씬을 이니셜라이즈
		currScene->Initialize();
		nextScene = "";
	}

	VOID SceneManager::Update()
	{
		UIMgr->Update();
		//타임매니저에서 델타타임을 리턴받아서 Scene매니저에서 델타티임을 이용하여 업데이트실행
		//currScene은 __interface로 구성되어있음
		currScene->Update(TimeMgr->DeltaTime());
	}

	VOID SceneManager::Draw()
	{
		HBITMAP backBitmap = CreateDIBSectionRe();
		SelectObject(hBackDC, backBitmap);

		currScene->Draw();
		UIMgr->Draw();

		BitBlt(hDC, 0, 0, width, height, hBackDC, 0, 0, SRCCOPY);
		DeleteObject(backBitmap);
	}

	BOOL SceneManager::RegisterScene(LPCSTR sceneName, Scene* scene)
	{
		//씬의 이름이 없거나 씬이 존재하지 않거나(nullptr) 씬 찾았을때 없었을경우 FALSE 반환
		if ("" == sceneName || !scene || scenes.find(sceneName) != scenes.end())
			return FALSE;
		scenes.insert(std::make_pair(sceneName, scene));
		return TRUE;
	}

	BOOL SceneManager::LoadScene(LPCSTR sceneName)
	{
		if ("" == sceneName || scenes.find(sceneName) == scenes.end())
			return FALSE;
		nextScene = sceneName;
		return TRUE;
	}

	//더블버퍼 파트 : 복습할것 
	HBITMAP SceneManager::CreateDIBSectionRe()
	{
		BITMAPINFO bmpinfo;
		ZeroMemory(&bmpinfo.bmiHeader, sizeof(BITMAPINFOHEADER));
		bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpinfo.bmiHeader.biBitCount = 32;
		bmpinfo.bmiHeader.biWidth = width;
		bmpinfo.bmiHeader.biHeight = height;
		bmpinfo.bmiHeader.biPlanes = 1;
		LPVOID pBits;
		return CreateDIBSection(hDC, &bmpinfo, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	}
}//namespace ENGINE