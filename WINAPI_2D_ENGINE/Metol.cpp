#include "Metol.h"

VOID GAME::Metol::Idle(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::Right:anim->Play_One(Idle_Right); break;
    case Direction::Left:anim->Play_One(Idle_Left); break;
    }

    if (State_Change_CoolTime <= State_elipsed_Time)
    {
        State_elipsed_Time = 0;
        CharState = CharacterState::Move;
        return VOID();
    }
    State_elipsed_Time += deltaTime;

    return VOID();
}

VOID GAME::Metol::Move(const FLOAT& deltaTime)
{

    switch (dir)
    {
    case Direction::Right:
        anim->Play_One(Move_Rignt);
        break;

    case Direction::Left:
        anim->Play_One(Move_Left);
        break;
    }
    Hit(deltaTime);


    //벽에 충돌시 바로 공격상태로 진입
    if (Object_Move_Check())
    {
        Distance_Count = 0;
        CharState = CharacterState::Attack;
        return VOID();
    }

    //거 = 시 * 속 
    Distance_Count += Speed * deltaTime; //Move상태일때 움직인 총거리 
    switch (dir)
    {
    case Direction::Right:
        Metol_Distance += Speed * deltaTime;
        break;

    case Direction::Left:
        Metol_Distance -= Speed * deltaTime;
    }

    //일정거리 이동시 FMS state 전환
    if (Move_Distance <= Distance_Count)
    {
        Distance_Count = 0;
        CharState = CharacterState::Attack;
    }


}

VOID GAME::Metol::Attack(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::Right:
        anim->Play_One(Move_Rignt);
        break;

    case Direction::Left:
        anim->Play_One(Move_Left);
        break;
    }
    Hit(deltaTime);

    Attack_Time += deltaTime;
    State_elipsed_Time += deltaTime;
     if (Attack_Time >= Attack_CoolTime)
     {
         //공격쿨타임이 지났으면 총알을 살림(update함수에서 작동)
         for (Bullet* b : arrBullet)
         {
             if (!b->Get_Bulletlife())
             {
                 b->Set_Bulletlife(TRUE);//총알 발사됨(true)
                 b->Set_BulletPositionX(transform->position.x);//현재 발사한 시점의 x좌표를 가져옴
                 b->Set_BulletPositionY(transform->position.y);//현재 발사한 시점의 y좌표를 가져옴
                 b->Set_BulletDir(dir);//총알에게 플레이어 방향 전달
                 break;
             }
         }

         Attack_Time = 0;
     }

    if (State_Change_CoolTime <= State_elipsed_Time )
    {
        Attack_Time = Attack_CoolTime;
        State_elipsed_Time = 0;
        CharState = CharacterState::None;
    }


    return VOID();
}

VOID GAME::Metol::Hit(const FLOAT& deltaTime)
{
    if (bEnemy_Hit)
    {
        switch (dir)
        {
        case Direction::Right:
            anim->Play_One(Hit_Right);
            break;

        case Direction::Left:
            anim->Play_One(Hit_Left);
            break;
        }
        bEnemy_Hit = FALSE;
    }
}

VOID GAME::Metol::Jump(const FLOAT& deltaTime)
{
    return VOID();
}

VOID GAME::Metol::Enemy_Init()
{
    pCurrState = Metol_IdleState::Instance();
    state = State::Idle;
    CharState = CharacterState::None;
    dir = Direction::Left;
    Jumpdir = JumpState::None;
    Metol_Distance = 0;
    Distance_Count = 0;
    State_elipsed_Time = 0;
    Health_Point = Enemy_Metol_Life;
    Attack_Time = Attack_CoolTime;
    Attack_Check = FALSE;
    Bullet_Attack = Enemy_Metol_Bullet_Attack;
    Body_Attack = Enemy_Metol_Attack;
    islife = FALSE;
    bEnemy_Hit = FALSE;
    HitArea = { 0,0,0,0 };
    
    transform->position = Enemy_Init_Point;
    for (Bullet* b : arrBullet)
    {
        b->Set_Bulletlife(FALSE);
        b->Reset_Bullet_HitArea();
    }
}

