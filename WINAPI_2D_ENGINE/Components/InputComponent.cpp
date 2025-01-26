#include "InputComponent.h"
#include "../InputManager.h"
#include <cassert> //assert함수 헤더

namespace ENGINE
{
	BOOL InputComponent::AddBinding(char key, EventListener action_start, EventListener action_cancle)
	{
		//assert 함수
		// 반환값은 bool , false인경우  assert error 발생,
		// 개발자 디버깅용 함수 , false인경우 버그발생위치,call stack 등을 알려주는 함수
		// action은 NULL일 수 없다.
		assert((NULL != action_start) && (NULL != action_cancle));

		if (mappings.find(key) != mappings.end()) return FALSE;
		mappings[key][0] = action_start;
		mappings[key][1] = action_cancle;
		return TRUE;
	}

	VOID InputComponent::Operate(GameObject* Owner)
	{
		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyUp(iter->first)) iter->second[1]();
		}

		for (auto iter = mappings.begin(); iter != mappings.end(); iter++)
		{
			if (ENGINE::InputMgr->GetKeyPressed(iter->first)) iter->second[0]();
		}

	}
}