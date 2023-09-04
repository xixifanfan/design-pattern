#pragma once
#include <memory>
#include <string>
#include <list>
#include <iostream>
/*
* 观察者模式
*/
//抽象观察者定义
class AbstractObserver;
//抽象被观察者
class AbstractSubject
{
protected:
    std::string subName;//被观察者对象名称
    bool state;//被观察者状态
    std::list<std::shared_ptr<AbstractObserver>>obsList;//观察者对象集
public:
    AbstractSubject(const std::string& name, bool state)noexcept :subName(name), state(state) {}
    virtual ~AbstractSubject() = default;
    //添加观察者
    virtual void attach(std::shared_ptr<AbstractObserver>) = 0;
    //减少观察者
    virtual void detach(std::shared_ptr<AbstractObserver>) = 0;
    //通知所有观察者
    virtual void notifyAll() = 0;
    virtual const std::string& getName()noexcept { return subName; }
    virtual bool getState()noexcept { return state; }
};
//抽象观察者
class AbstractObserver
{
protected:
    std::string obsName;//观察者名
    std::shared_ptr<AbstractSubject>subPtr;//被观察者对象
public:
    AbstractObserver(const std::string& name, std::shared_ptr<AbstractSubject>ptr)noexcept:obsName(name),subPtr(ptr){}
    virtual ~AbstractObserver() = default;
    virtual void show() = 0;
    virtual const std::string& getName() { return obsName; }
    virtual bool operator==(const AbstractObserver& obser)const
    {
        return obsName == obser.obsName && subPtr == obser.subPtr;
    }
};
/*---------------------------------------具体------------------------------------------------*/
//具体观察者
class Observer :AbstractObserver
{
public:
    Observer(const std::string& name="unknown", std::shared_ptr<AbstractSubject>ptr = nullptr)noexcept:AbstractObserver(name,ptr){}
    ~Observer() = default;
    void show()override
    { 
        if (!subPtr)
        {
            std::cout << "该观察者未观察任何对象" << "\n";
        }
        else
        {
            std::cout << "观察者名称：" << getName() <<"；被观察者名称："<<subPtr->getName()
                <<"，被观察的对象状态为：" << std::boolalpha << subPtr->getState() << '\n';
        }
    }
};
//具体被观察对象
class Subject :AbstractSubject
{
public:
    Subject(const std::string& name = "unknown", bool state = false):AbstractSubject(name,state){}
    ~Subject() = default;
    void attach(std::shared_ptr<AbstractObserver>ptr)noexcept override 
    {
        auto it = std::find(obsList.begin(), obsList.end(), ptr);
        if (it == obsList.end())
        {
            std::cout << ptr->getName() << "开始观察被观察者（" << subName << "）" << '\n';
            obsList.push_back(ptr);
        }
        else
        {
            std::cout << ptr->getName() << "正在观察被观察者（" << subName << "）" << '\n';
        }
    }
    //减少观察者
    void detach(std::shared_ptr<AbstractObserver>ptr)noexcept override
    {
        auto it = std::find(obsList.begin(), obsList.end(), ptr);
        if (it == obsList.end())
        {
            std::cout << ptr->getName() << "未观察被观察者（" << subName << "）" << '\n';
        }
        else
        {
            std::cout << ptr->getName() << "取消观察被观察者（" << subName << "）" << '\n';
            obsList.remove(ptr);
        }
    }
    //通知所有观察者
    void notifyAll()noexcept override
    {
        for (auto& obs : obsList)
        {
            obs->show();
        }
    }
};