#include "EngineMecro.h"
#include "UIManager.h"

//Title �ʼ� ���
#include "BackGround.h" // ��� ��� 
#include "UIGameManager.h"
#include "InputManager.h"
#include "SceneManager.h" //�������ϱ� ���� �ʿ��� 


#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H
namespace GAME
{
	class TitleScene : public ENGINE::Scene
	{
	private:

		BOOL Press_Start_Display; // �����ӿ� ���� üũ bool ���� 
		ENGINE::Bitmap* Press_Start_Img; // Press_Start �̹��� ��Ʈ�� ���� 
		BackGround* pTitleBackGround = nullptr;

	public:
		// Scene��(��) ���� ��ӵ�
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		
	};
}
#endif //!STAGE_1_SCENE_H
