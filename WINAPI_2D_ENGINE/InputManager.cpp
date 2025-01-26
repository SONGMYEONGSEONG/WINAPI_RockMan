#include "InputManager.h"
#include "SceneManager.h"
namespace ENGINE
{
	InputManager::~InputManager() { Release(); }

	VOID InputManager::Release()
	{
		str = "";
		keys.clear();
		mouse.clear();
		EndCapture();
	}

	VOID InputManager::Update()
	{
		//기존에 입력한 키 초기화 
		str = "";
		for (std::pair<CONST UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN: //눌렀을때 -> 누르는중으로 상태 변화
				key.second = InputState::PRESSED; 
				break;
			case InputState::UP: //땟을때 -> 누르고있지않는 상태 변화
				key.second = InputState::NONE; 
				break;
			}
		}

		for (std::pair<CONST UINT, InputState>& button : mouse)
		{
			switch(button.second)
			{
			case InputState::DOWN:
				button.second = InputState::PRESSED; 
				break;
			case InputState::UP:
				button.second = InputState::NONE;
				break;
			}
		}
	}
	
	// param 고정된 값이 아니다 , input msg(인풋메시지)에 따라 param의 인자값이 달라진다.
	// msg(WM_CHAR) -> param : 입력한 문자를 알아온다.
	// msg(WM_KEYDOWN) -> param : 입력한 가상키 코드(VK_~)를 알아온다.
	// msg(WM_TIMER) -> param : 만들어진 타이머의 ID(nIDEvent)를 알아온다.(SetTimer함수로 만듬)
	VOID InputManager::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		//입력한 문자를 str변수(문자열)에 정의함.
		case WM_CHAR: str = wParam; break;
		//키보드 및 마우스 눌렀을경우(DOWN)
		case WM_KEYDOWN: case WM_SYSKEYDOWN: SetKeyDown(wParam); break;
		case WM_KEYUP: case WM_SYSKEYUP: SetKeyUp(wParam); break;
		case WM_LBUTTONDOWN: SetMouseButtonDown(VK_LBUTTON); break;
		case WM_RBUTTONDOWN: SetMouseButtonDown(VK_RBUTTON); break;
		case WM_MBUTTONDOWN: SetMouseButtonDown(VK_MBUTTON); break;
		case WM_XBUTTONDOWN:	
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonDown(VK_XBUTTON1); break; //마우스 왼쪽 뒤 버튼.
			case XBUTTON2: SetMouseButtonDown(VK_XBUTTON2); break; //마우스 왼쪽 앞 버튼.
			}
		}
		break;
		//키보드 및 마우스 땟을경우(UP)
		case WM_LBUTTONUP: SetMouseButtonUp(VK_LBUTTON); break;
		case WM_RBUTTONUP: SetMouseButtonUp(VK_RBUTTON); break;
		case WM_MBUTTONUP: SetMouseButtonUp(VK_MBUTTON); break;
		case WM_XBUTTONUP:
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonUp(VK_XBUTTON1); break; // 마우스 왼쪽 뒤 버튼.
			case XBUTTON2: SetMouseButtonUp(VK_XBUTTON2); break; // 마우스 왼쪽 앞 버튼.
			}
		}
		break;
		//마우스 이동
		case WM_MOUSEMOVE: SetMousePosition(lParam); break;
		}
	}

	//키보드의 키를 눌렀거나 누르는 중인경우 TRUE 반환, 아닌경우 FALSE
	BOOL InputManager::PressedAnyKey()
	{
		for (std::pair<CONST UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN:
			case InputState::PRESSED:
				return TRUE;
			}
			return FALSE;
		}
	}

	// 게임클라이언트에서 마우스가 밖으로 나가지 않게 해주는 함수
	// ex)인벤토리창을 클릭하고 드래그해서 클라이언트 밖으로 나가게되면 
	// 사용자가 가져오지못하거나 안보이는경우를 막기위한 코드 
	VOID InputManager::StartCapture()
	{
		HWND hWnd = SceneMgr->GetHWND();
		SetCapture(hWnd);
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1,SceneMgr->GetHeight() + 1 };
		ClientToScreen(hWnd, &leftTop);
		ClientToScreen(hWnd, &rightBottom);
		RECT clip = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};
		ClipCursor(&clip); // 마우스를 지정한 영역(RECT)안에 가두는 명령어 -> clip영역 안에서만 마우스를 고정하게 함
	}

	VOID InputManager::EndCapture()
	{
		ClipCursor(NULL);
		ReleaseCapture();
	}

	//UINT keyID <- VK_~(가상키코드) 를 인자로 받음
	VOID InputManager::SetMouseButtonDown(UINT keyID)
	{
		StartCapture();
		//해당 가상키코드의 상태를 DOWN(눌렀을떄)으로 정의
		mouse[keyID] = InputState::DOWN;
	}

	//UINT keyID <- VK_~(가상키코드) 를 인자로 받음
	VOID InputManager::SetMouseButtonUp(UINT keyID)
	{
		mouse[keyID] = InputState::UP;
		EndCapture();
	}

	BOOL InputManager::KeyCheck(UINT keyID, CONST InputManager::InputState& state)
	{
		std::unordered_map<UINT, InputState>::iterator iter = keys.find(keyID);
		if (keys.end() != iter)
		{
			return (state == iter->second);
		}

		keys.insert(std::make_pair(keyID,InputState::NONE));
		return FALSE;
	}

	BOOL InputManager::ButtonCheck(UINT keyID, const InputState& state)
	{
		std::map<UINT, InputState>::iterator iter = mouse.find(keyID);
		if (mouse.end() != iter) return (state == iter->second);

		mouse.insert(std::make_pair(keyID, InputState::NONE));
		return FALSE;
	}
} //namespace ENGINE
