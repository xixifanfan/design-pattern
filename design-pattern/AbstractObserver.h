#pragma once
#include <memory>
#include <string>
#include <list>
#include <iostream>
/*
* �۲���ģʽ
*/
//����۲��߶���
class AbstractObserver;
//���󱻹۲���
class AbstractSubject
{
protected:
    std::string subName;//���۲��߶�������
    bool state;//���۲���״̬
    std::list<std::shared_ptr<AbstractObserver>>obsList;//�۲��߶���
public:
    AbstractSubject(const std::string& name, bool state)noexcept :subName(name), state(state) {}
    virtual ~AbstractSubject() = default;
    //��ӹ۲���
    virtual void attach(std::shared_ptr<AbstractObserver>) = 0;
    //���ٹ۲���
    virtual void detach(std::shared_ptr<AbstractObserver>) = 0;
    //֪ͨ���й۲���
    virtual void notifyAll() = 0;
    virtual const std::string& getName()noexcept { return subName; }
    virtual bool getState()noexcept { return state; }
};
//����۲���
class AbstractObserver
{
protected:
    std::string obsName;//�۲�����
    std::shared_ptr<AbstractSubject>subPtr;//���۲��߶���
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
/*---------------------------------------����------------------------------------------------*/
//����۲���
class Observer :AbstractObserver
{
public:
    Observer(const std::string& name="unknown", std::shared_ptr<AbstractSubject>ptr = nullptr)noexcept:AbstractObserver(name,ptr){}
    ~Observer() = default;
    void show()override
    { 
        if (!subPtr)
        {
            std::cout << "�ù۲���δ�۲��κζ���" << "\n";
        }
        else
        {
            std::cout << "�۲������ƣ�" << getName() <<"�����۲������ƣ�"<<subPtr->getName()
                <<"�����۲�Ķ���״̬Ϊ��" << std::boolalpha << subPtr->getState() << '\n';
        }
    }
};
//���屻�۲����
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
            std::cout << ptr->getName() << "��ʼ�۲챻�۲��ߣ�" << subName << "��" << '\n';
            obsList.push_back(ptr);
        }
        else
        {
            std::cout << ptr->getName() << "���ڹ۲챻�۲��ߣ�" << subName << "��" << '\n';
        }
    }
    //���ٹ۲���
    void detach(std::shared_ptr<AbstractObserver>ptr)noexcept override
    {
        auto it = std::find(obsList.begin(), obsList.end(), ptr);
        if (it == obsList.end())
        {
            std::cout << ptr->getName() << "δ�۲챻�۲��ߣ�" << subName << "��" << '\n';
        }
        else
        {
            std::cout << ptr->getName() << "ȡ���۲챻�۲��ߣ�" << subName << "��" << '\n';
            obsList.remove(ptr);
        }
    }
    //֪ͨ���й۲���
    void notifyAll()noexcept override
    {
        for (auto& obs : obsList)
        {
            obs->show();
        }
    }
};