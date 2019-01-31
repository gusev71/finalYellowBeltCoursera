#include "date.h"

Date ParseDate(const std::istringstream &is)
{
   int y = 0;
   int m = 0;
   int d = 0;
   char dash = '-';

   is >> y >> dash >> m >> dash >> d;

   return {y, m, d};

}

Date::Date(int y, int m, int d) : _year(y), _month(m), _day(d)
{

}

std::ostream& operator <<(std::ostream &os, const Date date)
{
    char dash = '-';
    string y = to_string(date._year);
    string m = to_string(date.month_);
    string d =to_string(date.day_);

    for(int i = y.length(); i < 4; ++i)
        os << "0";
    os << y << dash;

    if(m.length() == 1) os << "0";
    os << m <<  dash;

    if(d.length() == 1) os << "0";
    os << d;

    return os;
}



bool operator <(const Date date1, const Date date2)
{
    if(date1._year == date2._year){
        if(date1._month == date2._month){
            return date1._day < date2._day;
        }
        else
            return date1._month < date2._month;
    }
    else
        return date1._year < date2._year;
}

bool operator >(const Date date1, const Date date2)
{
    if(date1._year == date2._year){
        if(date1._month == date2._month){
            return date1._day > date2._day;
        }
        else
            return date1._month > date2._month;
    }
    else
        return date1._year > date2._year;
}

bool operator ==(const Date date1, const Date date2)
{
    return date1._month == date2._month
            && date1._month == date2._month
            && date1._day == date2._day;
}

bool operator !=(const Date date1, const Date date2)
{
    return date1._month != date2._month
            || date1._month != date2._month
            || date1._day != date2._day;
}

bool operator <=(const Date date1, const Date date2)
{
    return date1 < date2 || date1 == date2;
}

bool operator >=(const Date date1, const Date date2)
{
    return date1 > date2 || date1 == date2;
}
