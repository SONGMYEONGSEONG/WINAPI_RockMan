#include "UIGameManager.h"

VOID GAME::UIGameManager::Initialize()
{
    UIScene_List.push_back(new UIStage);
    UIScene_List[0]->Initialize();
}

VOID GAME::UIGameManager::Release()
{
    for (UIScene* UIscene : UIScene_List)
    {
        REL_DEL(UIscene);
    }
}

VOID GAME::UIGameManager::Update(const FLOAT& deltaTime)
{
    for (UIScene* UIscene : UIScene_List)
    {
        UIscene->Update(deltaTime);
    }

}

VOID GAME::UIGameManager::Draw()
{
    for (UIScene* UIscene : UIScene_List)
    {
        UIscene->Draw();
    }
}
