#include "GameMecro.h"
#include "ResourceManager.h" // bitmap �ڷ��� 
#include "ScroolManager.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

namespace GAME
{
	class BackGround
	{
	private:
		BackGround_Type BGType; // ��׶��� Ÿ�� ���� 

		INT32 bounds;  //STAGE1�� ��輱(�̹��� ũ�� ��輱)
		POINT BackGround_Point;	//����� ��ǥ
		//��� enumȭ �ϴ��� ,�ڵ�ȭ �Ҽ� �ְ� �ؾߵ�
		ENGINE::Bitmap* background;
		enum BackGroundPOINT
		{
			POINT_X = 0,
			POINT_Y =0,
		};
	public:
		// STAGE1��(��) ���� ��ӵ�
		BOOL Initialize(BackGround_Type Type);
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();

	};
}
#endif //!BACKGUOUND_H
