#include "database.h"

std::ostream &operator<<(std::ostream &os, const Entry &e)
{
    os << e.date << ' ' << e.event;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Entry> &v)
{
    for(const Entry e : v)
        os <<  e;
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
    return left.date < right.date;
}

bool operator>(const Entry &left, const Entry &right)
{
    return left.date > right.date;
}

bool operator==(const Entry &e, const std::string &str)
{
    return e.event == str;
}

bool operator!=(const Entry &e, const std::string &str)
{
    return e.event != str;
}

Database::Database()
{

}

void Database::Add(const Date& date, const std::string& event)
{
    if(eventsUnique.count({date, event}) == 0){
        eventsByDate[date].push_back(event);
        eventsUnique.insert({date, event});
    }
}

void Database::Print(std::ostream& os) const
{
    for(const auto& pair : eventsByDate)
        if(!pair.second.empty())
            for(const std::string& e : pair.second)
                os << pair.first << ' ' << e << std::endl;
}

std::string Database::Last(const Date &date) const
{
    std::string s = "";
    if (date == Date{0,0,0}) throw std::invalid_argument("No entries");;
    auto firstGreaterIt = eventsByDate.upper_bound(date);
    if (firstGreaterIt!=begin(eventsByDate))
    {
        auto lastNotGreaterIt = prev(firstGreaterIt);
        if ( ! lastNotGreaterIt->second.empty() ) {
            std::stringstream ss;
            ss << lastNotGreaterIt->first;
            s = ss.str() + " " + lastNotGreaterIt->second.back();
        }
        return s;
    } else throw std::invalid_argument("No entries");
}








