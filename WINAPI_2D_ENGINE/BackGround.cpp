#include "BackGround.h"
#include "EngineMecro.h" //STAGE interface 상속용
#include "ResourceManager.h"//리소스를 참조하기위한 매니저헤더
#include "SceneManager.h" // 클라이언트 w,h를 알기위해
#include "ScroolManager.h"

BOOL GAME::BackGround::Initialize(BackGround_Type background_Type)
{
    BGType = background_Type;
    BackGround_Point.x = POINT_X;
    BackGround_Point.y = POINT_Y;
    bounds = ENGINE::SceneMgr->GetWidth();

    std::string Background_Name;
    switch (BGType)
    {
    case BackGround_Type::Stage1:
        //background Init- Stage1
        Background_Name = "background.bmp";
        break;

    case BackGround_Type::Title:
        //background Init- Title
        Background_Name = "Title.bmp";
        break;

    case BackGround_Type::Clear:
        //background Init- Clear
        Background_Name = "Clear.bmp";
        break;

    default :

        return FALSE;
        break;
    }

    ENGINE::ResourceMgr->Load(Background_Name);

    background = ENGINE::ResourceMgr->GetBitmap(Background_Name);
    background->SetDrawSize(bounds, ENGINE::SceneMgr->GetHeight());

    return TRUE;
}

VOID GAME::BackGround::Release()
{
	return VOID();
}

VOID GAME::BackGround::Update(const FLOAT& deltaTime)
{
    FLOAT ScroolPoint = ScroolMgr->Get_ScroolPoint();
    INT32 ScroolRoop = ScroolMgr->Get_ScroolRoop();

    switch (BGType)
    {
    case BackGround_Type::Stage1:

        BackGround_Point.x = ScroolPoint + (bounds * ScroolRoop);

        break;
    default:
        break;
    }
   


	return VOID();
}

VOID GAME::BackGround::Draw()
{
   background->TransparentBlt(BackGround_Point.x, BackGround_Point.y);
   if (BGType == BackGround_Type::Stage1)
   {
       background->TransparentBlt(BackGround_Point.x + bounds, BackGround_Point.y);
   }

	return VOID();
}
