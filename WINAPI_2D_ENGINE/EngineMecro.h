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
#define DEL(a) if(a) {delete a; a = nullptr;} //delete ��ũ�� �Լ�
#endif //!DEL
#ifndef REL_DEL
#define REL_DEL(a) if (a) { a->Release(); delete a; a = nullptr; } //Release() �Լ� Ȧ�� �� delete
#endif //!REL_DEL

namespace ENGINE
{
	enum //����(no name) enum,���� ������ ���Ǵ� ���� �⺻ ������ ���� ��,
	{
		ClientSize_Width = 800,
		ClientSize_Height = 600,
		Client_Per_X = 50,
		Client_Per_Y = 50,/*0~100%*/
		FPS = 120/*�ʴ� ������*/
	};

	//interface �����Ұ�
	__interface Scene
	{
		VOID Initialize();
		VOID Release();
		VOID Update(CONST FLOAT& deltaTime);
		VOID Draw();
	};


}

#endif //!ENGINE_MECRO_H