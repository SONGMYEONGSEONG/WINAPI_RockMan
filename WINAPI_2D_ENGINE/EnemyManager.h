#pragma once
#include <fstream> // object-block ��ü ��ǥ ����� (.txt)
#include <vector>
#include <cassert> // vector index �ʰ��� ���� ��� 

#include "Singleton.h"
#include "GameMecro.h"
#include "Player.h" // Enemy ��ü�� �÷��̾��� Rect�� �˾ƾߵǱ� ������ �߰�

//�� Ŭ���� ��� �߰� 
#include "Metol.h"
#include "Tower.h"

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

namespace GAME
{
	class Player;
	class EnemyManager : public Singleton<EnemyManager>
	{
	private:
		Player* pPlayerState;
		std::vector<Enemy*> Enemy_list;
	public:
		VOID Initialize(Player* pPlayer);
		VOID Release();
		VOID Update(const FLOAT& deltaTime);
		VOID Draw();
		VOID Reset();//�÷��̾� ����� ���� ��ġ �ʱ�ȭ�ϴ� �ڵ� 

		Enemy* Get_EnemyIndex(UINT index)
		{
			//��������� ����� �ڵ�
			assert(index < Enemy_list.size());
			return Enemy_list[index];
		}

		std::vector<Enemy*> Get_EnemyList() { return Enemy_list; }
		UINT Get_ObjectManagerSize() { return Enemy_list.size(); }

		friend Singleton;
	};
#define EnemyMgr EnemyManager::GetInstance()
}

#endif //!OBJECT_MANAGER_H

