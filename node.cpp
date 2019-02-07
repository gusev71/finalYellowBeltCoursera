#include "node.h"

Node::Node()
{

}

bool DateComparisonNode::Evaluate(const Date &date, const string &event)
{
    switch (_cmp) {
    case Less:
        return date < _data;
    case LessOrEqual:
        return (date < _data) || (date == _data);
    case Greater:
        return date > _data;
    case GreaterOrEqual:
        return (date > _data) || (date == _data);
    case Equal:
        return date == _data;
    case NotEqual:
        return date != _data;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event)
{
    if(event == "ignore_event_") return true;
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event)
{

}
