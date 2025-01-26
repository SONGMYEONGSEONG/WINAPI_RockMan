#include "TitleScene.h"

VOID GAME::TitleScene::Initialize()
{
    pTitleBackGround = new BackGround;
    pTitleBackGround->Initialize(BackGround_Type::Title);

    //Press GameStart 이미지 출력 
    ENGINE::ResourceMgr->Load("Title_Press_Start.bmp");

    Press_Start_Img = ENGINE::ResourceMgr->GetBitmap("Title_Press_Start.bmp");
    Press_Start_Img->ResetSize();

    Press_Start_Display = TRUE;

    return VOID();
}

VOID GAME::TitleScene::Release()
{
    REL_DEL(pTitleBackGround);
    return VOID();
}

VOID GAME::TitleScene::Update(const FLOAT& deltaTime)
{
    pTitleBackGround->Update(deltaTime);

    static FLOAT elipsed_Time = 0;
    elipsed_Time += deltaTime;
    
    if (elipsed_Time >= 0.1f)
    {
        Press_Start_Display = !Press_Start_Display;
        elipsed_Time = 0;
    }

    if (ENGINE::InputMgr->GetKeyDown(VK_RETURN))
    {
        ENGINE::SceneMgr->LoadScene("Stage1");
    }

    return VOID();
}

VOID GAME::TitleScene::Draw()
{
    pTitleBackGround->Draw();
    if(Press_Start_Display)
    Press_Start_Img->TransparentBlt(ENGINE::SceneMgr->GetHeight() * 0.5f, ENGINE::SceneMgr->GetHeight() * 0.8f);

    return VOID();
}
