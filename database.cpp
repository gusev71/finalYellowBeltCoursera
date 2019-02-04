#include "database.h"

Database::Database()
{

}

void Database::Add(const Date& date, const std::string& event)
{
    if(uniqueEvents[date].count(event) == 0){
        eventsByDate[date].push_back(event);
        uniqueEvents[date].insert(event);
    }
}

void Database::Print(std::ostream& os) const
{
    for(const auto& date : eventsByDate)
        if(!date.second.isEmpty())
            for(const std::string& e : date.second)
                os << date.fist << ' ' << e << endl;
}

std::string Database::Last(const Date &) const
{

}
