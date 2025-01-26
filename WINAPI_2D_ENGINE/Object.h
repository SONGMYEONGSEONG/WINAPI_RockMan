#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함
#include "GameMecro.h"
#include "ScroolManager.h"

namespace GAME
{
	class Object : public ENGINE::GameObject
	{
	protected:
		ENGINE::SpriteRenderer* renderer;

		FLOAT Init_Point_X; //오브젝트 시작위치 
		FLOAT Init_Point_Y; //오브젝트 시작위치
		ObjectType Obj_Type;//오브젝트 타입 

		SIZE BlockSize; //블럭의 폭,너비
		RECT HitRect; // 블럭의 RECt 자료형 (충돌체크시 사용)
		RECT interact_area;//상호작용 영역 

	public:
		Object() {};
		virtual ~Object() {};

		virtual VOID Initialize(FLOAT Pos_x,FLOAT Pos_y,FLOAT right,FLOAT bottom, UINT Obj_Type) abstract;
		virtual VOID Release()abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw()abstract;


		VOID SetPoint(FLOAT Pos_x, FLOAT Pos_y, FLOAT right, FLOAT bottom)
		{
			Init_Point_X = Pos_x;
			Init_Point_Y = Pos_y;
			transform->position.x = Pos_x;
			transform->position.y = Pos_y;
			BlockSize = { (LONG)(right * transform->scale.x) , (LONG)(bottom * transform->scale.y) };
			HitRect = {
				(LONG)(Pos_x),
				(LONG)(Pos_y),
				(LONG)(Pos_x + right),
				(LONG)(Pos_y + bottom)
			};
		}

		VOID Object_Scrool(const FLOAT& deltaTime)
		{
			FLOAT ScroolPoint = ScroolMgr->Get_ScroolPoint();
			// 움직인 플레이어 스크롤 + 블록의 위치 = 오브젝트의 위치 
			transform->position.x = ScroolPoint + Init_Point_X;

			//transform의 position좌표를 renderer의 pos 변수에 대입 코드
			Object::renderer->Operate(this);

			HitRect.left = transform->position.x;
			HitRect.right = transform->position.x + BlockSize.cx;
			HitRect.top = transform->position.y;
			HitRect.bottom = transform->position.y + +BlockSize.cy;


		}


		RECT* Get_BlockRect()
		{
			return &HitRect;
		}
		ObjectType Get_ObjType()
		{
			return  Obj_Type;
		}
		virtual BOOL Interact_Obj(const FLOAT& deltaTime, BOOL ObjState)abstract;
		virtual RECT* Get_InteractRect()abstract;
	};
}

