#pragma once
#include<memory>
/*
* ������ģʽ
*/

//������Խ�ɫ
class AbstractStrategy
{
public:
    AbstractStrategy() = default;
    virtual ~AbstractStrategy() = default;
    //������
    virtual void doIt() = 0;
};
//ִ�н�ɫ
//1��������ָ��
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
    //ѡ�������
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
//2������ָ��
class Context
{
private:
    std::shared_ptr<AbstractStrategy>strategy;
public:
    Context() :strategy(nullptr) {}
    ~Context() = default;
    //ѡ�������
    void choose(std::shared_ptr<AbstractStrategy> concreteStrategy)noexcept
    {
        strategy = concreteStrategy;
    }
    void doIt()const noexcept
    {
        strategy->doIt();
    }
};