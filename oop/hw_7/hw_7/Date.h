#ifndef __Date_H__
#define __Date_H__
#include <iostream>

class Date {
public:
    Date();
    Date(int d, int m, int y);
    ~Date();
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    friend std::istream& operator>> (std::istream& in, Date& date);
    friend std::ostream& operator<< (std::ostream& out, const Date& date);
private:
    int day;
    int month;
    int year;
};
#endif // __Date_H__