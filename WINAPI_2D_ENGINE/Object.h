#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���
#include "GameMecro.h"
#include "ScroolManager.h"

namespace GAME
{
	class Object : public ENGINE::GameObject
	{
	protected:
		ENGINE::SpriteRenderer* renderer;

		FLOAT Init_Point_X; //������Ʈ ������ġ 
		FLOAT Init_Point_Y; //������Ʈ ������ġ
		ObjectType Obj_Type;//������Ʈ Ÿ�� 

		SIZE BlockSize; //���� ��,�ʺ�
		RECT HitRect; // ���� RECt �ڷ��� (�浹üũ�� ���)
		RECT interact_area;//��ȣ�ۿ� ���� 

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
			// ������ �÷��̾� ��ũ�� + ����� ��ġ = ������Ʈ�� ��ġ 
			transform->position.x = ScroolPoint + Init_Point_X;

			//transform�� position��ǥ�� renderer�� pos ������ ���� �ڵ�
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

