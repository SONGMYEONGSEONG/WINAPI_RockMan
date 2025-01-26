#include "EnemyManager.h"
#include <cmath>
VOID GAME::EnemyManager::Initialize(Player* pPlayer)
{
    pPlayerState = pPlayer; //현재 씬에서 진행되는 플레이어 주소가져옴

    std::ifstream Load_Point; // Enemy 좌표
    FLOAT Pos_x, Pos_y; //Enemy 속성
    Load_Point.open("Resources\\EnemyPoint.txt"); // 메모장 파일 오픈
    UINT INDEX = 0;
    UINT Enemy_Type_Num = 0;
    ENGINE::Vector2 Position = { 0, 0 };

    //메모장 기록 형식 
    //EnemyType,point_x,point_y
    while (!Load_Point.eof())
    {
        Load_Point >> Enemy_Type_Num;
        switch ((Character_Type)(Enemy_Type_Num))
        {
        case Character_Type::METOL:
            Enemy_list.push_back(new Metol);
            break;
            //구현예정
        case Character_Type::TOWER:
            Enemy_list.push_back(new Tower);
            break;
        }

        Load_Point >> Position.x;
        Load_Point >> Position.y;
        Enemy_list[INDEX]->SetPosition(Position);
        Enemy_list[INDEX]->Set_Enemy_Init_Point(Position);
        Enemy_list[INDEX]->Initialize();
        //Init 함수가 오버라이딩 되어있어서 위치는 Set함수를 사용하였음 

        INDEX++;
    }


}

VOID GAME::EnemyManager::Release()
{
    for (Enemy* Enemy : Enemy_list)
    {
        REL_DEL(Enemy);
    }
}

VOID GAME::EnemyManager::Update(const FLOAT& deltaTime)
{
    RECT* PlayerHitArea = pPlayerState->Get_HitArea();

    for (Enemy* Enemy : Enemy_list)
    {
        Enemy->Set_PlayerHitArea(PlayerHitArea);
        Enemy->Update(deltaTime);
    }
}

VOID GAME::EnemyManager::Draw()
{
    for (Enemy* Enemy : Enemy_list)
    {
        Enemy->Draw();
    }
}


VOID GAME::EnemyManager::Reset()
{
    for (Enemy* Enemy : Enemy_list)
    {
        Enemy->Enemy_Init();
    }
}
