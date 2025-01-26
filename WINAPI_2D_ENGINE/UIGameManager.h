#pragma once
//namespace ENGINE
#include "Singleton.h"
#include <vector>

//namespace GAME
#include "GameMecro.h"
#include "UIStage.h"

#ifndef UI_GAMEMANAGER_H
#define UI_GAMEMANAGER_H

namespace GAME
{
	class UIGameManager : public Singleton<UIGameManager>
	{
	private:
		std::vector< UIScene*> UIScene_List;
	public:
		VOID Initialize();
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();

		UIScene* Get_UIScene(UINT UIScene_index)
		{
			return UIScene_List[UIScene_index];
		}


		friend Singleton;
	};
#define UIGameMgr UIGameManager::GetInstance()
}

#endif 


