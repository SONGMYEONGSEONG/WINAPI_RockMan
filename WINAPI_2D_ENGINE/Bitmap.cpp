#include "Bitmap.h"
#include "SceneManager.h"
namespace ENGINE
{
	Bitmap::~Bitmap()
	{
		DeleteDC(memDC);
		DeleteObject(hBitmap);
	}

	VOID Bitmap::Load(std::string name)
	{
		memDC = CreateCompatibleDC(SceneMgr->GetBackDC()); // �޸�DC ����
		hBitmap = (HBITMAP)LoadImageA(NULL, name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE); //��Ʈ�� �̹��� �ε�
		SelectObject(memDC, hBitmap); //�޸� DC�� ��Ʈ�� �̹��� ����.

		BITMAP BitMap;
		//ī�����,ü��,���� �ڵ� �����ϸ鼭 �ּ� ã�ƺ��� 
		GetObject(hBitmap, sizeof(BITMAP), &BitMap); //��Ʈ���� ���� ���,
		origin.cx = BitMap.bmWidth;//��Ʈ���� ���� ũ�� ����.
		origin.cy = BitMap.bmHeight;
		dest = origin; src = { 0,0,origin.cx,origin.cy }; //ȭ�鿡 �׷��� ũ��� rec�� ����ũ��� ����

		pivot = { 0 , 0 };
		// 0010 (or ��Ʈ ����) 1000 => 1010 (10) 
		pivotType = (Pivot::Left | Pivot::Top);
	}

	VOID Bitmap::SetDrawSize(UINT width, UINT height)
	{
		dest = { (LONG)width,(LONG)height };
		SetPivot(pivotType);
	}

	VOID Bitmap::SetPivot(INT pivot)
	{
		pivotType = pivot;//18

		int halfWidth = dest.cx * 0.5f;
		int halfHeight = dest.cy * 0.5f;
		this->pivot = { -halfWidth,-halfHeight };

		//�÷��� ���� ���� ( ���� ��ü�� pivot�� enum���� ���� ������� ��ġ�Ұ�� ���ǹ� ����)
		if (pivot & Pivot::Left) this->pivot.x += halfWidth;
		if (pivot & Pivot::Right) this->pivot.x += -halfWidth;
		if (pivot & Pivot::Top) this->pivot.y += halfHeight;
		if (pivot & Pivot::Bottom) this->pivot.y += -halfHeight;
	}

	BOOL Bitmap::BitBlt(INT32 x, INT32 y)
	{
		//BOOL BitBlt(HDC hdc,int x,int y,int cx,int cy, HDC hdcSrc,int x1, int y1,DWORD rop);
		return ::BitBlt(SceneMgr->GetBackDC(),pivot.x + x,pivot.y + y, src.right,src.bottom,memDC,src.left,src.top,SRCCOPY);
	}

	BOOL Bitmap::StretchBlt(INT32 x, INT32 y)
	{
		//BOOL StretchBlt(HDC hdcDest,int xDest, int yDest, int wDest,  int hDest,  HDC hdcSrc,int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);
		return ::StretchBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom, SRCCOPY);
	}

	BOOL Bitmap::TransparentBlt(INT32 x, INT32 y,UINT transparent)
	{
		return ::TransparentBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, dest.cx, dest.cy, memDC, src.left, src.top, src.right, src.bottom,transparent );
	}

	BOOL Bitmap::TransparentBlt_Object(INT32 x, INT32 y, FLOAT width, FLOAT height, UINT transparent)
	{
		return ::TransparentBlt(SceneMgr->GetBackDC(), pivot.x + x, pivot.y + y, width, height, memDC, src.left, src.top, src.right, src.bottom, transparent);
	}
} //namespace ENGINE