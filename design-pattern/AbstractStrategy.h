#pragma once
#include<memory>
/*
* 策略者模式
*/

//抽象策略角色
class AbstractStrategy
{
public:
    AbstractStrategy() = default;
    virtual ~AbstractStrategy() = default;
    //做策略
    virtual void doIt() = 0;
};
//执行角色
//1、非智能指针
#if 0
class Context
{
private:
    AbstractStrategy *strategy;
public:
    Context():strategy(nullptr){}
    ~Context()
    {
        if (strategy == nullptr)return;
        delete strategy;
    }
    //选择策略者
    void choose(AbstractStrategy* concreteStrategy)noexcept
    {
        if (strategy != nullptr)delete strategy;
        strategy = concreteStrategy;
    }
    void doIt()const noexcept
    {
        strategy->doIt();
    }
};
#endif
//2、智能指针
class Context
{
private:
    std::shared_ptr<AbstractStrategy>strategy;
public:
    Context() :strategy(nullptr) {}
    ~Context() = default;
    //选择策略者
    void choose(std::shared_ptr<AbstractStrategy> concreteStrategy)noexcept
    {
        strategy = concreteStrategy;
    }
    void doIt()const noexcept
    {
        strategy->doIt();
    }
};