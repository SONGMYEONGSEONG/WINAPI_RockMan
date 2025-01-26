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

		//TimeMgr의 업데이트 경과시간이 FPS 못넘은경우 false 반환
		elapsed = (currTime - lastTime);
		if (elapsed < FPS) return FALSE; 

		elapseTime = elapsed * 0.001f;
		lastTime = currTime;

		return TRUE;
	}
}