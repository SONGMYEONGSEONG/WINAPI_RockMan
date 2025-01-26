#include "UIStage.h"

VOID GAME::UIStage::Initialize()
{
    FLOAT bounds = ENGINE::SceneMgr->GetWidth();

    ENGINE::ResourceMgr->Load("RockMan_Life.bmp");
    ENGINE::ResourceMgr->Load("base_panel.bmp");
    ENGINE::ResourceMgr->Load("continue_normal.bmp");
    ENGINE::ResourceMgr->Load("continue_pressed.bmp");
    ENGINE::ResourceMgr->Load("quit_normal.bmp");
    ENGINE::ResourceMgr->Load("quit_pressed.bmp");
    ENGINE::ResourceMgr->Load("Cursor.bmp");

    pauseWindow = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("PauseWindow Canvas");

    Player_Life_Str = " X ";

    //일시정지 화면 함수포인터 변경해야됨
    if (pauseWindow)
    {
        pauseWindow->Initialize("base_panel.bmp", ENGINE::DrawType::Transparent);
        pauseWindow->SetPosition(bounds * 0.5f, ENGINE::SceneMgr->GetHeight() * 0.5f, TRUE);

        //컨티뉴 UI 이미지
        ENGINE::UIImage* continueimg = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("continue img", pauseWindow);
        continueimg->Initialize("continue_normal.bmp", ENGINE::DrawType::Transparent);
        continueimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true);

        //나가기 UI 이미지
        ENGINE::UIImage* quitimg = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("quit img", pauseWindow);
        quitimg->Initialize("quit_normal.bmp", ENGINE::DrawType::Transparent);
        quitimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f + 50, true);

        //생명(목숨) UI이미지
        ENGINE::UIImage* Lifeimg = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("life img", pauseWindow);
        Lifeimg->Initialize("RockMan_Life.bmp", ENGINE::DrawType::Transparent);
        Lifeimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f - 50, pauseWindow->GetSize().cy * 0.5f + 150, true);

        //생명(목숨) UI 글자
        LifeCountText = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("lifecount Text", pauseWindow);
        LifeCountText->Initialize("");
        LifeCountText->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f+30, pauseWindow->GetSize().cy * 0.5f + 150, true);
        LifeCountText->SetColor(RGB(255, 255, 255));

        //생명(목숨) UI 글자폰트 설정
        hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
        SelectObject(ENGINE::SceneMgr->GetBackDC(), hFont);

        LifeCountText->SetFont(hFont);
    
        //커서 UI이미지
        Cursorimg = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("cursor img", pauseWindow);
        Cursorimg->Initialize("Cursor.bmp", ENGINE::DrawType::Transparent);
        Cursorimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f - 150, pauseWindow->GetSize().cy * 0.5f - 100, true);

        pauseWindow->SetEnable(FALSE);
    }

    isPause = FALSE;


    ENGINE::ResourceMgr->Load("Health_Tool.bmp");
    ENGINE::ResourceMgr->Load("Health_Point.bmp");

    HealthWindow = ENGINE::ResourceMgr->GetBitmap("Health_Tool.bmp");
    HealthWindow->ResetSize();

    HealthPoint = ENGINE::ResourceMgr->GetBitmap("Health_Point.bmp");
    HealthPoint->SetDrawSize(33,16);

}

VOID GAME::UIStage::Release()
{
    DeleteObject(hFont);
}

//포인트 x,y 좌표등 enum화 시켜야함
VOID GAME::UIStage::UI_PauseScreen()
{
    //ESC key 입력시 일시정지 동작 
    if (ENGINE::InputMgr->GetKeyDown(VK_ESCAPE))
    {
        switch (isPause)
        {
        case FALSE:
            PauseBtnClickHandler();
            break;
        case TRUE:
            ContinueBtnClickHandler();
            Cursorimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f - 150, pauseWindow->GetSize().cy * 0.5f - 100, true);
            break;
        }
        return;
    }

    //일시정지화면인경우 동작 조작 키 
    switch (isPause)
    {
    case TRUE:
        if (ENGINE::InputMgr->GetKeyDown(VK_UP))
        {
            Cursorimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f - 150, pauseWindow->GetSize().cy * 0.5f - 100, true);
        }

        if (ENGINE::InputMgr->GetKeyDown(VK_DOWN))
        {
            Cursorimg->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f - 150, pauseWindow->GetSize().cy * 0.5f + 50, true);
        }

        if (ENGINE::InputMgr->GetKeyDown(VK_RETURN))
        {
            if (Cursorimg->GetLocalPosition().y == pauseWindow->GetSize().cy * 0.5f - 100)
            {
                ContinueBtnClickHandler();
            }

            if (Cursorimg->GetLocalPosition().y == pauseWindow->GetSize().cy * 0.5f + 50)
            {
                QuitBtnClickHandler();
            }
        }
        break;

    }
}


VOID GAME::UIStage::Update(const FLOAT& deltaTime)
{
    Player_Life_Str = " X " + std::to_string(Player_life_count); //목숨값에 갱신하여 플레이어 목숨 글자 갱신
    LifeCountText->SetText(Player_Life_Str);
    UI_PauseScreen();
}

VOID GAME::UIStage::Draw()
{
    HealthWindow->TransparentBlt(30, ENGINE::SceneMgr->GetHeight() * 0.3f, TRUE);

    for (int i = 0; i < Draw_roop_count; i++)
    {
        HealthPoint->TransparentBlt(30, ENGINE::SceneMgr->GetHeight() * 0.6f - (i * 20));
    }

}

VOID GAME::UIStage::PauseBtnClickHandler()
{
    isPause = TRUE;
    pauseWindow->SetEnable(TRUE);
}

VOID  GAME::UIStage::ContinueBtnClickHandler()
{
    pauseWindow->SetEnable(FALSE);
    isPause = FALSE;
}

VOID GAME::UIStage::QuitBtnClickHandler()
{
    PostQuitMessage(0);
}
