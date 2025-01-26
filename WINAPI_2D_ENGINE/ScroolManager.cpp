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

	//��׶��� �̹��� ���ѽ�ũ���� ���� �Լ�����
	//��ũ�� roop�� �� ��ŭ ���� ��ǥ���� ���� ��� ��ũ�� ��ǥ�� �������ϴ� �Լ�
	//���� ��ũ�� ��ǥ ��ġ + (��ũ�� ��輱(Ŭ���̾�Ʈ ���λ�����) + ��ũ�� roop�� Ƚ��))
	old_ScroolPoint = ScroolPoint + (Bounds * ScroolRoop);

	//���������� ĳ���� �̵�(�ަU���� ��ũ��)
	if (old_ScroolPoint < -Bounds)
	{
		ScroolRoop++;
	}
	//�������� ĳ���� �̵�(���������� ��ũ��)
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
