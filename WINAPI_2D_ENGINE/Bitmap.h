#include "EngineMecro.h"
#ifndef BITMAP_H
#define BITMAP_H

//플래그 연산
// : 비트연산을 하여 여러 종류의 결과를 받을수있게 하는것 (하나의 반환값으로 여러상황을 파악할수있음)
// 서커스 찰리 게임을 예시로 들면
// ex) INT flag; = 3; => 이진법( 0011); 
//     enum flag_status
//		{
//			live = 1 << 0; (0001);
//			score_gain = 1 <<2 (0010);
//		}
//		~~~~~~~~~~~~~~
//		(flag를 인자값으로 받아옴)
// 		if (flag & flag_status::live) 플레이어 살아있으면 함수 동작  ; 
//			: 0011 & 0001 => xxx1 : 플레이어 생존상태
//		if (flag & flag_status::score_gain) 점수를 획득하면 함수 동작  ; 
//			: 0011 & 0010 => xx10 : 플레이어 점수 획득성공상태


namespace ENGINE
{
	//Center 0001 -> 0001 (1)
	//Left 0001 -> 0010 (2)
	//Right 0001 -> 0100 (4)
	//Top 0001 -> 1000 (8)
	//Bottom 0001 -> 0001 0000 (16)
	enum Pivot { Center = 1 << 0, Left = 1 << 1, Right = 1 << 2, Top = 1 << 3, Bottom = 1 << 4, };

	class Bitmap
	{
	private:
		HDC memDC;
		HBITMAP hBitmap;
		SIZE origin, dest;
		RECT src; //source(소스의 약자)
		POINT pivot;
		INT pivotType;
		
	public:
		~Bitmap();

		VOID Load(std::string name); // 비트맵 이미지를 로드하고 메모리 DC를 만든다.
		VOID SetDrawSize(UINT width = 0U, UINT height = 0U); // 실제 화면에 출력될크기를 변경.
		VOID ResetSize() { dest = origin; } // 화면에 출력되는 크기를 원본 크기로 변경.

		//Sprites 이미지의 임의의 위치부터 임의의 크기만큼 출력.
		VOID SliceSource(UINT cx, UINT cy, UINT width, UINT height)
		{
			src = { (LONG)cx,(LONG)cy ,(LONG)width ,(LONG)height };
		}
		VOID SetPivot(INT pivot);
		VOID ResetPivot() { pivot = { 0 , 0 }; }

		BOOL BitBlt(INT32 x, INT32 y); //원본 그대로 화면에 출력.
		BOOL StretchBlt(INT32 x, INT32 y); //설정한 출력 사이즈로 변경하여 출력.
		//설정한 출력 사이즈로 변경하고 지정 색을 투명 처리하여 출력.
		BOOL TransparentBlt(INT32 x, INT32 y, UINT Transparent = RGB(255, 0, 255));

		BOOL TransparentBlt_Object(INT32 x, INT32 y, FLOAT width, FLOAT height, UINT Transparent = RGB(255, 0, 255));

		SIZE GetBitmapSize() CONST { return origin; } //원본 비트맵의 크기.
		SIZE GetSize() CONST { return dest;  } //화면에 출력되는 이미지의 크기.
	}; //class Bitmap
	
}
#endif // !BITMAP_H

