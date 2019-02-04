#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <ostream>
#include <vector>
#include "date.h"
#include <set>

struct Entry{
    Date date;
    std::string event;
};

class Database
{
    map<Date, vector<string> > eventsByDate;
    map<Date, set<string> > uniqueEvents;
public:
    Database();
    void Add(const Date&, const std::string&);
    void Print(std::ostream&)const;
    template<typename F> int RemoveIf(F);
    template<typename F> std::vector<Entry> FindIf(F);
    std::string Last(const Date&)const;
};

#endif // DATABASE_H
