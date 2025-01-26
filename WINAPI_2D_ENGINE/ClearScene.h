#pragma once
#include "EngineMecro.h"
#include "UIManager.h"

//Clear필수 헤더
#include "BackGround.h" // 배경 헤더 
#include "UIGameManager.h"
#include "InputManager.h"
#include "SceneManager.h" //씬변경하기 위해 필요함 

#ifndef CLEAR_SCENE_H
#define CLEAR_SCENE_H
namespace GAME
{
	class ClearScene : public ENGINE::Scene
	{
	private:

		ENGINE::Bitmap* Clear_string_Img; // Clear_String 이미지 비트맵 파일 
		POINT Clear_Str_Point; //클리어 문구 좌표 위치 
		BackGround* pClearBackGround = nullptr;
	public:
		// Scene을(를) 통해 상속됨
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;

	};

}
#endif //!CLEAR_SCENE_H

