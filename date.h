#ifndef DATE_H
#define DATE_H
#include <istream>

Date ParseDate(const std::istringstream &is);

class Date
{
public:
    Date(int, int, int);
    const int _year, _month, _day;
};
    std::ostream &operator <<(std::ostream &os, const Date date);
    bool operator <(const Date date1, const Date date2);
    bool operator >(const Date date1, const Date date2);
    bool operator ==(const Date date1, const Date date2);
    bool operator !=(const Date date1, const Date date2);
    bool operator <=(const Date date1, const Date date2);
    bool operator >=(const Date date1, const Date date2);

#endif // DATE_H
