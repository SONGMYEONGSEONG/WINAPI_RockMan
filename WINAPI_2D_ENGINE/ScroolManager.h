#pragma once
#include "Singleton.h"
#include "GameMecro.h"

#ifndef SCROOL_MANAGER_H
#define SCROOL_MANAGER_H
namespace GAME
{
	
	class ScroolManager : public Singleton<ScroolManager>
	{
	private:
		FLOAT ScroolPoint;
		FLOAT ScroolSpeed;
		INT32 ScroolRoop;//
		INT32 Bounds;
		BOOL ScroolLock;//스크롤 락 변수 ,(
		ScrollDirection Scroll_Dir;
		ScroolManager() {};
	public:
		~ScroolManager() {};
		
		VOID Update();
		//Player 캐릭터가 x축으로 이동하는 만큼 Scrool값 조정
		VOID Update_Scrool(FLOAT ScroolSpeed,FLOAT ScroolPoint_add = 0);
		//각 스크롤되는 오브젝트들에게 현재 스크롤 위치 제공


		BOOL Initialize();

		FLOAT Get_ScroolPoint() { return ScroolPoint; }
		FLOAT Get_ScroolRoop() { return ScroolRoop; }
		FLOAT Get_ScroolSpeed() { return ScroolSpeed; }
		BOOL Get_ScroolLock() { return ScroolLock; }
		ScrollDirection Get_ScroolDir()
		{
			return Scroll_Dir;
		}
		VOID Set_ScroolPoint(FLOAT scroolpoint) { ScroolPoint = scroolpoint; }
		VOID Set_ScroolLock(BOOL scroolLock) { ScroolLock = scroolLock; }
		VOID Reset_ScroolDate() { ScroolPoint = 0; ScroolRoop = 0; }
		
		friend Singleton;
	};
#define ScroolMgr ScroolManager::GetInstance()
#define GetScroolPoint ScroolManager::GetInstance()->Get_ScroolPoint() 
}
#endif 
