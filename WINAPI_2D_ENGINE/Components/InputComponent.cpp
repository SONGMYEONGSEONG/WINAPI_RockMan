#include "InputComponent.h"
#include "../InputManager.h"
#include <cassert> //assert�Լ� ���

namespace ENGINE
{
	BOOL InputComponent::AddBinding(char key, EventListener action_start, EventListener action_cancle)
	{
		//assert �Լ�
		// ��ȯ���� bool , false�ΰ��  assert error �߻�,
		// ������ ������ �Լ� , false�ΰ�� ���׹߻���ġ,call stack ���� �˷��ִ� �Լ�
		// action�� NULL�� �� ����.
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