#include "SpriteRenderer.h"
#include "../ResourceManager.h"

namespace ENGINE
{
    SpriteRenderer::SpriteRenderer(LPCSTR name, UINT divX, UINT divY) : divide({ 1.0f / divX, 1.0f / divY })
    {
        //똑같은 스프라이트res를 사용하면 다른 객체여도 애니메이션 index가 같이 움직이는 버그
        // (metol 객체에서 발생 )
        //원래는 이미지 클래스내에서 각 기능에 맞게 수정이되야함
        //지금은 스프라이트 res를 복사하는 형식으로 진행(포인터 x)
        sprites = ResourceMgr->GetBitmap(name);
        sprite_copy = *sprites;

        //localSize = sprites->GetBitmapSize();
        localSize = sprite_copy.GetBitmapSize();
        localSize.cx *= divide.x;
        localSize.cy *= divide.y;
        size = localSize;
        SetSrc(0, 0);
    }

    VOID SpriteRenderer::SetSrc(UINT cx, UINT cy)
    {
        //sprites->SliceSource(cx * localSize.cx, cy * localSize.cy, localSize.cx, localSize.cy);
        sprite_copy.SliceSource(cx * localSize.cx, cy * localSize.cy, localSize.cx, localSize.cy);
    }

    VOID SpriteRenderer::Operate(GameObject* Owner) 
    {
        //if (sprites) pos = Owner->GetTransform()->position;
        if (&sprite_copy) pos = Owner->GetTransform()->position;
    }

    VOID SpriteRenderer::Reset()
    {
       /* if (sprites)*/
        if (&sprite_copy)
        {
            sprites->ResetSize();
            sprites->ResetPivot();
        }
    }

    VOID SpriteRenderer::SetScale(UINT cx, UINT cy)
    {
        size = { (LONG)(localSize.cx * cx), (LONG)(localSize.cy * cy) };
        /*sprites->SetDrawSize(size.cx, size.cy);*/
        sprite_copy.SetDrawSize(size.cx, size.cy);
    }

    VOID SpriteRenderer::Draw()
    {
        //if (sprites) sprites->TransparentBlt(pos.x, pos.y);
        if (&sprite_copy) sprite_copy.TransparentBlt(pos.x, pos.y);
    }

    VOID SpriteRenderer::ObjectDraw(FLOAT width, FLOAT height)
    {
        //if (sprites) sprites->TransparentBlt_Object(pos.x, pos.y, width, height);
        if (&sprite_copy) sprite_copy.TransparentBlt_Object(pos.x, pos.y, width, height);
    }
}