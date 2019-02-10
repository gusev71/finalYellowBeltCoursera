#include "database.h"
#include <algorithm>

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

int Database::RemoveIf(F f)
{
    int total = 0;
    for (auto& entry : eventsByDate)
    {
        {
            int count = 0, del = 0;
            const Date& date = entry.first;
            auto bound = std::stable_partition(entry.second.begin(),
                                          entry.second.end(),
                                          [date, f](const std::string& event){
                bool Erase = f(date, event);
                return !Erase;
            });
            if(bound != entry.second.end()) del = entry.second.end() - bound;
            for(int i = 0; i < del; ++i) {
                if(!entry.second.empty()) {
                    Entry erz {date, entry.second.back()};
                    eventsUnique.erase(erz);
                    entry.second.pop_back();
                    ++count;
                }
                else {
                    eventsByDate.erase(date);
                }
            }

            total += count;
            if(entry.second.empty()) eventsByDate.erase(date);
        }
    }
    return total;
}

std::vector<Entry> Database::FindIf(F f)
{
    std::vector<Entry> res;
    for(const auto& pair : eventsByDate)
        for(const std::string& event : pair.second)
            if(f(pair.first, event))res.push_back({pair.first, event});
    return res;
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








