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
    template<typename F>
    int RemoveIf(F f){
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
