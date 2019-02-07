#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <date.h>
#include <memory>

enum LogicalOperation{
    And,
    Or
};

enum Comparison{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node{
public:
    virtual bool Evaluate(const Date& date, const std::string& event) = 0;
    virtual ~Node(){}
};

class EmptyNode{
public:
    bool Evaluate(const Date& date, const std::string& event) {return  true;}
};

class DateComparisonNode{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    virtual bool Evaluate(const Date& date, const std::string& event)override;

private:
    Comparison _cmp;
    Date _data;
};

class EventComparisonNode{
public:
    EventComparisonNode(const Date& date, const std::string& event);
    virtual bool Evaluate(const Date& date, const std::string& event)override;

private:
    Comparison _cmp;
    std::string _event;
};
class LogicalOperationNode{
public:
    LogicalOperationNode(const LogicalOperation& lop,
                         const shared_ptr<Node>& nodeLeft,
                         const shared_ptr<Node>& nodeRight);
    virtual bool Evaluate(const Date& date, const std::string& event)override;

private:
    LogicalOperation _lop;
    shared_ptr<Node> _nodeLeft;
    shared_ptr<Node> _nodeRight;
};

#endif // NODE_H
