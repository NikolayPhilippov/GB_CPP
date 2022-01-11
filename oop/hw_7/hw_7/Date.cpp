#include "Date.h"

Date::Date() = default;
Date::Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {  };
Date::~Date() {  };
void Date::setDay(int d) { day = d; };
void Date::setMonth(int m) { month = m; };
void Date::setYear(int y) { year = y; };
int Date::getDay() const { return day; };
int Date::getMonth() const { return month; };
int Date::getYear() const { return year; };
std::istream& operator>> (std::istream& in, Date& date) {

    do {
        std::cout << "¬ведите день : ";
        in >> date.day;
    } while ( !(date.day >= 1 && date.day <= 30) );

    do {
        std::cout << "¬ведите мес€ц : ";
        in >> date.month;
    } while ( !(date.month >= 1 && date.month <= 12) );

    do {
        std::cout << "¬ведите год : ";
        in >> date.year;
    } while ( !(date.year >= 2000 && date.year <= 2050) );

    return in;
};

std::ostream& operator<< (std::ostream& out, const Date& date) {
    out << "ƒата : " << date.day << " / " << date.month << " / " << date.year;
    return out;
};