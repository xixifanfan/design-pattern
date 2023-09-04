#pragma once
#include<type_traits>
#include<memory>
#include<mutex>

/*
* 用于继承的单例模式,例如：struct A:Singleton<A>
* 
*/
#if 1

template<typename T,class=typename std::enable_if<!std::is_reference<T>::value>::type>
class Singleton
{
protected:
	~Singleton() = default;
	Singleton()=default;
public:
	Singleton(const Singleton&) = delete;
	Singleton operator=(const Singleton&) = delete;
	static T& getInstance()
	{
		static T instance;
		return instance;
	}
};
#endif 

/*
* 
* c++11线程安全的单例模式（call_once,once_flag,shared_ptr）
*/
#if 0

class Singleton
{
private:
	static std::shared_ptr<Singleton> instance;
	static std::once_flag once;
	
	Singleton() = default;
public:
	~Singleton() = default;
	
	static std::shared_ptr<Singleton> getInstance()
	{
		std::call_once(once, [&] {
			instance = std::make_shared<Singleton>(Singleton());
			});
		return instance;
	}
};
std::shared_ptr<Singleton> Singleton::instance = nullptr;
#endif

/*
* c++11普通版线程安全单例模式（mutext,unique_lock）
*
*/
#if 0
class Singleton
{
private:
	static std::mutex mtx;
	static Singleton* instance;
	struct GC
	{
		~GC() { delete instance; }
	};
	Singleton() = default;
	
	
public:
	~Singleton() = default;

	static Singleton* getInstance()
	{
		if (instance == nullptr)
		{
			std::unique_lock<std::mutex>lock(mtx);
			if (instance == nullptr)
			{
				static GC gc;
				instance = new(std::nothrow) Singleton();
			}
		}
		return instance;
	}
};
std::mutex Singleton::mtx;
Singleton* Singleton::instance = nullptr;
#endif