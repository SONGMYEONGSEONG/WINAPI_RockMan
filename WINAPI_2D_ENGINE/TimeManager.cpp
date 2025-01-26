#include "TimeManager.h"
namespace ENGINE
{
	VOID TimeManager::Initialize(UINT32 FPS)
	{
		this->FPS = 1000 / FPS;
		currTime = lastTime = GetTickCount64();
	}

	BOOL TimeManager::Update()
	{
		currTime = GetTickCount64();

		//TimeMgr�� ������Ʈ ����ð��� FPS ��������� false ��ȯ
		elapsed = (currTime - lastTime);
		if (elapsed < FPS) return FALSE; 

		elapseTime = elapsed * 0.001f;
		lastTime = currTime;

		return TRUE;
	}
}