BOOL GAME::Metol::Initialize()
{
    Type = Character_Type::METOL;

    //리솟매니저에 저장한 리소스 로드
    ENGINE::ResourceMgr->Load("Metol.bmp");
    //비트맵 이미지 렌더링후 
    renderer = new ENGINE::SpriteRenderer("Metol.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    //총알 할당
    for (int i = 0; i < arrBullet.size(); i++)
    {
        arrBullet[i] = new Bullet;
        arrBullet[i]->Initialize(transform->position.x, 0, Type);
    }

    Enemy_Init();
    return TRUE;
}

VOID GAME::Metol::Release()
{
    int arr_size = arrBullet.size();
    for (int i = 0; i < arr_size; i++)
    {
        delete arrBullet[i];
        arrBullet[i] = nullptr;
    }

    return VOID();
}

VOID GAME::Metol::Update(const FLOAT& deltaTime)
{
    //스크롤 기준 배경화면 left,bottom기준 
    FLOAT ScroolPoint = -ScroolMgr->Get_ScroolPoint() + ENGINE::ClientSize_Width;
    if (Enemy_Init_Point.x < ScroolPoint && Health_Point > 0)
    {
        islife = true;
    }

    if (islife)
    {
        //Test -Enemy HP Decreases Code
        Enemy::Hit_Check();

        //FSM 객체 진입
        pCurrState->Excute(this, deltaTime);
        Operate(this);//현재객체의 컴포넌트를 전부 실행 하는것

        if (islife)
        {
            Enemy::Position_Update(Metol_Distance);

            SIZE MetolSize = renderer->GetDrawSize();
            Enemy::HitArea_Update(MetolSize, 15, 15, -15, 0);
        }


    }

    //총알 사용
    for (Bullet* b : arrBullet)
    {
        b->Update(deltaTime, Enemy_Metol_Bullet_Speed, Enemy_Target_HitAtea);
        if (b->RectCheck(Enemy_Target_HitAtea))
        {
            Attack_Check = TRUE;
        }
    }

    return VOID();
}

VOID GAME::Metol::Draw()
{
    if (islife)
    {
        renderer->Draw();
    }

    for (Bullet* b : arrBullet)
    {
        b->Draw();
    }

    /*Debug*/
    if (GetKeyState(VK_F11))
    {
        Rectangle(ENGINE::SceneMgr->GetBackDC(), HitArea.left, HitArea.top, HitArea.right, HitArea.bottom);
        if (CharState == CharacterState::None)
        {
            Ellipse(ENGINE::SceneMgr->GetBackDC(), HitArea.left, HitArea.top-20, HitArea.right, HitArea.bottom - 20);
        }
    }
    /*!Debug*/
    return VOID();
}

VOID GAME::Metol::StateChange(FSMState*)
{
    return VOID();
}

/*Idle State*/
VOID GAME::Metol_IdleState::Enter(Character* character)
{
    if (character->Get_State() != State::Idle)
    {
        character->Set_State(State::Idle);
    }
}

VOID GAME::Metol_IdleState::Excute(Character* character, const FLOAT& deltaTime)
{
    switch (character->Get_CharState())
    {
    case CharacterState::None:
        character->Idle(deltaTime);
        break;
    case CharacterState::Move:
        character->Move(deltaTime);
        break;
    case CharacterState::Attack:
        character->Attack(deltaTime);
        break;
    }
    //중력코드 
//오브젝트 위에서도 중력코드 적용받게해야됨 지금 적용안받아서 오브젝트 위에서 점프가되질않음
    character->Gravity_Down(deltaTime);
    return VOID();
}

VOID GAME::Metol_IdleState::Exit(Character* character)
{
    return VOID();
}
/*!Idle State*/
