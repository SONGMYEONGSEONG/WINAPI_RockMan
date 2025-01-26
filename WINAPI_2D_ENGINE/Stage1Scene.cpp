#include "Stage1Scene.h"
#include "TimeManager.h"//��ŸŸ���� ���� ��ũ�� �̵� ����������

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
   
    //���� �Ͻ�������� ���ǹ�
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
