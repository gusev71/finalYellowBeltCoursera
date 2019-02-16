#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <ostream>
#include <vector>
#include "date.h"
#include <set>
#include <map>
#include <algorithm>
#include <iostream>

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
    std::map<Date, std::vector<std::string>> eventsByDate;
    std::map<Date, std::set<std::string>> eventsUnique;

public:
    Database();
    void Add(const Date&, const std::string&);
    void Print(std::ostream&)const;

    template<typename Pred>
    int RemoveIf(Pred pred){
        int total = 0;
        auto tmp = eventsByDate;
        for(auto& entry : tmp){
            const Date& date = entry.first;
            auto end = eventsByDate[date].end();
            auto bound = std::stable_partition(eventsByDate[date].begin(),
                                               end,
                                               [=](const std::string& event){
                bool b = pred(date, event);
                if(b)eventsUnique[date].erase(event);
                return !b;
            });
            int del = std::distance(bound, end);
            if(del > 0){
                eventsByDate[date].erase(bound, end);
            }
            if(eventsByDate[date].empty()){
                eventsByDate.erase(date);
                eventsUnique.erase(date);
            }
            total += del;
        }
        return total;
    }
    template<typename Pred>
    std::vector<Entry> FindIf(Pred pred)const{
        std::vector<Entry> res;
        for(const auto& pair : eventsByDate)
            for(const std::string& event : pair.second)
                if(pred(pair.first, event))res.push_back({pair.first, event});
        return res;
    }
    Entry Last(const Date&)const;
};

#endif // DATABASE_H
