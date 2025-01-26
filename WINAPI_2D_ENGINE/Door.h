#pragma once
#include "GameMecro.h"
#include "Block.h"

#include "SceneManager.h" // TEST,DC 호출용도
#include "ResourceManager.h"

namespace GAME
{
	class Door : public Block
	{
	protected:
		enum Door_Data
		{
			Door_Speed = 200,
		};

	public:
		Door() {};
		virtual ~Door() {};

		// Block을(를) 통해 상속됨
		virtual VOID Initialize(FLOAT Pos_x, FLOAT Pos_y, FLOAT right, FLOAT bottom, UINT Obj_Type) override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;

		virtual RECT* Get_InteractRect()override
		{
			return &interact_area;
		};
		virtual BOOL Interact_Obj(const FLOAT& deltaTime, BOOL DoorState)
		{
			switch (DoorState)
			{
			case TRUE: // 문을 열음
				if (transform->position.y <= -200)
				{
					return TRUE;
				}
				transform->position.y -= Door_Speed * deltaTime;
				break;
			case FALSE: // 문을 닫음
				
				if (transform->position.y >= Init_Point_Y)
				{
					return TRUE;
				}
				transform->position.y += Door_Speed * deltaTime;
				break;
				
			}
			
			return FALSE;
		}


	};

}