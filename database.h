#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <ostream>
#include <vector>
#include "date.h"
#include <set>
#include <map>
#include <algorithm>

struct Entry{
    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream&, const Entry&);
std::ostream& operator<<(std::ostream&, const std::vector<Entry>&);
std::ostream& operator<<(std::ostream&, const std::vector<std::string>&);

bool operator<(const Entry&, const Entry&);
bool operator>(const Entry&, const Entry&);
bool operator==(const Entry&, const Entry&);
bool operator!=(const Entry&, const Entry&);
bool operator==(const Entry&, const std::string&);
bool operator!=(const Entry&, const std::string&);

class Database
{
    std::map<Date, std::vector<std::string> > eventsByDate;
    std::map<Date, std::set<std::string>> eventsUnique;

public:
    Database();
    void Add(const Date&, const std::string&);
    void Print(std::ostream&)const;

    template<typename Pred>
    int RemoveIf(Pred pred){
        int total = 0;
        for (auto& entry : eventsByDate){
            const Date& date = entry.first;
            auto bound = std::remove_if(entry.second.begin(),
                                               entry.second.end(),
                                               [=](const std::string& event){
                bool b = pred(date, event);
                if(b)eventsUnique[date].erase(event);
                return b;
            });
            int del = std::distance(bound, entry.second.end());
            if(del > 0){
                entry.second.erase(bound, entry.second.end());
            }
            if(eventsByDate[date].empty()){
                eventsByDate.erase(date);
                eventsUnique.erase(date);
            }
            total += del;
        }
        return total;
    }
    template<typename F>
    std::vector<Entry> FindIf(F f)const{
        std::vector<Entry> res;
        for(const auto& pair : eventsByDate)
            for(const std::string& event : pair.second)
                if(f(pair.first, event))res.push_back({pair.first, event});
        return res;
    }
    std::string Last(const Date&)const;
};

#endif // DATABASE_H
