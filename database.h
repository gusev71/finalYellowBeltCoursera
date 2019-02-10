#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <ostream>
#include <vector>
#include "date.h"
#include <set>
#include <map>

using F = bool(*)(const Date& date, const std::string& event);

struct Entry{
    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream&, const Entry&);
std::ostream& operator<<(std::ostream&, const std::vector<Entry>&);
std::ostream& operator<<(std::ostream&, const std::vector<std::string>&);

bool operator<(const Entry&, const Entry&);
bool operator>(const Entry&, const Entry&);
bool operator==(const Entry&, const std::string&);
bool operator!=(const Entry&, const std::string&);

class Database
{
    std::map<Date, std::vector<std::string>> eventsByDate;
    std::set<Entry> eventsUnique;

public:
    Database();
    void Add(const Date&, const std::string&);
    void Print(std::ostream&)const;
    int RemoveIf(F);
    std::vector<Entry> FindIf(F);
    std::string Last(const Date&)const;
};

#endif // DATABASE_H
