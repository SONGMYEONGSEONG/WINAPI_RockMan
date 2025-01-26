#include "EngineMecro.h"
#ifndef BITMAP_H
#define BITMAP_H

//�÷��� ����
// : ��Ʈ������ �Ͽ� ���� ������ ����� �������ְ� �ϴ°� (�ϳ��� ��ȯ������ ������Ȳ�� �ľ��Ҽ�����)
// ��Ŀ�� ���� ������ ���÷� ���
// ex) INT flag; = 3; => ������( 0011); 
//     enum flag_status
//		{
//			live = 1 << 0; (0001);
//			score_gain = 1 <<2 (0010);
//		}
//		~~~~~~~~~~~~~~
//		(flag�� ���ڰ����� �޾ƿ�)
// 		if (flag & flag_status::live) �÷��̾� ��������� �Լ� ����  ; 
//			: 0011 & 0001 => xxx1 : �÷��̾� ��������
//		if (flag & flag_status::score_gain) ������ ȹ���ϸ� �Լ� ����  ; 
//			: 0011 & 0010 => xx10 : �÷��̾� ���� ȹ�漺������


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
		RECT src; //source(�ҽ��� ����)
		POINT pivot;
		INT pivotType;
		
	public:
		~Bitmap();

		VOID Load(std::string name); // ��Ʈ�� �̹����� �ε��ϰ� �޸� DC�� �����.
		VOID SetDrawSize(UINT width = 0U, UINT height = 0U); // ���� ȭ�鿡 ��µ�ũ�⸦ ����.
		VOID ResetSize() { dest = origin; } // ȭ�鿡 ��µǴ� ũ�⸦ ���� ũ��� ����.

		//Sprites �̹����� ������ ��ġ���� ������ ũ�⸸ŭ ���.
		VOID SliceSource(UINT cx, UINT cy, UINT width, UINT height)
		{
			src = { (LONG)cx,(LONG)cy ,(LONG)width ,(LONG)height };
		}
		VOID SetPivot(INT pivot);
		VOID ResetPivot() { pivot = { 0 , 0 }; }

		BOOL BitBlt(INT32 x, INT32 y); //���� �״�� ȭ�鿡 ���.
		BOOL StretchBlt(INT32 x, INT32 y); //������ ��� ������� �����Ͽ� ���.
		//������ ��� ������� �����ϰ� ���� ���� ���� ó���Ͽ� ���.
		BOOL TransparentBlt(INT32 x, INT32 y, UINT Transparent = RGB(255, 0, 255));

		BOOL TransparentBlt_Object(INT32 x, INT32 y, FLOAT width, FLOAT height, UINT Transparent = RGB(255, 0, 255));

		SIZE GetBitmapSize() CONST { return origin; } //���� ��Ʈ���� ũ��.
		SIZE GetSize() CONST { return dest;  } //ȭ�鿡 ��µǴ� �̹����� ũ��.
	}; //class Bitmap
	
}
#endif // !BITMAP_H

