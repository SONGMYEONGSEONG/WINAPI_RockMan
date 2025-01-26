#include "Block.h"

VOID GAME::Block::Initialize(FLOAT Pos_x, FLOAT Pos_y, FLOAT right, FLOAT bottom, UINT Type)
{
	//오브젝트 좌표 설정
	Object::SetPoint(Pos_x, Pos_y, right, bottom);
	Obj_Type = (ObjectType)Type;

	//object type 설정
	LPCSTR File_Name ="";
	switch (Obj_Type)
	{
	case  ObjectType::Ground_Obj:
		File_Name = "Ground.bmp";
		break;
	case ObjectType::Block_Obj:
		File_Name = "Block1.bmp";
		break;
	case ObjectType::Ceiling_Obj:
		File_Name = "Ceiling.bmp";
		break;
	}

	ENGINE::ResourceMgr->Load(File_Name);
	Object::renderer = new ENGINE::SpriteRenderer(File_Name);
	Object::renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
	AddComponent(Object::renderer);

	return VOID();
}

VOID GAME::Block::Release()
{
	return VOID();
}

VOID GAME::Block::Update(const FLOAT& deltaTime)
{
	Object_Scrool(deltaTime);

	return VOID();
}

VOID GAME::Block::Draw()
{	
	//이미지의 dest(원본크기)가 아닌 히트영역에 맞춰서 다시그리게 하는 코드(추가함)
	renderer->ObjectDraw(BlockSize.cx,BlockSize.cy);
	//debug
	if (GetKeyState(VK_F11))
	{
		Rectangle(ENGINE::SceneMgr->GetBackDC(), HitRect.left, HitRect.top, HitRect.right, HitRect.bottom);
	}
	return VOID();
}
