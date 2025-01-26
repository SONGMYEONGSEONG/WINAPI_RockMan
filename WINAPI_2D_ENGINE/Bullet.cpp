#include "Bullet.h"

VOID GAME::Bullet::Initialize(FLOAT Init_Posx, FLOAT Init_Posy , Character_Type Type)
{
	islife = FALSE;
    BulletDir = 0;

    Init_Pos = { Init_Posx, Init_Posy };
    transform->position = Init_Pos;

    std::string Bullet_res;

    //리소스 로드
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

    //비트맵 이미지 렌더링후 
    renderer = new ENGINE::SpriteRenderer(Bullet_res.c_str());
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);

    //총알 폭,너비 및 총알 충돌영역 init 
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
    Operate(this); //현재객체의 컴포넌트를 전부 실행 하는것

    switch (islife)
    {
    case TRUE:
        //Set_BulletPositionX(BulletDir);
        //충돌영역 x좌표 위치 deltatime 갱신 
        //플레이어의 이동에 스크롤매니저가 영향을 받아서 문제가생김
        //플레이어 이동과 총알은 별개로 동작하게 해야됨 
        transform->position.x += (deltaTime * BulletSpeed) * BulletDir;

        //스크롤 이동시에 총알속도 보정 
        //200.0f 스크롤 속도 (플레이엉 속도)
        switch (ScroolMgr->Get_ScroolDir())
        {
        case ScrollDirection::Left:
            transform->position.x -= (deltaTime * ScroolMgr->Get_ScroolSpeed()) ;
            break;
        case ScrollDirection::Right:
            transform->position.x += (deltaTime * ScroolMgr->Get_ScroolSpeed()) ;
            break;
        }
        
        //충돌영역 update 
        BulletRect.left = (LONG)transform->position.x;
        BulletRect.right = (LONG)transform->position.x + BulletSize.cx;
        BulletRect.bottom = (LONG)transform->position.y;
        BulletRect.top = (LONG)transform->position.y - BulletSize.cy;
        
    }

    //벽에 끝에 닿을 경우 총알 사라짐 ,
   //나중에 몹에 닿을경우 데미지 처리 및 사라지게 구현해야함
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

