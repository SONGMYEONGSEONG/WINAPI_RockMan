#include "Player.h"

VOID GAME::Player::Idle(const FLOAT& deltaTime)
{
    //Jump(deltaTime);
    if (Jumpdir == JumpState::None)
    {
        switch (dir)
        {
        case Direction::Right:anim->Play(Idle_Right); break;
        case Direction::Left:anim->Play(Idle_Left); break;
        }
    }

    return VOID();
}

VOID GAME::Player::Player_Move(const FLOAT& deltaTime)
{
    if (!Object_Move_Check())
    {
        BOOL Scrool_Lock_Start = ScroolMgr->Get_ScroolPoint() > 0 && transform->position.x <= Init_X;
        BOOL Scrool_Lock_Door = ScroolMgr->Get_ScroolPoint() < -3800 && transform->position.x >= Init_X;

        //��ũ�Ѷ� üũ 
        if (Scrool_Lock_Start || Scrool_Lock_Door)
        {
            ScroolMgr->Set_ScroolLock(TRUE);
        }
        else
        {
            ScroolMgr->Set_ScroolLock(FALSE);
        }

        //�÷��̾� ��ǥ �̵� 
        switch (ScroolMgr->Get_ScroolLock())
        {
        case TRUE:
            switch (dir)
            {
            case Direction::Right:
                transform->position.x += Player_Speed * deltaTime;
                break;

            case Direction::Left:
                transform->position.x -= Player_Speed * deltaTime;

                break;
            }
            return VOID();

        case FALSE:
            transform->position.x = Init_X;
            //��ũ�� �������� ����⶧���� ������ �����Ӹ�ŭ ���ڰ�����
            switch (dir)
            {
            case Direction::Right:
                ScroolMgr->Update_Scrool(Player_Speed, -Player_Speed * deltaTime);
                break;

            case Direction::Left:
                ScroolMgr->Update_Scrool(Player_Speed, Player_Speed * deltaTime);
                break;
            }
        }

    }
}

VOID GAME::Player::Player_Move_animation(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::Right:
        anim->Play(Move_Rignt);
        break;
    case Direction::Left:
        anim->Play(Move_Left);
        break;
    }
}
VOID GAME::Player::Move(const FLOAT& deltaTime)
{
    //Jump(deltaTime);
    if (Jumpdir == JumpState::None)
    {
        Player_Move_animation(deltaTime);
    }

    Player_Speed = Speed;
    Player_Move(deltaTime);

    return VOID();
}

VOID GAME::Player::Jump_Animation()
{
    //���� �ִϸ��̼� �ε��� 
    switch (dir)
    {
    case Direction::Right:
        anim->Play(Jump_Right);
        break;
    case Direction::Left:
        anim->Play(Jump_Left);
        break;
    }
    //!���� �ִϸ��̼� �ε��� 
}


VOID GAME::Player::Jump(const FLOAT& deltaTime)
{
    //���� ���鶧 ���� �ö󰡴� ��ɸ� �߰��ѵ�, �������°� �߷��ڵ带 �����ϸ�
    //�ڵ����� ������ �����ȴ�.

    //������ �ְ���̸� �����ϰ� �ؾߵȴ�, ���� ��ǥ�� ���������ʰ��ؾߵȴ�.
    switch (Jumpdir)
    {
    case JumpState::Up:
        Jump_Distance += JumpSpeed * deltaTime; //������ ���� ���� ����
        transform->position.y -= JumpSpeed * deltaTime; //y�� ��ġ ����

        if (Jump_Distance >= 160  || Ceiling_Check()) // ���� �ִ���� ���� enumȭ �Ұ� 
        {
            transform->position.y = clamp(transform->position.y, 0, 500);
            Jumpdir = JumpState::Down;
            Jump_Distance = 0; //���� ���� �ʱ�ȭ
        }
        break;
    }

    if (Jumpdir == JumpState::Up)
    {
        Jump_Animation();
        Get_anim()->Stop();
    }
}


