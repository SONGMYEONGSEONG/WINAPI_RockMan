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
		BOOL ScroolLock;//��ũ�� �� ���� ,(
		ScrollDirection Scroll_Dir;
		ScroolManager() {};
	public:
		~ScroolManager() {};
		
		VOID Update();
		//Player ĳ���Ͱ� x������ �̵��ϴ� ��ŭ Scrool�� ����
		VOID Update_Scrool(FLOAT ScroolSpeed,FLOAT ScroolPoint_add = 0);
		//�� ��ũ�ѵǴ� ������Ʈ�鿡�� ���� ��ũ�� ��ġ ����


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
