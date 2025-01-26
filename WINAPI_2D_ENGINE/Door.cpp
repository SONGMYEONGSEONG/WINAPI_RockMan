#include "Door.h"


VOID GAME::Door::Initialize(FLOAT Pos_x, FLOAT Pos_y, FLOAT right, FLOAT bottom, UINT Type)
{
	//오브젝트 좌표 설정
	Object::SetPoint(Pos_x, Pos_y, right, bottom);
	Obj_Type = (ObjectType)Type;

	interact_area = {
		(LONG)HitRect.left-30,
		(LONG)HitRect.bottom - 10,
		(LONG)HitRect.left,
		(LONG)HitRect.bottom
	};

	ENGINE::ResourceMgr->Load("Door.bmp");
	Object::renderer = new ENGINE::SpriteRenderer("Door.bmp");
	Object::renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
	AddComponent(Object::renderer);

	return VOID();
}

VOID GAME::Door::Update(const FLOAT& deltaTime)
{
	Block::Object_Scrool(deltaTime);

	interact_area = {
	(LONG)HitRect.left - 30,
	(LONG)HitRect.bottom - 10,
	(LONG)HitRect.left,
	(LONG)HitRect.bottom + BlockSize.cy
	};

	return VOID();
}

VOID GAME::Door::Draw()
{
	Block::Draw();

	if (GetKeyState(VK_F11))
	{
		Rectangle(ENGINE::SceneMgr->GetBackDC(), interact_area.left, interact_area.top, interact_area.right, interact_area.bottom);
	}
	return VOID();
}

