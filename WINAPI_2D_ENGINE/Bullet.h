#include "GameMecro.h" 
#include "SceneManager.h" // debug용 
#include "ScroolManager.h" //플레이어 이동시 총알 속도 보정용 
#include "ResourceManager.h" // bitmap 자료형 
#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include <cmath>

#ifndef BULLET_H
#define BULLET_H


//총알이 충돌영역 체크하게 해야됨 
//(공격받는 상대(총알RECT,적 RECT)가 누구인지 확인해서 데미지 적용시켜야되기위해)
//오브텍트 풀링으로 3개까지 만들어놓기 , 더 필요하면 할당
namespace GAME
{
	enum
	{
		BULLET_MAX = 5,//화면에 있을수 있는 총알 갯수
	};

	class Bullet : public ENGINE::GameObject
	{
	private:
		enum BulletPoint
		{
			Right_Pointx = 50,//오른쪽보고 사격시 보정 좌표값
			Left_Pointx = -10,//왼쪽보고 사격시 보정 좌표값
			Gun_Pointy = -25, //캐릭터 총구 보정 좌표값
		};
		
		ENGINE::Vector2 Init_Pos; // 총알 초기 위치 
		BOOL islife; //총알 유무

		INT BulletDir;
		RECT BulletRect; // 총알 충돌영역체크 
		SIZE BulletSize; // bullet width,height 

		ENGINE::SpriteRenderer* renderer; //그래픽컴포넌트 스프라이트 렌더러 활용
	public:
		VOID Initialize(FLOAT Init_Posx , FLOAT Init_Posy, Character_Type Type);
		VOID Release();
		BOOL Update(const FLOAT& deltaTime,FLOAT BulletSpeed ,RECT* CharacterRect);
		VOID Draw();

		VOID Set_Bulletlife(BOOL Bulletlife) { islife = Bulletlife; };
		VOID Reset_Bullet_HitArea() { BulletRect = { 0,0,0,0 };	}
		BOOL Get_Bulletlife() { return islife; };

		//플레이어 방향에 따른 총알 좌표 및 방향 설정
		VOID Set_BulletDir(Direction CharacterDir)
		{
			switch (CharacterDir)
			{
			case Direction::Right:
				BulletDir = 1;

				transform->position.x += Right_Pointx;
				break;
			case Direction::Left:
				BulletDir = -1;
				transform->position.x += Left_Pointx;
				break;
			}
		}
		VOID Set_BulletPositionX(FLOAT Point_X)
		{
			transform->position.x = Point_X;
		}
		VOID Set_BulletPositionY(FLOAT Point_Y)
		{
			transform->position.y = Point_Y + Gun_Pointy;
		}

		//Enemy -> Player ,Player->Enemy
		BOOL RectCheck(RECT* characterHitRect)
		{
			RECT result_Rect = {0,0,0,0};
			if (IntersectRect(&result_Rect, characterHitRect, &BulletRect))
			{
				islife = FALSE;
				transform->position = Init_Pos;
				BulletRect = { 0,0,0,0 };//
				return TRUE;
			}
			return FALSE;
		}

	};
}
#endif //!BULLET_H