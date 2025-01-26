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


    //���� �浹�� �ٷ� ���ݻ��·� ����
    if (Object_Move_Check())
    {
        Distance_Count = 0;
        CharState = CharacterState::Attack;
        return VOID();
    }

    //�� = �� * �� 
    Distance_Count += Speed * deltaTime; //Move�����϶� ������ �ѰŸ� 
    switch (dir)
    {
    case Direction::Right:
        Metol_Distance += Speed * deltaTime;
        break;

    case Direction::Left:
        Metol_Distance -= Speed * deltaTime;
    }

    //�����Ÿ� �̵��� FMS state ��ȯ
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
         //������Ÿ���� �������� �Ѿ��� �츲(update�Լ����� �۵�)
         for (Bullet* b : arrBullet)
         {
             if (!b->Get_Bulletlife())
             {
                 b->Set_Bulletlife(TRUE);//�Ѿ� �߻��(true)
                 b->Set_BulletPositionX(transform->position.x);//���� �߻��� ������ x��ǥ�� ������
                 b->Set_BulletPositionY(transform->position.y);//���� �߻��� ������ y��ǥ�� ������
                 b->Set_BulletDir(dir);//�Ѿ˿��� �÷��̾� ���� ����
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

    //���ڸŴ����� ������ ���ҽ� �ε�
    ENGINE::ResourceMgr->Load("Metol.bmp");
    //��Ʈ�� �̹��� �������� 
    renderer = new ENGINE::SpriteRenderer("Metol.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    //�Ѿ� �Ҵ�
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
    //��ũ�� ���� ���ȭ�� left,bottom���� 
    FLOAT ScroolPoint = -ScroolMgr->Get_ScroolPoint() + ENGINE::ClientSize_Width;
    if (Enemy_Init_Point.x < ScroolPoint && Health_Point > 0)
    {
        islife = true;
    }

    if (islife)
    {
        //Test -Enemy HP Decreases Code
        Enemy::Hit_Check();

        //FSM ��ü ����
        pCurrState->Excute(this, deltaTime);
        Operate(this);//���簴ü�� ������Ʈ�� ���� ���� �ϴ°�

        if (islife)
        {
            Enemy::Position_Update(Metol_Distance);

            SIZE MetolSize = renderer->GetDrawSize();
            Enemy::HitArea_Update(MetolSize, 15, 15, -15, 0);
        }


    }

    //�Ѿ� ���
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
    //�߷��ڵ� 
//������Ʈ �������� �߷��ڵ� ����ް��ؾߵ� ���� ����ȹ޾Ƽ� ������Ʈ ������ ��������������
    character->Gravity_Down(deltaTime);
    return VOID();
}

VOID GAME::Metol_IdleState::Exit(Character* character)
{
    return VOID();
}
/*!Idle State*/
