#include "Bullet.h"

VOID GAME::Bullet::Initialize(FLOAT Init_Posx, FLOAT Init_Posy , Character_Type Type)
{
	islife = FALSE;
    BulletDir = 0;

    Init_Pos = { Init_Posx, Init_Posy };
    transform->position = Init_Pos;

    std::string Bullet_res;

    //���ҽ� �ε�
    switch (Type)
    {
    case Character_Type::METOL:
        Bullet_res = "Bullet_Metol.bmp";
        transform->scale *= 3.0f;
        break;
    case Character_Type::TOWER:
        Bullet_res = "Bullet_Tower.bmp";
        break;
    default: //Player
        Bullet_res = "Bullet.bmp";
        transform->scale *= 3.0f;
        break;
    }

    ENGINE::ResourceMgr->Load(Bullet_res);

    //��Ʈ�� �̹��� �������� 
    renderer = new ENGINE::SpriteRenderer(Bullet_res.c_str());
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);

    //�Ѿ� ��,�ʺ� �� �Ѿ� �浹���� init 
    BulletSize = renderer->GetDrawSize();
    BulletRect = {
        (LONG)transform->position.x ,
        (LONG)transform->position.y - BulletSize.cy,
        (LONG)transform->position.x + BulletSize.cx,
        (LONG)transform->position.y  };
}

VOID GAME::Bullet::Release()
{
    return VOID();
}

BOOL GAME::Bullet::Update(const FLOAT& deltaTime, FLOAT BulletSpeed,RECT* CharacterRect)
{
    Operate(this); //���簴ü�� ������Ʈ�� ���� ���� �ϴ°�

    switch (islife)
    {
    case TRUE:
        //Set_BulletPositionX(BulletDir);
        //�浹���� x��ǥ ��ġ deltatime ���� 
        //�÷��̾��� �̵��� ��ũ�ѸŴ����� ������ �޾Ƽ� ����������
        //�÷��̾� �̵��� �Ѿ��� ������ �����ϰ� �ؾߵ� 
        transform->position.x += (deltaTime * BulletSpeed) * BulletDir;

        //��ũ�� �̵��ÿ� �Ѿ˼ӵ� ���� 
        //200.0f ��ũ�� �ӵ� (�÷��̾� �ӵ�)
        switch (ScroolMgr->Get_ScroolDir())
        {
        case ScrollDirection::Left:
            transform->position.x -= (deltaTime * ScroolMgr->Get_ScroolSpeed()) ;
            break;
        case ScrollDirection::Right:
            transform->position.x += (deltaTime * ScroolMgr->Get_ScroolSpeed()) ;
            break;
        }
        
        //�浹���� update 
        BulletRect.left = (LONG)transform->position.x;
        BulletRect.right = (LONG)transform->position.x + BulletSize.cx;
        BulletRect.bottom = (LONG)transform->position.y;
        BulletRect.top = (LONG)transform->position.y - BulletSize.cy;
        
    }

    //���� ���� ���� ��� �Ѿ� ����� ,
   //���߿� ���� ������� ������ ó�� �� ������� �����ؾ���
    if (transform->position.x >= ENGINE::ClientSize_Width 
        || transform->position.x <= 1.0f)
    {
        islife = FALSE;
        transform->position = Init_Pos;
        BulletRect = { 0,0,0,0 };//
    }

    return FALSE;
}


VOID GAME::Bullet::Draw()
{
    if (islife)
    {
        renderer->Draw();
      
    }

    if (GetKeyState(VK_F11))
    {
        Rectangle(ENGINE::SceneMgr->GetBackDC(), BulletRect.left, BulletRect.top, BulletRect.right, BulletRect.bottom);
    }

    return VOID();
}

