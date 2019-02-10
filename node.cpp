#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date)
    : _cmp(cmp), _data(date) {}

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

EventComparisonNode::EventComparisonNode(const Comparison cmp, const string &event)
    : _cmp(cmp), _event(event){}

bool EventComparisonNode::Evaluate(const Date &date, const string &event)
{
    if(event == "ignore_event_") return true;
    switch (_cmp) {
    case Less:
        return event < _event;
    case LessOrEqual:
        return (event < _event) || (event == _event);
    case Greater:
        return event > _event;
    case GreaterOrEqual:
        return (event > _event) || (event == _event);
    case Equal:
        return event == _event;
    case NotEqual:
        return event != _event;
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &lop,
                                           const shared_ptr<Node> &nodeLeft,
                                           const shared_ptr<Node> &nodeRight)
   : _lop(lop), _nodeLeft(nodeLeft), _nodeRight(nodeRight){}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event)
{
    return _lop == LogicalOperation::And
            ? _nodeLeft->Evaluate(date, event) && _nodeRight->Evaluate(date, event)
            : _nodeLeft->Evaluate(date, event) || _nodeRight->Evaluate(date, event);
}
