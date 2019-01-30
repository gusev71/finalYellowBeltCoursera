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
    std::ostream &operator <<(std::ostream &os, Date date);
    bool operator <(Date date1, Date date2);
    bool operator >(Date date1, Date date2);
    bool operator ==(Date date1, Date date2);
    bool operator !=(Date date1, Date date2);
    bool operator <=(Date date1, Date date2);
    bool operator >=(Date date1, Date date2);

#endif // DATE_H
