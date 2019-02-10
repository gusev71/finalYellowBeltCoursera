#include "node.h"

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

bool LogicalOperationNode::Evaluate(const Date &date, const string &event)
{
    return _lop == LogicalOperation::And
            ? _nodeLeft->Evaluate(date, event) && _nodeRight->Evaluate(date, event)
            : _nodeLeft->Evaluate(date, event) || _nodeRight->Evaluate(date, event);
}
