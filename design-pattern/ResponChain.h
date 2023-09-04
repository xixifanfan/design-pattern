#pragma once
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <functional>
/*
* 责任链模式
*/
//任务处理者
class Handle
{
protected:
    using NextHandle = std::shared_ptr<Handle>;
    using WrappedFun = std::function<void>;
    std::list<NextHandle> nexts;//存储下级处理者
    std::string hdlName;//处理者名称
public:
    explicit Handle(const std::string& name)noexcept:hdlName(name){}
    virtual ~Handle() = default;
    //添加下一个处理者
    virtual void addNextHandle(const NextHandle&) = 0;
    //传入请求
    virtual void solveRequest(const WrappedFun&) = 0;
};