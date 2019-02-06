#ifndef NODE_H
#define NODE_H

#include "token.h"

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
     bool Evaluate(const Date& date, const std::string& event) = 0;
};
class EmptyNode{

};

class DateComparisonNode{
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event);
};

class EventComparisonNode{

};
class LogicalOperationNode{

};
//----------------------------------
class Node
{
public:
    Node();
};

#endif // NODE_H
