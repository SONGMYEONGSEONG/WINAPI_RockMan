#include "SpriteRenderer.h"
#include "../ResourceManager.h"

namespace ENGINE
{
    SpriteRenderer::SpriteRenderer(LPCSTR name, UINT divX, UINT divY) : divide({ 1.0f / divX, 1.0f / divY })
    {
        //�Ȱ��� ��������Ʈres�� ����ϸ� �ٸ� ��ü���� �ִϸ��̼� index�� ���� �����̴� ����
        // (metol ��ü���� �߻� )
        //������ �̹��� Ŭ���������� �� ��ɿ� �°� �����̵Ǿ���
        //������ ��������Ʈ res�� �����ϴ� �������� ����(������ x)
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