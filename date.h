#ifndef DATE_H
#define DATE_H
#include <istream>

Date ParseDate(const std::istringstream &is);

class Date
{
public:
    Date();
};

#endif // DATE_H
