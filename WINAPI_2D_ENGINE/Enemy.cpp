#include "Enemy.h"

VOID GAME::Enemy::Set_HItCheck()
{
	switch (Type)
			{
			case Character_Type::METOL:
				//������ ��� �Ѱ��� �ݰ����� ��� ������ ���ϸ� �ȵǱ� ����������
				if (CharState != CharacterState::None) { bEnemy_Hit = TRUE; };
				break;

			default:
				bEnemy_Hit = TRUE;
				break;
			}
}

VOID GAME::Enemy::Position_Update(FLOAT Move_Distance)
{
	FLOAT ScroolPoint = ScroolMgr->Get_ScroolPoint();
	transform->position.x = ScroolPoint + Enemy_Init_Point.x + Move_Distance;
}

VOID GAME::Enemy::HitArea_Update(const SIZE Enemy_Size, const LONG Left_add, const LONG Top_add, const LONG Right_add, const LONG Bottom_add)
{
	HitArea =
	{
		(LONG)transform->position.x + Left_add,
		(LONG)transform->position.y - Enemy_Size.cy + Top_add,
		(LONG)transform->position.x + Enemy_Size.cx + Right_add,
		(LONG)transform->position.y + Bottom_add
	};
}

VOID GAME::Enemy::Hit_Check()
{
	//Test -Enemy HP Decreases Code
	if (bEnemy_Hit)
	{
		if (Health_Point <= 0)
		{
			islife = false;
			HitArea = { 0,0,0,0 };
			return;
		}
		Health_Point -= 10;//�÷��̾��� ���ݷ��� play���� ���������ؾ���
	}

}

VOID GAME::Enemy::Set_Enemy_Init_Point(ENGINE::Vector2 Init_Point)
{
	Enemy_Init_Point = Init_Point;
	transform->position.x = Enemy_Init_Point.x;
}

VOID GAME::Enemy::Set_PlayerHitArea(RECT* PlayerHitArea)
{
	Enemy_Target_HitAtea = PlayerHitArea;
}