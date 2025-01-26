#include "WinApiEngine.h"
#include "InputManager.h"//inputmanager �ۼ� �� �߰�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace ENGINE
{
	WinApiEngine::WinApiEngine(HINSTANCE hInstance, std::wstring title,
		INT32 per_x, INT32 per_y,
		UINT32 width, UINT32 height) : isInit(FALSE), title(title), x(0), y(0), width(width), height(height)
	{
		WNDCLASSEXW wcex =
		{
			sizeof(WNDCLASSEX),			//�� ����ü�� ũ��.
			CS_HREDRAW | CS_VREDRAW,	//�������� ��� ����, (CS_HREDRAW | CS_VREDRAW : �������� ũ�Ⱑ ����Ǹ� �ٽ� �׸���.
			WndProc,					//������ �޽��� ó���� ����� ���ν���
			0,							//cbClsExtra : Ŭ������ ���� ���� �޸� �Ҵ�
			0,							//cbWndExtra : �����츦 ���� ���� �޸� �Ҵ�. �Ϲ������� ���X
			hInstance,					//�ش� ���ø����̼��� �ν��Ͻ� �ڵ�.
			0,0,0,						//������,Ŀ��,������ ���� ����.
			NULL,						//�޴� �̸�, �޴��� ��� ���θ� ����
			L"2DEngineWindowClass",		//������ Ŭ���� �̸�. ������ ������ �̿�
			NULL						//���� ������ ����
		};
		RegisterClassExW(&wcex);

		/*--------------------------------------*/
		HWND hWnd = CreateWindow(
			TEXT("2DEngineWindowClass"), title.c_str(),
			WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
			nullptr, nullptr, hInstance, nullptr);

		if (!hWnd) return; //������ �ڵ� �������н� ���� 

		RECT rcWindow, rcClient; //rc : RECT �ڷ���
		GetWindowRect(hWnd, &rcWindow);
		GetClientRect(hWnd, &rcClient);
		//CreateWindow�� ���ڷ� ���� �ʺ�, ���� ���� ����ũ �� ����� ũ�⸦ ������ ���̱� ������,
		// �� ���� ���� ���Ͽ� ������ ����� ���ϴ� Ŭ���̾�Ʈ �������� �ٽø����.
		UINT32 cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		UINT32 cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN); // SM_CXFULLSCREEN: ��üȭ���� �ʺ�
		//CX,CY �� ���� �ߺ��� ������
		int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN); // SM_CYFULLSCREEN: ��üȭ���� ����
		per_x = clamp(per_x, 0, 100); //per_x,per_y r�� ������ 0~100���̷� ����.
		per_y = clamp(per_y, 0, 100);
		x = per_x * 0.01f * (screenWidth - width); //�����츦 �����(Screen) ������ Ư�� ��ġ�� ����
		y = per_y * 0.01f * (screenHeight - height);

		//���� ����� �ߵ�
		MoveWindow(hWnd, x, y, width + cx, height + cy, false); //Window�� ��ġ �� ũ�⸦ �缳��.

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		srand((unsigned)time(NULL));

		//Engine���ο� ScneManager ���� (�ּ����� ȣ�� �Ǵ� ��ġ ���)
		/* Scene Initialized */ 
		SceneMgr->Initialize(hWnd, width, height);

		isInit = TRUE;
	}

	WinApiEngine::~WinApiEngine() { Release(); }

	INT WinApiEngine::Run()
	{
		if (!isInit) return -1;	//WinApiEngine�Լ��� ������� ������� ����

		MSG msg; ZeroMemory(&msg, sizeof(msg));
		while (WM_QUIT != msg.message) //Game Loop
		{
			//0U :�������ͷ����̻� - ������ �ڷ��� ǥ��
			//0U : 0(unsinged int) , OUL : 0(unsigned long)
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))	
			{
				TranslateMessage(&msg);	//���� Ű �ڵ带 WM_CHAR���� ��밡���� ���ڷ� ��ȯ.
				DispatchMessage(&msg); //�߻��� �޽����� WndProc()�� �߼� , WndPorc()�� ȣ��.
			}
			else
			{
			//Engine���ο� ScneManager ���� (�ּ����� ȣ�� �Ǵ� ��ġ ���)
			/* Scene Render*/ 
			SceneMgr->Render();
			}
		}
		Release();


		return (int)msg.wParam;
	}

	VOID WinApiEngine::Release()
	{
		//Engine���ο� ScneManager ���� (�ּ����� ȣ�� �Ǵ� ��ġ ���)
		/* Scene Destroy */
		SceneMgr->Destroy();
	}

} //namespace ENGINE

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//��ǲ�Ŵ������ �߰��� ��ǲ���ν��� �߰�
	ENGINE::InputMgr->InputProc(iMessage, wParam, lParam);

	switch (iMessage)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}

	return 0;
}