#pragma once
#include "GameMecro.h"
#include "Object.h"

#include "SceneManager.h" // TEST,DC ȣ��뵵
#include "ResourceManager.h"

namespace GAME
{
	class Ground : public Object
	{
	private:


	public:

		// Object��(��) ���� ��ӵ�
		virtual VOID Initialize(FLOAT Pos_x, FLOAT Pos_y, FLOAT right, FLOAT bottom) override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;

		RECT* Get_BlockRect()
		{
			return &BlockRect;
		}
	};

}
