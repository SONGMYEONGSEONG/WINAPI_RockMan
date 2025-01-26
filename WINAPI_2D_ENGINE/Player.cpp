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

        //스크롤락 체크 
        if (Scrool_Lock_Start || Scrool_Lock_Door)
        {
            ScroolMgr->Set_ScroolLock(TRUE);
        }
        else
        {
            ScroolMgr->Set_ScroolLock(FALSE);
        }

        //플레이어 좌표 이동 
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
            //스크롤 움직임이 생기기때문에 움직인 프레임만큼 인자값전달
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
    //점프 애니메이션 인덱스 
    switch (dir)
    {
    case Direction::Right:
        anim->Play(Jump_Right);
        break;
    case Direction::Left:
        anim->Play(Jump_Left);
        break;
    }
    //!점프 애니메이션 인덱스 
}


VOID GAME::Player::Jump(const FLOAT& deltaTime)
{
    //점프 만들때 위로 올라가는 기능만 추가한뒤, 내려오는건 중력코드를 구현하면
    //자동으로 점프가 구현된다.

    //점프는 최고높이를 설정하고 해야된다, 맵의 좌표로 설정하지않게해야된다.
    switch (Jumpdir)
    {
    case JumpState::Up:
        Jump_Distance += JumpSpeed * deltaTime; //점프의 현재 높이 변수
        transform->position.y -= JumpSpeed * deltaTime; //y축 위치 갱신

        if (Jump_Distance >= 160  || Ceiling_Check()) // 점프 최대높이 설정 enum화 할것 
        {
            transform->position.y = clamp(transform->position.y, 0, 500);
            Jumpdir = JumpState::Down;
            Jump_Distance = 0; //점프 높이 초기화
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

    //공격에 맞거나 충돌시 뒤로 밀림
    Player_Speed = -Hit_Speed;
    Player_Move(deltaTime);

    //충돌 애니메이션은 1.0초후에 종료후 idle state로 변경
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
    transform->position = { Init_X, Init_Y };//플레이어 시작위치
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
    //ENGINE에서 가져온 컴포넌트 Init
    //pPlayerTr = GetTransform(); //트랜스폼 포인터 변수 호출(반환)
    /*
    static_cast<바꾸려고 하는 타입>(대상);
    static_cast<new_type>(expression)

    특징 (논리적으로 변환 가능한 타입을 변환한다)
    */
 /*   pPlayerSr = static_cast<ENGINE::SpriteRenderer*>(GetComponent(ENGINE::ComponentType::Graphic));*/

    Player_Init();

    for (int i = 0; i < arrBullet.size(); i++)
    {
        arrBullet[i] = new Bullet;
        //총알나오는 위치 정의(플레이어 , enum화 할것)
        arrBullet[i]->Initialize(450,0, Type);
    }

    //리솟매니저에 저장한 리소스 로드
    ENGINE::ResourceMgr->Load("RockMan.bmp");

    //비트맵 이미지 렌더링후 
    renderer = new ENGINE::SpriteRenderer("RockMan.bmp", SpritesX, SpritesY);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    AddComponent(renderer);
    AddComponent(anim = new  ENGINE::SpriteAnimation(SpritesX, SpritesY));

    ENGINE::InputComponent* input = new  ENGINE::InputComponent;
    //람다식 사용(람다식 자체가 함수) , 함수포인터로 람다식 자체를 호출하는것 
    //[캡쳐] (매개변수(생략가능)) {함수 동작} (호출 인자(생략가능)) ;
    //[] () {} : 함수를 만들기만 한것 . [] () {} () : 함수를 만들고 호출한것 ;
    //캡쳐 : 람다 외부에 정의 되어있는 변수,상수를 람다 내부에서 사용목적
    // 사용목적 : 모든변수,상수를 매개변수롤 못넘길때 사용 
    //캡쳐는 변수를 참조로 캡쳐 [&] , 복사로 캡쳐하는냐 차이 [변수이름]
    /*input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });*/
   
    //람디식으로 키를 바인딩 하는것 
    input->AddBinding(VK_LEFT, [&]() { if (state == State::Idle) { dir = Direction::Left; CharState = CharacterState::Move; }}, [&]() {CharState = CharacterState::None; });
    input->AddBinding(VK_RIGHT, [&]() { if (state == State::Idle) { dir = Direction::Right; CharState = CharacterState::Move; } }, [&]() { CharState = CharacterState::None; });
    input->AddBinding(VK_SPACE, [&]() { if (Jumpdir == JumpState::None) { Jumpdir = JumpState::Up; } }, [&]() {});
    input->AddBinding(ATTACK_BUTTON, [&]() { CharState = CharacterState::Attack; }, [&]() { CharState = CharacterState::None; }); //공격키 z
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
    // 적에게 Hit당했는지 체크 
    for (Enemy* E : EnemyMgr->Get_EnemyList())
    {
        if (Hit_State_Check)
        {
            //Enemy > Player 공격한경우 (총알 or 몸으로충돌)
            if (E->Get_AttackCheck() || IntersectRect(&result_Rect, &HitArea, E->Get_HitArea()))
            {
                UINT Attack_Damage = E->Get_Bullet_Attack();//적 총알 데미지
                Health_Point -= Attack_Damage;

                //적의 공격이 플레이어의 체력을 초과했을때 clamp처리
                if (Health_Point < Attack_Damage) { Health_Point = 0; }

                StateChange(HitState::Instance());
            }
        }
        E->ReSet_AttackCheck();
    }

}

VOID GAME::Player::Player_Bullet(const FLOAT& deltaTime)
{
    //총알 사용 여부 및 총알이 적에게 맞았는지 체크 
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
    //플레이어 낙사 조건 체크    //에너지가 0이된경우 
    if (transform->position.y > ENGINE::ClientSize_Height + renderer->GetDrawSize().cy
        ||
        Health_Point <= 0)
    {

        ScroolMgr->Reset_ScroolDate();
        Player_Status_Init();
        Life--;

        //죽었으므로 총알을 전부 화면에서 제거
        for (Bullet* b : arrBullet)
        {
            b->Set_Bulletlife(FALSE);
            b->Reset_Bullet_HitArea();
        }

        EnemyMgr->Reset();

        //플레이어 목숨이 0이면 stage1 Scene 종료
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
            //플레이여 hit영역 <> 오브젝트(Door)타입 interact영역 충돌체크
            if (IntersectRect(&result_Rect, &HitArea, obj->Get_InteractRect()))
            {
                StateChange(StoryState::Instance());
            }
        }
    }


}

VOID GAME::Player::Update(const FLOAT& deltaTime)
{
    Operate(this);//현재객체의 컴포넌트를 전부 실행 하는것

    UIGameMgr->Get_UIScene(0)->Set_PlayerHealthCount(Health_Point);
    UIGameMgr->Get_UIScene(0)->Set_PlayerLifeCount(Life);

    //플레이어의 방향 및 스크롤 사용 여부를 스크롤매니저에게 전달 
    ScroolMgr->Update_Scrool(Player_Speed);

    //FSM 객체 진입
    pCurrState->Excute(this, deltaTime);

    Player_Bullet(deltaTime);

    Player_Rect_Set();

    //설계할때 update 밖에서 호출해도 좋다.
    Player_Interact(deltaTime);

    //설계 할때 상호작용 안에 hitcheck
    Player_HitCheck();

    //피격후 무적시간 적용 함수 
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

    //플레이어의 현재체력 및 목숨갯수를 UIMgr에 전달 
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
    //점프는 Idle FSM일때 언제든지 호출가능
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

    //중력코드 
    //오브젝트 위에서도 중력코드 적용받게해야됨 지금 적용안받아서 오브젝트 위에서 점프가되질않음
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
    character->Hit(deltaTime);//피격시 애니메이션 

    //중력코드 
    //오브젝트 위에서도 중력코드 적용받게해야됨 지금 적용안받아서 오브젝트 위에서 점프가되질않음
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
        // 스토리 연출이나 대사 적으면 됨 
        if (Door_Obj->Interact_Obj(deltaTime, FALSE))
        {
            Door_Num = 0;
            ENGINE::SceneMgr->LoadScene("Clear");
            return VOID();
        }
        break; 
    }


    //중력코드 
    //오브젝트 위에서도 중력코드 적용받게해야됨 지금 적용안받아서 오브젝트 위에서 점프가되질않음
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