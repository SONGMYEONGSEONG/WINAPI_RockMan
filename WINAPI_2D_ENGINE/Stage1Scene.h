//Player의 움직임에 따라 화면의 배경,오브젝트가 같이 이동하게 하는 클래스
//1.스크롤매니저는 리소스매니저에서 가져온 배경화면의 w,h를 알아야된다.
//2.배경화면의 끝에 도달한경우 다시 앞으로 한장더 그린다.
//3.스크롤매니저는 Stage_N_Scnen에서만 사용된다. 
//4.스크롤매니저느 Player좌표의 기준으로 스크롤되며, 스크롤 좌표는 left,botoom을 기준으로한다.

#include <array>
#include "EngineMecro.h"
#include "UIManager.h"

//Stage1Scene 필수 헤더
#include "ScroolManager.h"
#include "BackGround.h" // 배경 헤더 
#include "Player.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "UIGameManager.h"


#ifndef STAGE_1_SCENE_H
#define STAGE_1_SCENE_H
namespace GAME
{
	class Stage1Scene : public ENGINE::Scene
	{
	private:
		BackGround* pBackGround = nullptr;
		Player* pPlayer = nullptr;


	public:
		// Scene을(를) 통해 상속됨
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
	};
}
#endif //!STAGE_1_SCENE_H
