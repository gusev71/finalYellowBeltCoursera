#include "database.h"

std::ostream &operator<<(std::ostream &os, const Entry &e)
{
    os << e.date << ' ' << e.event;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Entry> &v)
{
    for(const Entry e : v)
        os <<  e << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &events)
{
    for (const std::string& ev : events){
        os << ev << " ";
    }
    return os;
}

bool operator<(const Entry &left, const Entry &right)
{
    if(left.date == right.date)
        return left.event < right.event;
    else
        return left.date < right.date;
}

bool operator>(const Entry &left, const Entry &right)
{
    if(left.date == right.date)
        return left.event > right.event;
    else
        return left.date > right.date;
}

bool operator==(const Entry &e, const std::string &str)
{
    std::stringstream ss;
    ss << e.date << ' ' << e.event;
    return (str == e.event || str == ss.str());
}

bool operator!=(const Entry &e, const std::string &str)
{
    std::stringstream ss;
    ss << e.date << ' ' << e.event;
    return (str != e.event && str != ss.str());
}

bool operator==(const Entry& left, const Entry& right)
{
    return (left.date == right.date) && (left.event == right.event);
}

bool operator!=(const Entry& left, const Entry& right)
{
    return left.date != right.date || left.event != right.event;
}

Database::Database()
{

}

void Database::Add(const Date& date, const std::string& event)
{
    if(eventsUnique[date].count(event) == 0){
        eventsByDate[date].push_back(event);
        eventsUnique[date].insert(event);
    }
}

void Database::Print(std::ostream& os) const
{
    for(const auto& pair : eventsByDate)
        if(!pair.second.empty())
            for(const std::string& e : pair.second)
                os << pair.first << ' ' << e << std::endl;
}

Entry Database::Last(const Date &date) const
{
    if (date < eventsByDate.begin()->first)
        throw std::invalid_argument("No entries");;
    auto firstGreaterIt = eventsByDate.upper_bound(date);
    if(firstGreaterIt != begin(eventsByDate)){
        auto lastNotGreaterIt = prev(firstGreaterIt);
        if(!lastNotGreaterIt->second.empty()){
            return {lastNotGreaterIt->first, lastNotGreaterIt->second.back()};
        }
        throw std::invalid_argument("No entries");
    } else throw std::invalid_argument("No entries");
}
