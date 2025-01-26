#pragma once
#include <fstream> // object-block 객체 좌표 저장소 (.txt)
#include <vector>
#include <cassert> // vector index 초과시 검출 헤더 

#include "Singleton.h"
#include "GameMecro.h"
#include "Player.h" // Enemy 객체는 플레이어의 Rect를 알아야되기 떄문에 추가

//적 클래스 헤더 추가 
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
		VOID Reset();//플레이어 사망시 몹들 위치 초기화하는 코드 

		Enemy* Get_EnemyIndex(UINT index)
		{
			//에러검출용 디버깅 코드
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

