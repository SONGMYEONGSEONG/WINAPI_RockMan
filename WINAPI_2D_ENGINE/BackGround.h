#include "GameMecro.h"
#include "ResourceManager.h" // bitmap 자료형 
#include "ScroolManager.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

namespace GAME
{
	class BackGround
	{
	private:
		BackGround_Type BGType; // 백그라운드 타입 변수 

		INT32 bounds;  //STAGE1의 경계선(이미지 크기 경계선)
		POINT BackGround_Point;	//배경의 좌표
		//상수 enum화 하던가 ,자동화 할수 있게 해야됨
		ENGINE::Bitmap* background;
		enum BackGroundPOINT
		{
			POINT_X = 0,
			POINT_Y =0,
		};
	public:
		// STAGE1을(를) 통해 상속됨
		BOOL Initialize(BackGround_Type Type);
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();

	};
}
#endif //!BACKGUOUND_H
