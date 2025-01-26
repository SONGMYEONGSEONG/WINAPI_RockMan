#include "EnemyManager.h"
#include <cmath>
VOID GAME::EnemyManager::Initialize(Player* pPlayer)
{
    pPlayerState = pPlayer; //���� ������ ����Ǵ� �÷��̾� �ּҰ�����

    std::ifstream Load_Point; // Enemy ��ǥ
    FLOAT Pos_x, Pos_y; //Enemy �Ӽ�
    Load_Point.open("Resources\\EnemyPoint.txt"); // �޸��� ���� ����
    UINT INDEX = 0;
    UINT Enemy_Type_Num = 0;
    ENGINE::Vector2 Position = { 0, 0 };

    //�޸��� ��� ���� 
    //EnemyType,point_x,point_y
    while (!Load_Point.eof())
    {
        Load_Point >> Enemy_Type_Num;
        switch ((Character_Type)(Enemy_Type_Num))
        {
        case Character_Type::METOL:
            Enemy_list.push_back(new Metol);
            break;
            //��������
        case Character_Type::TOWER:
            Enemy_list.push_back(new Tower);
            break;
        }

        Load_Point >> Position.x;
        Load_Point >> Position.y;
        Enemy_list[INDEX]->SetPosition(Position);
        Enemy_list[INDEX]->Set_Enemy_Init_Point(Position);
        Enemy_list[INDEX]->Initialize();
        //Init �Լ��� �������̵� �Ǿ��־ ��ġ�� Set�Լ��� ����Ͽ��� 

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
