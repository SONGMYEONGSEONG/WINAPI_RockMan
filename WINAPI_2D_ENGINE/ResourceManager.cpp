//코드 공부해야됨, 모르는 명령어 많음 

#include "ResourceManager.h"
#include <fstream> //파일(리소스) 불러오기 
#include <io.h> // access()

// c++17 이상의 경우 #include<filesystem>사용
// 현재 프로젝트 c++14 사용중 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem> //directory_iterator()
using namespace std::experimental::filesystem;

namespace ENGINE
{
	ResourceManager::~ResourceManager() { Clear(); }

	VOID ResourceManager::Initialize() { Clear(); }

	BOOL ResourceManager::Load(const std::string& fileName)
	{
		if (fileName.empty()) return FALSE;

		std::string path = defaultPath + fileName;
		// 0 : 파일 및 디렉토리의 존재 유무.
		// 2 : 쓰기 접근 가능 여부.
		// 4 : 읽기 접근 가능 여부.
		// 6 : 읽기,쓰기 접근가능 여부.
		// return : 0(true), -1(false)
		if (0 != _access(path.c_str(), 0)) return FALSE;

		Bitmap* bitmap = new Bitmap;
		bitmap->Load(defaultPath + fileName);
		resources.insert(make_pair(fileName, bitmap));

		return TRUE;
	}

	VOID ResourceManager::LoadALL(const std::string& directoryName)
	{
		v1::path path;
		//path path;
		std::string name;
		// directory_iterator : 디렉토리(폴더) 내의 파일 및 폴더를 찾는다, 하위 디렉토리는 탐색하지 않는다.
		for (const auto& file : directory_iterator(defaultPath + directoryName))
		{
			path = file.path();
			if (".bmp" != path.extension().u8string()) continue; //비트맵 리소스만을 로드.

			name = path.u8string();
			name.replace(name.find(defaultPath), strlen(defaultPath), ""); //Load()에서 defaultPath를 추가하여 쓰기 때문에 문자열에서 제거 

			if (nullptr != GetBitmap(name)) continue; //이미 가지고 있는 파일은 로드에서 제외
			Load(name);
		}
	
	}

	Bitmap* ResourceManager::GetBitmap(const std::string& name)
	{
		std::map<std::string, Bitmap*>::iterator iter = resources.find(name);
		if (resources.end() != iter) return iter->second;
		return nullptr;
	}

	VOID ResourceManager::Clear()
	{
		for (std::pair<std::string, Bitmap*> resource : resources) DEL(resource.second);
		resources.clear();
	}
}//namespace ENGINE