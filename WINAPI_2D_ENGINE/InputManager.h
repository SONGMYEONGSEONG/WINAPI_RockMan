#include "Singleton.h"
#include <unordered_map>
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
namespace ENGINE
{
	class InputManager : public Singleton<InputManager>
	{
	private:
		/*
		NONE : Ű�� ������ ���� ������(���û���)
		DOWN : Ű�� ��������(�ش� �����ӿ� ����������)
		PRESSED :  Ű�� ������������(������ �ִ»���)
		UP : Ű���� ���� ������(�ش� �����ӿ��� ������ �ʾ�����)
		*/
		enum class InputState { NONE, DOWN, PRESSED, UP };

		// map���� �� ���� Ž���� ���� �ڷᱸ��, �ߺ� �����͸� ������� �ʴ´�.
		// map���� �� ���� �����͸� ������ �� ���� ������ �����Ѵ�.
		std::unordered_map<UINT, InputState> keys; // key �Է� ���� ����
		std::map<UINT, InputState> mouse; //���콺 ��ư ���� ����
		POINT mousePosition; //���� ���콺 Ŀ���� ��ġ
		std::string str; //�Էµ� Ű�� ���� ����

		InputManager() : mousePosition({ 0,0 }) {}
	public:
		~InputManager();

		VOID Initialize() {}
		VOID Release();
		VOID Update();
		VOID InputProc(UINT message, WPARAM wParm, LPARAM lParam); // Input Procedur(��ǲ ó����)
		//c_str : string class ���ڿ� -> const char* �ڷ������� �����ϴ� ����Լ�
		LPCSTR GetChar() { return str.c_str(); }// �Է��� Ű�� ���� ������ �˾ƿ´�
		BOOL GetKeyDown(UINT keyID) { return KeyCheck(keyID, InputState::DOWN); } //Ȯ���Ϸ��� Key�� ���� �����ӿ��� ���� ���°�?
		BOOL GetKeyPressed(UINT keyID)
		{
			return(KeyCheck(keyID, InputState::PRESSED) || KeyCheck(keyID, InputState::DOWN));
		} //Ȯ���Ϸ��� key�� ������ �����ΰ�?
		BOOL GetKeyUp(UINT keyID) { return KeyCheck(keyID, InputState::UP); }//Ȯ�� �Ϸ��� key�� ���� �����ӿ��� �������� �ʾҴ°�?
		BOOL PressedAnyKey();
		BOOL GetMouseButtonDown(UINT keyID) { return ButtonCheck(keyID, InputState::DOWN); }
		BOOL GetMouseButtonPressed(UINT keyID)
		{
			return(ButtonCheck(keyID, InputState::PRESSED) || ButtonCheck(keyID, InputState::DOWN));
		}
		BOOL GetMouseButtonUp(UINT keyID) { return ButtonCheck(keyID, InputState::UP); }
		POINT GetMousePosition() CONST { return mousePosition; }
	
	private:
		VOID StartCapture(); // ���콺 Ŀ�� �̵� ���� ����.
		VOID EndCapture();	//���콺 Ŀ�� �̵� ���� ����.
		VOID SetKeyDown(UINT keyID) { keys[keyID] = InputState::DOWN; }//���� �Էµ� Ű�� �������·� ���� 
		VOID SetKeyUp(UINT keyID) { keys[keyID] = InputState::UP; }//���� �Էµ� Ű�� ������ �������·� ����
		VOID SetMouseButtonDown(UINT keyID);
		VOID SetMouseButtonUp(UINT keyID);
		VOID SetMousePosition(LPARAM lParam) {mousePosition = { LOWORD(lParam),HIWORD(lParam) }; }
		BOOL KeyCheck(UINT keyID, CONST InputState& state);
		BOOL ButtonCheck(UINT keyID, CONST InputState& state);

		friend Singleton;
	}; //class InputManager;
#define InputMgr InputManager::GetInstance()
} //namespace ENGINE
#endif //!INPUT_MANAGER_H