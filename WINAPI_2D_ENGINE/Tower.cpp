#include "Tower.h"


VOID GAME::Tower::Idle(const FLOAT& deltaTime)
{
    //플레이어 방향을 확인후 그쪽으로 방향이 전환되야함 
    //이 행동은 Idle일때만 동작해야됨 
    bool Tower_Pos_Check = transform->position.x < ENGINE::ClientSize_Width * 0.5f;

    switch (Tower_Pos_Check)
    {
    case TRUE:
        dir = Direction::Right;
        anim->Play_One(Idle_Right); 
        break;
    case FALSE:
        dir = Direction::Left;
        anim->Play_One(Idle_Left); 
        break;
    }
    Hit(deltaTime);

    if (State_Change_CoolTime <= State_elipsed_Time)
    {
        State_elipsed_Time = 0;
        CharState = CharacterState::Attack;
        return VOID();
    }
    State_elipsed_Time += deltaTime;

    return VOID();
}


VOID GAME::Tower::Attack(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::Right:anim->Play_One(Attack_Right); break;
    case Direction::Left:anim->Play_One(Attack_Left); break;
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

    if (State_Change_CoolTime <= State_elipsed_Time)
    {
        Attack_Time = Attack_CoolTime;
        State_elipsed_Time = 0;
        CharState = CharacterState::None;
    }


    return VOID();
}

VOID GAME::Tower::Hit(const FLOAT& deltaTime)
{
    if (bEnemy_Hit)
    {
        switch (dir)
        {
        case Direction::Right:
            anim->Play_One(Idle_Hit_Right);
            break;

        case Direction::Left:
            anim->Play_One(Idle_Hit_Left);
            break;
        }
        bEnemy_Hit = FALSE;
    }
}

VOID GAME::Tower::Jump(const FLOAT& deltaTime)
{
    return VOID();
}

VOID GAME::Tower::Enemy_Init()
{
    pCurrState = Tower_IdleState::Instance();
    state = State::Idle;
    CharState = CharacterState::None;
    dir = Direction::Left;
    Jumpdir = JumpState::None;
    State_elipsed_Time = 1;
    Health_Point = Enemy_Tower_Life;
    Attack_Time = Attack_CoolTime;
    Attack_Check = FALSE;
    Bullet_Attack = Enemy_Tower_Bullet_Attack;
    Body_Attack = Enemy_Tower_Attack;
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

BOOL GAME::Tower::Initialize()
{
    Type = Character_Type::TOWER;

    //리솟매니저에 저장한 리소스 로드
    ENGINE::ResourceMgr->Load("Tower.bmp");
    //비트맵 이미지 렌더링후 
    renderer = new ENGINE::SpriteRenderer("Tower.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x*3, transform->scale.y*3);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    //총알 할당
    for (int i = 0; i < arrBullet.size(); i++)
    {
        arrBullet[i] = new Bullet;
        arrBullet[i]->Initialize(transform->position.x, 0,Type);
    }

    Enemy_Init();
    return TRUE;
}

VOID GAME::Tower::Release()
{
    int arr_size = arrBullet.size();
    for (int i = 0; i < arr_size; i++)
    {
        delete arrBullet[i];
        arrBullet[i] = nullptr;
    }

    return VOID();
}

VOID GAME::Tower::Update(const FLOAT& deltaTime)
{
    //스크롤 기준 배경화면 left,bottom기준 
    FLOAT ScroolPoint = -ScroolMgr->Get_ScroolPoint() + ENGINE::ClientSize_Width;
    if (Enemy_Init_Point.x < ScroolPoint && Health_Point > 0)
    {
        islife = true;
    }

    if (islife)
    {
        
        Enemy::Hit_Check();

        //FSM 객체 진입
        pCurrState->Excute(this, deltaTime);
        Operate(this);//현재객체의 컴포넌트를 전부 실행 하는것

        if (islife)
        {
            Enemy::Position_Update();

            //Tower Rect영역(HitArea) 정의 
            SIZE TowerSize = renderer->GetDrawSize();
            HitArea_Update(TowerSize, 0, 0, 0, 0);
        }
    }


    //총알 사용
    for (Bullet* b : arrBullet)
    {
        b->Update(deltaTime, Enemy_Tower_Bullet_Speed, Enemy_Target_HitAtea);
        if (b->RectCheck(Enemy_Target_HitAtea))
        {
            Attack_Check = TRUE;
        }
    }
    return VOID();
}

VOID GAME::Tower::Draw()
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
    }
    /*!Debug*/
    return VOID();
}

VOID GAME::Tower::StateChange(FSMState*)
{
    return VOID();
}

/*Idle State*/
VOID GAME::Tower_IdleState::Enter(Character* character)
{
    if (character->Get_State() != State::Idle)
    {
        character->Set_State(State::Idle);
    }
}

VOID GAME::Tower_IdleState::Excute(Character* character, const FLOAT& deltaTime)
{
    switch (character->Get_CharState())
    {
    case CharacterState::None:
        character->Idle(deltaTime);
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

VOID GAME::Tower_IdleState::Exit(Character* character)
{
    return VOID();
}
/*!Idle State*/
