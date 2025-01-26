#pragma once
//namespace ENGINE
#include "EngineMecro.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"

//namespace GAME
#include "GameMecro.h"


#ifndef UI_SCENE_H
#define UI_SCENE_H

namespace GAME
{
	class UIScene : public ENGINE::GameObject
	{
	protected:
		ENGINE::UIImage* Cursorimg;
	public:
		UIScene() {};
		virtual ~UIScene() {};
		virtual VOID Initialize() abstract;
		virtual VOID Release()abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw() abstract;

		virtual BOOL Get_isPause() abstract;
		virtual VOID Set_PlayerHealthCount(UINT Health_Point) abstract;
		virtual VOID Set_PlayerLifeCount(UINT Life) abstract;
	};
}
#endif 