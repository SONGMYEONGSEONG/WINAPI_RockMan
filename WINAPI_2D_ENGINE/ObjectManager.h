#pragma once
#include <fstream> // object-block 객체 좌표 저장소 (.txt)
#include <vector>
#include <cassert> // vector index 초과시 검출 헤더 

#include "Singleton.h"
#include "GameMecro.h"
#include "Block.h"
#include "Door.h"

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

namespace GAME
{
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:
		std::vector<Block*> Object_list;
	public:
		 VOID Initialize() ;
		 VOID Release() ;
		 VOID Update(const FLOAT& deltaTime) ;
		 VOID Draw();

		 std::vector<Block*> Get_BlockObjectList()
		 {
			 return Object_list;
		 }


		Block* Get_BlockObject(UINT index)
		 {
			//에러검출용 디버깅 코드
			assert(index < Object_list.size());

			return Object_list[index];

		 }

		UINT Get_ObjectManagerSize()
		{
			return Object_list.size();
		}
		
		 friend Singleton;
	};
#define ObjectMgr ObjectManager::GetInstance()
}

#endif //!OBJECT_MANAGER_H

