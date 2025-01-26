#include "WinApiEngine.h"
#include "InputManager.h"//inputmanager 작성 후 추가
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

namespace ENGINE
{
	WinApiEngine::WinApiEngine(HINSTANCE hInstance, std::wstring title,
		INT32 per_x, INT32 per_y,
		UINT32 width, UINT32 height) : isInit(FALSE), title(title), x(0), y(0), width(width), height(height)
	{
		WNDCLASSEXW wcex =
		{
			sizeof(WNDCLASSEX),			//이 구조체의 크기.
			CS_HREDRAW | CS_VREDRAW,	//윈도우의 출력 형태, (CS_HREDRAW | CS_VREDRAW : 윈도우의 크기가 변경되면 다시 그린다.
			WndProc,					//윈도우 메시지 처리에 사용할 프로시저
			0,							//cbClsExtra : 클래스를 위한 여분 메모리 할당
			0,							//cbWndExtra : 윈도우를 위한 여분 메모리 할당. 일반적으로 사용X
			hInstance,					//해당 어플리케이션의 인스턴스 핸들.
			0,0,0,						//아이콘,커서,윈도우 배경색 설정.
			NULL,						//메뉴 이름, 메뉴의 사용 여부를 결정
			L"2DEngineWindowClass",		//윈도우 클래스 이름. 윈도우 생성시 이용
			NULL						//작은 아이콘 설정
		};
		RegisterClassExW(&wcex);

		/*--------------------------------------*/
		HWND hWnd = CreateWindow(
			TEXT("2DEngineWindowClass"), title.c_str(),
			WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
			nullptr, nullptr, hInstance, nullptr);

		if (!hWnd) return; //윈도우 핸들 생성실패시 리턴 

		RECT rcWindow, rcClient; //rc : RECT 자료형
		GetWindowRect(hWnd, &rcWindow);
		GetClientRect(hWnd, &rcClient);
		//CreateWindow의 인자로 들어가는 너비, 높이 값은 데스크 바 등등의 크기를 포함한 값이기 떄문에,
		// 그 차이 값을 구하여 윈도우 사이즈를 원하는 클라이언트 영역으로 다시만든다.
		UINT32 cx = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		UINT32 cy = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN); // SM_CXFULLSCREEN: 전체화면의 너비
		//CX,CY 축 방향 잘보고 적을것
		int screenHeight = GetSystemMetrics(SM_CYFULLSCREEN); // SM_CYFULLSCREEN: 전체화면의 높이
		per_x = clamp(per_x, 0, 100); //per_x,per_y r값 범위를 0~100사이로 제한.
		per_y = clamp(per_y, 0, 100);
		x = per_x * 0.01f * (screenWidth - width); //윈도우를 모니터(Screen) 범위의 특정 위치로 변경
		y = per_y * 0.01f * (screenHeight - height);

		//동작 제대로 잘됨
		MoveWindow(hWnd, x, y, width + cx, height + cy, false); //Window의 위치 및 크기를 재설정.

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		srand((unsigned)time(NULL));

		//Engine메인에 ScneManager 적용 (주석으로 호출 되는 위치 기록)
		/* Scene Initialized */ 
		SceneMgr->Initialize(hWnd, width, height);

		isInit = TRUE;
	}

	WinApiEngine::~WinApiEngine() { Release(); }

	INT WinApiEngine::Run()
	{
		if (!isInit) return -1;	//WinApiEngine함수가 실행되지 않은경우 리턴

		MSG msg; ZeroMemory(&msg, sizeof(msg));
		while (WM_QUIT != msg.message) //Game Loop
		{
			//0U :정수리터럴접미사 - 정수의 자료형 표기
			//0U : 0(unsinged int) , OUL : 0(unsigned long)
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))	
			{
				TranslateMessage(&msg);	//가상 키 코드를 WM_CHAR에서 사용가능한 문자로 반환.
				DispatchMessage(&msg); //발생한 메시지를 WndProc()에 발송 , WndPorc()가 호출.
			}
			else
			{
			//Engine메인에 ScneManager 적용 (주석으로 호출 되는 위치 기록)
			/* Scene Render*/ 
			SceneMgr->Render();
			}
		}
		Release();


		return (int)msg.wParam;
	}

	VOID WinApiEngine::Release()
	{
		//Engine메인에 ScneManager 적용 (주석으로 호출 되는 위치 기록)
		/* Scene Destroy */
		SceneMgr->Destroy();
	}

} //namespace ENGINE

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//인풋매니저헤더 추가후 인풋프로시저 추가
	ENGINE::InputMgr->InputProc(iMessage, wParam, lParam);

	switch (iMessage)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}

	return 0;
}