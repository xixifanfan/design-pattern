#pragma once
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <functional>
/*
* ������ģʽ
*/
//��������
class Handle
{
protected:
    using NextHandle = std::shared_ptr<Handle>;
    using WrappedFun = std::function<void>;
    std::list<NextHandle> nexts;//�洢�¼�������
    std::string hdlName;//����������
public:
    explicit Handle(const std::string& name)noexcept:hdlName(name){}
    virtual ~Handle() = default;
    //�����һ��������
    virtual void addNextHandle(const NextHandle&) = 0;
    //��������
    virtual void solveRequest(const WrappedFun&) = 0;
};