#include "Singleton.h"
//friend 복습할것
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
namespace ENGINE
{
	class TimeManager : public Singleton<TimeManager>
	{
	private:
		UINT32 FPS;
		FLOAT elapseTime;
		ULONGLONG currTime, lastTime, elapsed;

		TimeManager() : FPS(0), elapseTime(0.0f), currTime(0),lastTime(0) { }
	public:
		VOID Initialize(UINT32 FPS);
		BOOL Update();
		FLOAT DeltaTime() CONST { return elapseTime; }

		friend Singleton;
	};
#define TimeMgr TimeManager::GetInstance()
}
#endif  //!TIME_MANAGER_H
