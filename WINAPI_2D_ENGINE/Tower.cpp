#include "Tower.h"


VOID GAME::Tower::Idle(const FLOAT& deltaTime)
{
    //�÷��̾� ������ Ȯ���� �������� ������ ��ȯ�Ǿ��� 
    //�� �ൿ�� Idle�϶��� �����ؾߵ� 
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

    //���ڸŴ����� ������ ���ҽ� �ε�
    ENGINE::ResourceMgr->Load("Tower.bmp");
    //��Ʈ�� �̹��� �������� 
    renderer = new ENGINE::SpriteRenderer("Tower.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x*3, transform->scale.y*3);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    //�Ѿ� �Ҵ�
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
    //��ũ�� ���� ���ȭ�� left,bottom���� 
    FLOAT ScroolPoint = -ScroolMgr->Get_ScroolPoint() + ENGINE::ClientSize_Width;
    if (Enemy_Init_Point.x < ScroolPoint && Health_Point > 0)
    {
        islife = true;
    }

    if (islife)
    {
        
        Enemy::Hit_Check();

        //FSM ��ü ����
        pCurrState->Excute(this, deltaTime);
        Operate(this);//���簴ü�� ������Ʈ�� ���� ���� �ϴ°�

        if (islife)
        {
            Enemy::Position_Update();

            //Tower Rect����(HitArea) ���� 
            SIZE TowerSize = renderer->GetDrawSize();
            HitArea_Update(TowerSize, 0, 0, 0, 0);
        }
    }


    //�Ѿ� ���
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
    //�߷��ڵ� 
//������Ʈ �������� �߷��ڵ� ����ް��ؾߵ� ���� ����ȹ޾Ƽ� ������Ʈ ������ ��������������
    character->Gravity_Down(deltaTime);
    return VOID();
}

VOID GAME::Tower_IdleState::Exit(Character* character)
{
    return VOID();
}
/*!Idle State*/
