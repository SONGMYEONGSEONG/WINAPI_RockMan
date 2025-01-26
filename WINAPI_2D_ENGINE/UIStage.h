#pragma once
//namespace ENGINE
#include "EngineMecro.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "Components/InputComponent.h" 
#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���

//namespace GAME
#include "GameMecro.h"
#include "UIScene.h"
#include <vector>

#ifndef UI_STAGE_H
#define UI_STAGE_H

namespace GAME
{
	class UIStage : public UIScene
	{
	private:
		BOOL isPause;//�Ͻ����� üũ ����

		//�Ͻ����� ȭ�� UIImage->��ġ �� ���� x
		ENGINE::UIImage* Cursorimg;
		ENGINE::UIImage* pauseWindow;

		//�ΰ��� �÷��̾� hp�� -> ��ġ �� ���� ����
		ENGINE::Bitmap* HealthWindow;
		ENGINE::Bitmap* HealthPoint;

		UINT Draw_roop_count;//�÷��̾��� ����ü�¸�ŭ �׸��� Ƚ��

		ENGINE::UILabel* LifeCountText; //UI TEXT : �÷��̾� ������� ���� 
		UINT Player_life_count;//�÷��̾��� ������� 
		std::string Player_Life_Str; // �÷��̾� ���� ( ex : ~ x )
		HFONT hFont; // ��Ʈ
	public:
		VOID Initialize();
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();

		VOID UI_PauseScreen();//�Ͻ������� ���õ� UI ��ũ��(����ϱ�,�����ϱ�)

		VOID PauseBtnClickHandler();
		VOID ContinueBtnClickHandler();
		VOID QuitBtnClickHandler();

		BOOL Get_isPause() { return isPause; }
		VOID Set_PlayerHealthCount(UINT Health_Point) { Draw_roop_count = Health_Point; }//�÷��̾� ü�� ǥ�� (�÷��̾� Ŭ�������� HP ���ڰ� �޾Ƽ� ǥ��
		VOID Set_PlayerLifeCount(UINT Life) { Player_life_count = Life; }//�÷��̾� ������� ǥ�� (�÷��̾� Ŭ�������� life(ü��) ���ڰ� �޾Ƽ� ǥ��
	};
}
#endif 