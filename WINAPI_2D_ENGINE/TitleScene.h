#include "EngineMecro.h"
#include "UIManager.h"

//Title 필수 헤더
#include "BackGround.h" // 배경 헤더 
#include "UIGameManager.h"
#include "InputManager.h"
#include "SceneManager.h" //씬변경하기 위해 필요함 


#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H
namespace GAME
{
	class TitleScene : public ENGINE::Scene
	{
	private:

		BOOL Press_Start_Display; // 프레임에 따른 체크 bool 변수 
		ENGINE::Bitmap* Press_Start_Img; // Press_Start 이미지 비트맵 파일 
		BackGround* pTitleBackGround = nullptr;

	public:
		// Scene을(를) 통해 상속됨
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		
	};
}
#endif //!STAGE_1_SCENE_H
