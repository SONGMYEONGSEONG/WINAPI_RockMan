////template∂˚ ΩÃ±€≈Ê∆–≈œ ¥ŸΩ√ ∫πΩ¿«“∞Õ 
#include "EngineMecro.h"
#ifndef SINGLETON_H
#define SINGLETON_H
template<typename T>
class Singleton
{
private:
	static T* instance;
protected:
	Singleton() {}
public:
	static T* GetInstance()
	{
		if (nullptr == instance) instance = new T;
		return instance;
	}
	static void Destroy() { DEL(instance); }
};
template<typename T>T* Singleton<T>::instance = nullptr;
#endif // !SINGLETON_H