VOID GAME::Player::Attack(const FLOAT& deltaTime)
{
    if (Attack_CoolTime * 0.1 <= Attack_Time)
    {
    switch (dir)
    {
    case Direction::Right:
        if (Jumpdir == JumpState::None)
        {
            anim->Play(Attack_Right);
        }
        else
        {
            anim->Play(Attack_Jump_Right);
        }
        break;
    case Direction::Left:
        if (Jumpdir == JumpState::None)
        {
            anim->Play(Attack_Left);
        }
        else
        {
            anim->Play(Attack_Jump_Left);
        }
        break;
    }
   Get_anim()->Stop();

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
   else
   {
       Attack_Time += deltaTime;
   }
   return VOID();
}

VOID GAME::Player::Hit(const FLOAT& deltaTime)
{
    static FLOAT Hit_elipsed = 0;
    Hit_elipsed += deltaTime;
   
    switch (dir)
    {
    case Direction::Right:
        anim->Play(Hit_Right);
        break;
    case Direction::Left:
        anim->Play(Hit_left);
        break;
    }

    //���ݿ� �°ų� �浹�� �ڷ� �и�
    Player_Speed = -Hit_Speed;
    Player_Move(deltaTime);

    //�浹 �ִϸ��̼��� 1.0���Ŀ� ������ idle state�� ����
    if (Hit_elipsed >= 1.0f)
    {
        Hit_elipsed = 0;
        Grace = TRUE;
        StateChange(IdleState::Instance());
    }
    return VOID();
}

VOID GAME::Player::Player_Status_Init()
{
    pCurrState = IdleState::Instance();
    state = State::Idle;
    CharState = CharacterState::None;
    dir = Direction::Right;
    Jumpdir = JumpState::None;
    Health_Point = Player_HP;
    transform->position = { Init_X, Init_Y };//�÷��̾� ������ġ
    Attack_Check = FALSE;
    Grace = FALSE;
    Death = FALSE;
}

VOID GAME::Player::Player_Init()
{
    Player_Status_Init();
    Attack_Time = Attack_CoolTime;
    Life = Player_Life;
}

BOOL GAME::Player::Initialize()
{
    //ENGINE���� ������ ������Ʈ Init
    //pPlayerTr = GetTransform(); //Ʈ������ ������ ���� ȣ��(��ȯ)
    /*
    static_cast<�ٲٷ��� �ϴ� Ÿ��>(���);
    static_cast<new_type>(expression)

    Ư¡ (�������� ��ȯ ������ Ÿ���� ��ȯ�Ѵ�)
    */
 /*   pPlayerSr = static_cast<ENGINE::SpriteRenderer*>(GetComponent(ENGINE::ComponentType::Graphic));*/

    Player_Init();

    for (int i = 0; i < arrBullet.size(); i++)
    {
        arrBullet[i] = new Bullet;
        //�Ѿ˳����� ��ġ ����(�÷��̾� , enumȭ �Ұ�)
        arrBullet[i]->Initialize(450,0, Type);
    }

    //���ڸŴ����� ������ ���ҽ� �ε�
    ENGINE::ResourceMgr->Load("RockMan.bmp");

    //��Ʈ�� �̹��� �������� 
    renderer = new ENGINE::SpriteRenderer("RockMan.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    ENGINE::InputComponent* input = new  ENGINE::InputComponent;
    //���ٽ� ���(���ٽ� ��ü�� �Լ�) , �Լ������ͷ� ���ٽ� ��ü�� ȣ���ϴ°� 
    //[ĸ��] (�Ű�����(��������)) {�Լ� ����} (ȣ�� ����(��������)) ;
    //[] () {} : �Լ��� ����⸸ �Ѱ� . [] () {} () : �Լ��� ����� ȣ���Ѱ� ;
    //ĸ�� : ���� �ܺο� ���� �Ǿ��ִ� ����,����� ���� ���ο��� ������
    // ������ : ��纯��,����� �Ű������� ���ѱ涧 ��� 
    //ĸ�Ĵ� ������ ������ ĸ�� [&] , ����� ĸ���ϴ³� ���� [�����̸�]
    /*input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });*/
   
    //��������� Ű�� ���ε� �ϴ°� 
    input->AddBinding(VK_LEFT, [&]() { if (state == State::Idle) { dir = Direction::Left; CharState = CharacterState::Move; }}, [&]() {CharState = CharacterState::None; });
    input->AddBinding(VK_RIGHT, [&]() { if (state == State::Idle) { dir = Direction::Right; CharState = CharacterState::Move; } }, [&]() { CharState = CharacterState::None; });
    input->AddBinding(VK_SPACE, [&]() { if (Jumpdir == JumpState::None) { Jumpdir = JumpState::Up; } }, [&]() {});
    input->AddBinding(ATTACK_BUTTON, [&]() { CharState = CharacterState::Attack; }, [&]() { CharState = CharacterState::None; }); //����Ű z
    AddComponent(input);

    return true;
}

VOID GAME::Player::Release()
{
    int arr_size = arrBullet.size();
    for (int i = 0; i < arr_size; i++)
    {
        delete arrBullet[i];
        arrBullet[i] = nullptr;
    }

    return VOID();
}

VOID GAME::Player::Player_HitCheck()
{
    BOOL Hit_State_Check = state != State::Hit && Grace == FALSE;

    RECT result_Rect = { 0,0,0,0 };
    // ������ Hit���ߴ��� üũ 
    for (Enemy* E : EnemyMgr->Get_EnemyList())
    {
        if (Hit_State_Check)
        {
            //Enemy > Player �����Ѱ�� (�Ѿ� or �������浹)
            if (E->Get_AttackCheck() || IntersectRect(&result_Rect, &HitArea, E->Get_HitArea()))
            {
                UINT Attack_Damage = E->Get_Bullet_Attack();//�� �Ѿ� ������
                Health_Point -= Attack_Damage;

                //���� ������ �÷��̾��� ü���� �ʰ������� clampó��
                if (Health_Point < Attack_Damage) { Health_Point = 0; }

                StateChange(HitState::Instance());
            }
        }
        E->ReSet_AttackCheck();
    }

}

VOID GAME::Player::Player_Bullet(const FLOAT& deltaTime)
{
    //�Ѿ� ��� ���� �� �Ѿ��� ������ �¾Ҵ��� üũ 
    for (Bullet* b : arrBullet)
    {
        b->Update(deltaTime, Bullet_Speed, &HitArea);
        for (Enemy* E : EnemyMgr->Get_EnemyList())
        {
            if (b->RectCheck(E->Get_HitArea()))
            {
                E->Set_HItCheck();
            }
        }
    }
}

VOID GAME::Player::Player_Rect_Set()
{ 
    SIZE PlayerSize = renderer->GetDrawSize();

    HitArea.left = (LONG)transform->position.x + 30;
    HitArea.right = (LONG)transform->position.x + PlayerSize.cx - 30;
    HitArea.top = (LONG)transform->position.y - PlayerSize.cy + 20;
    HitArea.bottom = (LONG)transform->position.y;
}

VOID GAME::Player::Player_Death()
{
    //�÷��̾� ���� ���� üũ    //�������� 0�̵Ȱ�� 
    if (transform->position.y > ENGINE::ClientSize_Height + renderer->GetDrawSize().cy
        ||
        Health_Point <= 0)
    {

        ScroolMgr->Reset_ScroolDate();
        Player_Status_Init();
        Life--;

        //�׾����Ƿ� �Ѿ��� ���� ȭ�鿡�� ����
        for (Bullet* b : arrBullet)
        {
            b->Set_Bulletlife(FALSE);
            b->Reset_Bullet_HitArea();
        }

        EnemyMgr->Reset();

        //�÷��̾� ����� 0�̸� stage1 Scene ����
        if (Life <= 0)
        {
            ENGINE::SceneMgr->LoadScene("Title");
        }
    }
}

VOID GAME::Player::Player_Interact(const FLOAT& deltaTime)
{
    RECT result_Rect = { 0,0,0,0 };
    for (Object* obj : ObjectMgr->Get_BlockObjectList())
    {
        if (obj->Get_ObjType() == ObjectType::Door_Obj)
        {
            //�÷��̿� hit���� <> ������Ʈ(Door)Ÿ�� interact���� �浹üũ
            if (IntersectRect(&result_Rect, &HitArea, obj->Get_InteractRect()))
            {
                StateChange(StoryState::Instance());
            }
        }
    }


}

VOID GAME::Player::Update(const FLOAT& deltaTime)
{
    Operate(this);//���簴ü�� ������Ʈ�� ���� ���� �ϴ°�

    UIGameMgr->Get_UIScene(0)->Set_PlayerHealthCount(Health_Point);
    UIGameMgr->Get_UIScene(0)->Set_PlayerLifeCount(Life);

    //�÷��̾��� ���� �� ��ũ�� ��� ���θ� ��ũ�ѸŴ������� ���� 
    ScroolMgr->Update_Scrool(Player_Speed);

    //FSM ��ü ����
    pCurrState->Excute(this, deltaTime);

    Player_Bullet(deltaTime);

    Player_Rect_Set();

    //�����Ҷ� update �ۿ��� ȣ���ص� ����.
    Player_Interact(deltaTime);

    //���� �Ҷ� ��ȣ�ۿ� �ȿ� hitcheck
    Player_HitCheck();

    //�ǰ��� �����ð� ���� �Լ� 
    static FLOAT Grace_Period = 0;
    if (Grace)
    {
        Grace_Period += deltaTime;
        if (Grace_Period >= Grace_Time)
        {
            Grace_Period = 0;
            Grace = FALSE;
        }
    }

    //�÷��̾��� ����ü�� �� ��������� UIMgr�� ���� 
    Player_Death();

    return VOID();
}

VOID GAME::Player::Draw()
{
    renderer->Draw();
    for (Bullet* b : arrBullet)
    {
        b->Draw();
    }

    /*Debug*/
    if (GetKeyState(VK_F11))
    {
        std::string ScroolPoint(std::to_string(ScroolMgr->Get_ScroolPoint()));

        
        
        Rectangle(ENGINE::SceneMgr->GetBackDC(), HitArea.left, HitArea.top, HitArea.right, HitArea.bottom);
        TextOutA(ENGINE::SceneMgr->GetBackDC(), 0, 0, ScroolPoint.c_str(), ScroolPoint.length());


        int height_roop = ENGINE::ClientSize_Height / 100;
        int width_roop = ENGINE::ClientSize_Width / 100;

        for (int width = 0; width < width_roop; width++)
        {
            MoveToEx(ENGINE::SceneMgr->GetBackDC(), width*100, 0, NULL);
            LineTo(ENGINE::SceneMgr->GetBackDC(), width*100, ENGINE::ClientSize_Height);
        }
        

        for (int height = 0; height < height_roop; height++)
        {
            MoveToEx(ENGINE::SceneMgr->GetBackDC(), 0, height*100, NULL);
            LineTo(ENGINE::SceneMgr->GetBackDC(), ENGINE::ClientSize_Width, height * 100);
        }

    }
    /*!Debug*/
    return VOID();
}

VOID GAME::Player::StateChange(FSMState* pState)
{
    pCurrState->Exit(this);
    pCurrState = pState;
    pCurrState->Enter(this);
}

/*Idle State*/
VOID GAME::IdleState::Enter(Character* character)
{
    if (character->Get_State() != State::Idle)
    {
        character->Set_State(State::Idle);
    }
}

VOID GAME::IdleState::Excute(Character* character, const FLOAT& deltaTime)
{
    //������ Idle FSM�϶� �������� ȣ�Ⱑ��
    character->Jump(deltaTime);

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

VOID GAME::IdleState::Exit(Character* character)
{
    return VOID();
}
/*!Idle State*/

/*Hit State*/
VOID GAME::HitState::Enter(Character* character)
{
    if (character->Get_State() != State::Hit)
    {
        character->Set_State(State::Hit);
    }
}

VOID GAME::HitState::Excute(Character* character, const FLOAT& deltaTime)
{
    character->Hit(deltaTime);//�ǰݽ� �ִϸ��̼� 

    //�߷��ڵ� 
    //������Ʈ �������� �߷��ڵ� ����ް��ؾߵ� ���� ����ȹ޾Ƽ� ������Ʈ ������ ��������������
    character->Gravity_Down(deltaTime);

    return VOID();
}

VOID GAME::HitState::Exit(Character* character)
{
    character->Set_CharState(CharacterState::None);
    character->Set_JumpState(JumpState::None) ;
    return VOID();
}
/*!Hit State*/

/*Story State*/
VOID GAME::StoryState::Enter(Character* character)
{
    if (character->Get_State() != State::Story)
    {
        character->Set_State(State::Story);
    }
}

VOID GAME::StoryState::Excute(Character* character, const FLOAT& deltaTime)
{
    Block* Door_Obj = ObjectMgr->Get_BlockObject(0);
    static UINT32 Door_Num = 0;

    switch (Door_Num)
    {
    case 0:
        if (Door_Obj->Interact_Obj(deltaTime, TRUE))
        {
            Door_Num++;
        }
            
        break; 
    case 1:
        if (character->GetTransform()->position.x > ENGINE::ClientSize_Width)
        {
            Door_Num++;
            return VOID();
        }
        character->GetTransform()->position.x += 200 * deltaTime;
        character->Player_Move_animation(deltaTime);
        break;
    case 2:
        // ���丮 �����̳� ��� ������ �� 
        if (Door_Obj->Interact_Obj(deltaTime, FALSE))
        {
            Door_Num = 0;
            ENGINE::SceneMgr->LoadScene("Clear");
            return VOID();
        }
        break; 
    }


    //�߷��ڵ� 
    //������Ʈ �������� �߷��ڵ� ����ް��ؾߵ� ���� ����ȹ޾Ƽ� ������Ʈ ������ ��������������
    character->Gravity_Down(deltaTime);

    return VOID();
}

VOID GAME::StoryState::Exit(Character* character)
{
    character->Set_CharState(CharacterState::None);
    character->Set_JumpState(JumpState::None);
    return VOID();
}
/*!Hit State*/