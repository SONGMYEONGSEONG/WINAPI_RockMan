#include "ClearScene.h"

VOID GAME::ClearScene::Initialize()
{
    pClearBackGround = new BackGround;
    pClearBackGround->Initialize(BackGround_Type::Clear);

    //CLEAR 이미지 출력
    ENGINE::ResourceMgr->Load("Clear_Str.bmp");

    Clear_string_Img = ENGINE::ResourceMgr->GetBitmap("Clear_Str.bmp");

    //클리어 문구 좌표 init
    Clear_Str_Point.x = ENGINE::SceneMgr->GetWidth() * 0.5f - (Clear_string_Img->GetSize().cx * 0.5f);
    Clear_Str_Point.y = ENGINE::SceneMgr->GetHeight() * 0.5f - (Clear_string_Img->GetSize().cy * 0.5f);

    return VOID();
}

VOID GAME::ClearScene::Release()
{
    REL_DEL(pClearBackGround);
    return VOID();
}

VOID GAME::ClearScene::Update(const FLOAT& deltaTime)
{
    pClearBackGround->Update(deltaTime);

    static FLOAT Clear_Elipsed_Time = 0;
    Clear_Elipsed_Time += deltaTime;
    if(Clear_Elipsed_Time >= 3.0f)
    { 
        Clear_Elipsed_Time = 0;
        ENGINE::SceneMgr->LoadScene("Title");
    }
    return VOID();
}

VOID GAME::ClearScene::Draw()
{
    pClearBackGround->Draw();
    Clear_string_Img->TransparentBlt(Clear_Str_Point.x, Clear_Str_Point.y);
    return VOID();
}
