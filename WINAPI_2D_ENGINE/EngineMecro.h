#pragma comment(lib, "msimg32.lib")
#include <crtdbg.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "Component.h"

#ifndef ENGINE_MECRO_H
#define ENGINE_MECRO_H

#ifndef DEL
#define DEL(a) if(a) {delete a; a = nullptr;} //delete 매크로 함수
#endif //!DEL
#ifndef REL_DEL
#define REL_DEL(a) if (a) { a->Release(); delete a; a = nullptr; } //Release() 함수 홀출 후 delete
#endif //!REL_DEL

namespace ENGINE
{
	enum //무명(no name) enum,게임 엔진에 사용되는 여러 기본 데이터 설정 값,
	{
		ClientSize_Width = 800,
		ClientSize_Height = 600,
		Client_Per_X = 50,
		Client_Per_Y = 50,/*0~100%*/
		FPS = 120/*초당 프레임*/
	};

	//interface 복습할것
	__interface Scene
	{
		VOID Initialize();
		VOID Release();
		VOID Update(CONST FLOAT& deltaTime);
		VOID Draw();
	};


}

#endif //!ENGINE_MECRO_H