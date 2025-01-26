#include "Stage1Scene.h"
#include "TimeManager.h"//델타타임을 통한 스크롤 이동 정해져야함

VOID GAME::Stage1Scene::Initialize()
{

   UINT32 bounds = ENGINE::SceneMgr->GetWidth();

   pBackGround = new BackGround;

   pBackGround->Initialize(BackGround_Type::Stage1);

   pPlayer = new Player;
   pPlayer->Initialize();

   ScroolMgr->Initialize();
   ObjectMgr->Initialize();
   EnemyMgr->Initialize(pPlayer);
   UIGameMgr->Initialize();

    return VOID();
}

VOID GAME::Stage1Scene::Release()
{
    UIGameMgr->Release();
    ObjectMgr->Release();
    EnemyMgr->Release();

    UIGameMgr->Destroy();
    ObjectMgr->Destroy();
    EnemyMgr->Destroy();
    ScroolMgr->Destroy();

    REL_DEL(pPlayer);
    REL_DEL(pBackGround);
  


    return VOID();
}

VOID GAME::Stage1Scene::Update(const FLOAT& deltaTime)
{
    UIGameMgr->Update(deltaTime);
   
    //게임 일시정지기능 조건문
    if (!UIGameMgr->Get_UIScene(0)->Get_isPause())
    {
        ScroolMgr->Update();
        pPlayer->Update(deltaTime);
        pBackGround->Update(deltaTime);
        ObjectMgr->Update(deltaTime);
        EnemyMgr->Update(deltaTime);
    }

    return VOID();
}

VOID GAME::Stage1Scene::Draw()
{
    pBackGround->Draw();
    ObjectMgr->Draw();
    EnemyMgr->Draw();
    pPlayer->Draw();
    UIGameMgr->Draw();

    return VOID();
}
