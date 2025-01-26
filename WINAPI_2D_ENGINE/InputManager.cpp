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
		//������ �Է��� Ű �ʱ�ȭ 
		str = "";
		for (std::pair<CONST UINT, InputState>& key : keys)
		{
			switch (key.second)
			{
			case InputState::DOWN: //�������� -> ������������ ���� ��ȭ
				key.second = InputState::PRESSED; 
				break;
			case InputState::UP: //������ -> �����������ʴ� ���� ��ȭ
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
	
	// param ������ ���� �ƴϴ� , input msg(��ǲ�޽���)�� ���� param�� ���ڰ��� �޶�����.
	// msg(WM_CHAR) -> param : �Է��� ���ڸ� �˾ƿ´�.
	// msg(WM_KEYDOWN) -> param : �Է��� ����Ű �ڵ�(VK_~)�� �˾ƿ´�.
	// msg(WM_TIMER) -> param : ������� Ÿ�̸��� ID(nIDEvent)�� �˾ƿ´�.(SetTimer�Լ��� ����)
	VOID InputManager::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		//�Է��� ���ڸ� str����(���ڿ�)�� ������.
		case WM_CHAR: str = wParam; break;
		//Ű���� �� ���콺 ���������(DOWN)
		case WM_KEYDOWN: case WM_SYSKEYDOWN: SetKeyDown(wParam); break;
		case WM_KEYUP: case WM_SYSKEYUP: SetKeyUp(wParam); break;
		case WM_LBUTTONDOWN: SetMouseButtonDown(VK_LBUTTON); break;
		case WM_RBUTTONDOWN: SetMouseButtonDown(VK_RBUTTON); break;
		case WM_MBUTTONDOWN: SetMouseButtonDown(VK_MBUTTON); break;
		case WM_XBUTTONDOWN:	
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonDown(VK_XBUTTON1); break; //���콺 ���� �� ��ư.
			case XBUTTON2: SetMouseButtonDown(VK_XBUTTON2); break; //���콺 ���� �� ��ư.
			}
		}
		break;
		//Ű���� �� ���콺 �������(UP)
		case WM_LBUTTONUP: SetMouseButtonUp(VK_LBUTTON); break;
		case WM_RBUTTONUP: SetMouseButtonUp(VK_RBUTTON); break;
		case WM_MBUTTONUP: SetMouseButtonUp(VK_MBUTTON); break;
		case WM_XBUTTONUP:
		{
			switch (wParam)
			{
			case XBUTTON1: SetMouseButtonUp(VK_XBUTTON1); break; // ���콺 ���� �� ��ư.
			case XBUTTON2: SetMouseButtonUp(VK_XBUTTON2); break; // ���콺 ���� �� ��ư.
			}
		}
		break;
		//���콺 �̵�
		case WM_MOUSEMOVE: SetMousePosition(lParam); break;
		}
	}

	//Ű������ Ű�� �����ų� ������ ���ΰ�� TRUE ��ȯ, �ƴѰ�� FALSE
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

	// ����Ŭ���̾�Ʈ���� ���콺�� ������ ������ �ʰ� ���ִ� �Լ�
	// ex)�κ��丮â�� Ŭ���ϰ� �巡���ؼ� Ŭ���̾�Ʈ ������ �����ԵǸ� 
	// ����ڰ� �����������ϰų� �Ⱥ��̴°�츦 �������� �ڵ� 
	VOID InputManager::StartCapture()
	{
		HWND hWnd = SceneMgr->GetHWND();
		SetCapture(hWnd);
		POINT leftTop = { 0,0 };
		POINT rightBottom = { SceneMgr->GetWidth() + 1,SceneMgr->GetHeight() + 1 };
		ClientToScreen(hWnd, &leftTop);
		ClientToScreen(hWnd, &rightBottom);
		RECT clip = { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};
		ClipCursor(&clip); // ���콺�� ������ ����(RECT)�ȿ� ���δ� ��ɾ� -> clip���� �ȿ����� ���콺�� �����ϰ� ��
	}

	VOID InputManager::EndCapture()
	{
		ClipCursor(NULL);
		ReleaseCapture();
	}

	//UINT keyID <- VK_~(����Ű�ڵ�) �� ���ڷ� ����
	VOID InputManager::SetMouseButtonDown(UINT keyID)
	{
		StartCapture();
		//�ش� ����Ű�ڵ��� ���¸� DOWN(��������)���� ����
		mouse[keyID] = InputState::DOWN;
	}

	//UINT keyID <- VK_~(����Ű�ڵ�) �� ���ڷ� ����
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
