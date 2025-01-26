#include "Character.h"

 BOOL GAME::Character::Object_Move_Check()
{
	POINT LeftBottom = { HitArea.left,HitArea.bottom - 1 };
	POINT RightBottom = { HitArea.right, HitArea.bottom - 1 };
	POINT CenterBottom = { (HitArea.right - HitArea.left) * 0.5f + HitArea.left,HitArea.bottom + 1 };

	for (int index = 0; index < ObjectMgr->Get_ObjectManagerSize(); index++)
	{
		RECT* tmp_RECT = ObjectMgr->Get_BlockObject(index)->Get_BlockRect();

		//Player 중앙지점에 오브젝트가 닿은경우 Move오브젝트체크 실행X
		if (!PtInRect(tmp_RECT, CenterBottom))
		{
			if ((PtInRect(tmp_RECT, LeftBottom) && dir == Direction::Left)
				||
				(PtInRect(tmp_RECT, RightBottom) && dir == Direction::Right)
				)
			{
				//TODO CODE
				return TRUE;
			}
		}
	}
	return FALSE;
}

 UINT GAME::Character::Ground_Check()
{
	POINT CenterBottom = { (HitArea.right - HitArea.left) * 0.5f + HitArea.left,HitArea.bottom };

	for (int index = 0; index < ObjectMgr->Get_ObjectManagerSize(); index++)
	{
		RECT* tmp_RECT = ObjectMgr->Get_BlockObject(index)->Get_BlockRect();

		if (PtInRect(tmp_RECT, CenterBottom))
		{
			//TODO CODE
			return index;
		}
	}
	return -1;
}

 VOID GAME::Character::Gravity_Down(const FLOAT& deltaTime)
{
	//300 : PlayerJumpSpeed
	if (Jumpdir != JumpState::Up || state == State::Hit)
	{
		transform->position.y += 300 * deltaTime;

		UINT BlockIndex = Ground_Check();
		switch (BlockIndex)
		{
		case -1:

			break;
		default:
			RECT* Ground_Block = ObjectMgr->Get_BlockObject(BlockIndex)->Get_BlockRect();
			transform->position.y = clamp(transform->position.y, 0, Ground_Block->top);
			Jumpdir = JumpState::None;
			break;
		}
	}

}

 BOOL GAME::Character::Ceiling_Check()
 {
	 POINT LeftTop = { HitArea.left,HitArea.top - 1 };
	 POINT RightTop = { HitArea.right, HitArea.top - 1 };
	 POINT CenterTop = { (HitArea.right - HitArea.left) * 0.5f + HitArea.left , HitArea.top + 1 };

	 for (int index = 0; index < ObjectMgr->Get_ObjectManagerSize(); index++)
	 {
		 RECT* tmp_RECT = ObjectMgr->Get_BlockObject(index)->Get_BlockRect();

		 //Player 중앙지점에 오브젝트가 닿은경우 Move오브젝트체크 실행X
		 if (PtInRect(tmp_RECT, CenterTop))
		 {
			 return TRUE;
		 }
	 }
	 return FALSE;
 }