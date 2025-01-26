//�ڵ� �����ؾߵ�, �𸣴� ��ɾ� ���� 

#include "ResourceManager.h"
#include <fstream> //����(���ҽ�) �ҷ����� 
#include <io.h> // access()

// c++17 �̻��� ��� #include<filesystem>���
// ���� ������Ʈ c++14 ����� 
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
		// 0 : ���� �� ���丮�� ���� ����.
		// 2 : ���� ���� ���� ����.
		// 4 : �б� ���� ���� ����.
		// 6 : �б�,���� ���ٰ��� ����.
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
		// directory_iterator : ���丮(����) ���� ���� �� ������ ã�´�, ���� ���丮�� Ž������ �ʴ´�.
		for (const auto& file : directory_iterator(defaultPath + directoryName))
		{
			path = file.path();
			if (".bmp" != path.extension().u8string()) continue; //��Ʈ�� ���ҽ����� �ε�.

			name = path.u8string();
			name.replace(name.find(defaultPath), strlen(defaultPath), ""); //Load()���� defaultPath�� �߰��Ͽ� ���� ������ ���ڿ����� ���� 

			if (nullptr != GetBitmap(name)) continue; //�̹� ������ �ִ� ������ �ε忡�� ����
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