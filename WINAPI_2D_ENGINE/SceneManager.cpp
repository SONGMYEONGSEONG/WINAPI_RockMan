#include "SceneManager.h"
#include "TimeManager.h"
//��ǲ�Ŵ��� Ŭ���� �ۼ��� ��� �߰�
#include "InputManager.h"
//���ҽ� �ų��� Ŭ���� �ۼ��� ��� �߰�
#include "ResourceManager.h"
//UI �Ŵ��� Ŭ���� �ۼ��� ��� �߰�
#include "UIManager.h"

namespace ENGINE
{
	SceneManager::~SceneManager() { Release(); }

	VOID SceneManager::Initialize(HWND hWnd, UINT32 width, UINT32 height)
	{
		if (!hWnd) return; //������ �ڵ��� �������� ������ ��ȯ

		this->hWnd = hWnd;
		this->width = width;
		this->height = height;
		hDC = GetDC(hWnd);
		//WINAPI ���� �Ұ�
		hBackDC = CreateCompatibleDC(hDC);
		TimeMgr->Initialize(FPS); //FPS : EngineMecro::ENGINE::enum::FPS
		InputMgr->Initialize();
		ResourceMgr->Initialize();
		UIMgr->Initialize();
	}

	VOID SceneManager::Release()
	{
		currScene = NULL;

		//������ �Ҵ��� ���� 
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
		//���� ���� ����ִ°�� ����
		if (nextScene.empty()) return;

		//���� ���� �����Ѵٸ� ������� ������ �� ���ҽ� �ʱ�ȭ
		if (currScene)
		{ 
			//������ ������ �Ҵ��� ����
			currScene->Release();
			UIMgr->Clear();
			ResourceMgr->Clear();
		}

		//���� ���� ���������� ����
		currScene = scenes[nextScene];
		//���� ���� �̴ϼȶ�����
		currScene->Initialize();
		nextScene = "";
	}

	VOID SceneManager::Update()
	{
		UIMgr->Update();
		//Ÿ�ӸŴ������� ��ŸŸ���� ���Ϲ޾Ƽ� Scene�Ŵ������� ��ŸƼ���� �̿��Ͽ� ������Ʈ����
		//currScene�� __interface�� �����Ǿ�����
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
		//���� �̸��� ���ų� ���� �������� �ʰų�(nullptr) �� ã������ ��������� FALSE ��ȯ
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

	//������� ��Ʈ : �����Ұ� 
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