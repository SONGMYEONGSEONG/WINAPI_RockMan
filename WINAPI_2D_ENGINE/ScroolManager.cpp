#include "ScroolManager.h"

BOOL GAME::ScroolManager::Initialize()
{
	Bounds = ENGINE::ClientSize_Width;
	ScroolLock = FALSE;
    ScroolPoint = 0;
	ScroolRoop = 0;
	ScroolSpeed = 0;
    Scroll_Dir = ScrollDirection::None;
    return TRUE;
}

VOID GAME::ScroolManager::Update()
{
	static FLOAT old_ScroolPoint = 0;

	//백그라운드 이미지 무한스크롤을 위한 함수영역
	//스크롤 roop를 한 만큼 현재 좌표에서 빼서 배경 스크롤 좌표를 재조정하는 함수
	//현재 스크롤 좌표 위치 + (스크롤 경계선(클라이언트 가로사이즈) + 스크롤 roop한 횟수))
	old_ScroolPoint = ScroolPoint + (Bounds * ScroolRoop);

	//오른쪽으로 캐릭터 이동(왼쪾으로 스크롤)
	if (old_ScroolPoint < -Bounds)
	{
		ScroolRoop++;
	}
	//왼쪽으로 캐릭터 이동(오른쪽으로 스크롤)
	else if (old_ScroolPoint > 0)
	{
		ScroolRoop--;
	}

}

VOID GAME::ScroolManager::Update_Scrool(FLOAT Scroolspeed,FLOAT ScroolPoint_add)
{
	if (ScroolPoint_add < 0)
	{
		Scroll_Dir = ScrollDirection::Left;
	}
	else if (ScroolPoint_add > 0)
	{
		Scroll_Dir = ScrollDirection::Right;
	}
	else
	{
		Scroll_Dir = ScrollDirection::None;
	}

	ScroolPoint += ScroolPoint_add;
	ScroolSpeed = Scroolspeed;
}
