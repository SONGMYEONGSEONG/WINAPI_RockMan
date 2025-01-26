#pragma once
//namespace ENGINE
#include "EngineMecro.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "InputManager.h"
#include "Components/InputComponent.h" 
#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함

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
		BOOL isPause;//일시정지 체크 변수

		//일시정지 화면 UIImage->위치 및 변동 x
		ENGINE::UIImage* Cursorimg;
		ENGINE::UIImage* pauseWindow;

		//인게임 플레이어 hp바 -> 위치 및 변동 가능
		ENGINE::Bitmap* HealthWindow;
		ENGINE::Bitmap* HealthPoint;

		UINT Draw_roop_count;//플레이어의 현재체력만큼 그리는 횟수

		ENGINE::UILabel* LifeCountText; //UI TEXT : 플레이어 목숨갯수 글자 
		UINT Player_life_count;//플레이어의 목숨갯수 
		std::string Player_Life_Str; // 플레이어 글자 ( ex : ~ x )
		HFONT hFont; // 폰트
	public:
		VOID Initialize();
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();

		VOID UI_PauseScreen();//일시정지에 관련된 UI 스크린(계속하기,종료하기)

		VOID PauseBtnClickHandler();
		VOID ContinueBtnClickHandler();
		VOID QuitBtnClickHandler();

		BOOL Get_isPause() { return isPause; }
		VOID Set_PlayerHealthCount(UINT Health_Point) { Draw_roop_count = Health_Point; }//플레이어 체력 표현 (플레이어 클래스에서 HP 인자값 받아서 표현
		VOID Set_PlayerLifeCount(UINT Life) { Player_life_count = Life; }//플레이어 목숨갯수 표현 (플레이어 클래스에서 life(체력) 인자값 받아서 표현
	};
}
#endif 