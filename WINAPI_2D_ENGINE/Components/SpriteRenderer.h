#include "../Component.h"
#include "../Bitmap.h"

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

namespace ENGINE
{
	class SpriteRenderer : public GrahpicComponent
	{
	private:
		Bitmap sprite_copy;
		Bitmap* sprites;
		SIZE localSize, size;
		Vector2 pos, divide;

	private:
		SpriteRenderer();
	public:
		SpriteRenderer(LPCSTR name, UINT divX = 1, UINT divY = 1);

		VOID SetPivot(INT pivot)/* { if (sprites) sprites->SetPivot(pivot); }*/
		{
			if (&sprite_copy)  sprite_copy.SetPivot(pivot);
		}
		VOID SetSrc(UINT cx, UINT cy);
		SIZE GetDrawSize() { return size; }
		//object 객체 그릴때 사용(block)
		VOID ObjectDraw(FLOAT width, FLOAT height);

		// GrahpicComponent을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;
		virtual VOID SetScale(UINT cx, UINT cy) override;
		virtual VOID Draw() override;
	};
}

#endif // !SPRITE_RENDERER_H