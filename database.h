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
    std::set<Entry> eventsUnique;

public:
    Database();
    void Add(const Date&, const std::string&);
    void Print(std::ostream&)const;
    template<typename Pred>
    int RemoveIf(Pred pred){
        int total = 0;
        for (auto& entry : eventsByDate){
            int count = 0;
            const Date& date = entry.first;
            auto bound = std::stable_partition(entry.second.begin(),
                                               entry.second.end(),
                                               [date, pred](const std::string& event){
                return !pred(date, event);
            });
            int del = std::distance(bound, entry.second.end());
            for(int i = 0; i < del; ++i) {
                if(!entry.second.empty()) {
                    Entry e{date, entry.second.back()};
                    eventsUnique.erase(e);
                    entry.second.pop_back();
                    ++count;
                }
                else
                    eventsByDate.erase(date);
            }
            total += count;
            if(entry.second.empty())
                eventsByDate.erase(date);
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
