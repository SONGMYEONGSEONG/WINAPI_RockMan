#pragma once
#include "EngineMecro.h"
#include "UIManager.h"

//Clear�ʼ� ���
#include "BackGround.h" // ��� ��� 
#include "UIGameManager.h"
#include "InputManager.h"
#include "SceneManager.h" //�������ϱ� ���� �ʿ��� 

#ifndef CLEAR_SCENE_H
#define CLEAR_SCENE_H
namespace GAME
{
	class ClearScene : public ENGINE::Scene
	{
	private:

		ENGINE::Bitmap* Clear_string_Img; // Clear_String �̹��� ��Ʈ�� ���� 
		POINT Clear_Str_Point; //Ŭ���� ���� ��ǥ ��ġ 
		BackGround* pClearBackGround = nullptr;
	public:
		// Scene��(��) ���� ��ӵ�
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;

	};

}
#endif //!CLEAR_SCENE_H

