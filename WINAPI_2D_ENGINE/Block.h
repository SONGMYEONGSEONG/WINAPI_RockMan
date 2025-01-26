#pragma once
#include "GameMecro.h"
#include "Object.h"

#include "SceneManager.h" // TEST,DC 호출용도
#include "ResourceManager.h"

namespace GAME
{
	class Block : public Object
	{
	protected:
		

	public:
		Block() {};
		virtual ~Block() {};

		// Object을(를) 통해 상속됨
		virtual VOID Initialize(FLOAT Pos_x, FLOAT Pos_y,FLOAT right, FLOAT bottom, UINT Obj_Type) override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;

		virtual RECT* Get_InteractRect()override { return nullptr; };
		virtual BOOL Interact_Obj(const FLOAT& deltaTime, BOOL ObjState)override { return TRUE; };
		

	
	};

}
