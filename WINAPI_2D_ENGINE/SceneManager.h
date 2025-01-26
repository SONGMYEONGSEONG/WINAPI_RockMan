#include "Singleton.h"
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
//더블버퍼 복습할것 (backDC)
namespace ENGINE
{
	class SceneManager : public Singleton<SceneManager>
	{
	private:
		HWND hWnd;
		HDC hDC, hBackDC;
		UINT32 width, height;

		Scene* currScene;
		std::string nextScene;
		std::map<std::string, Scene*> scenes;

		SceneManager() : hWnd(NULL), hDC(NULL), hBackDC(NULL), width(0), height(0), currScene(NULL) { };
	public:
		~SceneManager();

		VOID Initialize(HWND hWnd, UINT32 width, UINT32 height);
		VOID Release();
		VOID Render();

		BOOL RegisterScene(LPCSTR sceneName, Scene* scene); //Scene 등록.
		BOOL LoadScene(LPCSTR sceneName); // 불러 올 Scene 설정.

		UINT32 GetWidth() CONST { return width; } // 윈도우의 클라이언트 너비.
		UINT32 GetHeight() CONST { return height; } // 윈도우의 클라이언트 높이.
		HWND GetHWND() CONST { return hWnd; }
		HDC GetBackDC() CONST { return hBackDC; }

	private:
		VOID SetScene(); //등록된 Scene을 적용
		VOID Update();
		VOID Draw();
		HBITMAP CreateDIBSectionRe(); // Back Bitmap을 만들기 위한 비트맵 Creater
	
		friend Singleton;
	}; //class SceneManager
#define SceneMgr SceneManager::GetInstance()
}//namespace ENGINE
#endif //!SCENE_MANAGER_H

