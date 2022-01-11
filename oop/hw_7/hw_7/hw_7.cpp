#include <iostream>
#include "Date.h"

template<class T>
class smart_ptr
{
private:
    T* m_ptr;
public:
    smart_ptr(T* ptr) : m_ptr(ptr) { };
    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;
    smart_ptr(smart_ptr&& ptr) : m_ptr(ptr.m_ptr) { ptr.m_ptr = nullptr; };
    
    smart_ptr& operator=(smart_ptr&& prt)
    {
        if (&prt == this) {
            return *this;
        }
        delete m_ptr;
        m_ptr = prt.m_ptr;
        prt.m_ptr = nullptr;
        return *this;
    };

    ~smart_ptr()
    { 
        if (m_ptr == NULL) {
            delete m_ptr;
        };
    };

    bool operator!=(const smart_ptr&)
    {
        return m_ptr != NULL;
    }

    T& operator*() const { return *m_ptr; };
    T* operator->() const { return m_ptr; };

};

bool dateBiger(const smart_ptr<Date>& date1, const smart_ptr<Date>& date2)
{
    return ((date1->getYear() * 365 + date1->getMonth() * 30 + date1->getDay()) >
            (date2->getYear() * 365 + date2->getMonth() * 30 + date2->getDay()));
};

void swap_ptr(smart_ptr<Date>& date1, smart_ptr<Date>& date2)
{
    smart_ptr<Date> ptrTemp(std::move(date2));
    date2 = std::move(date1);
    date1 = std::move(ptrTemp);
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Date date_today;

    smart_ptr<Date> today = &date_today;

    today->setDay(9);
    today->setMonth(1);
    today->setYear(2022);

    std::cout << date_today << std::endl;
    
    smart_ptr<Date> date(std::move(today));

    if (today != NULL) {
        std::cout << "today != NULL" << std::endl;
    }
    else {
        std::cout << "today == NULL" << std::endl;
    }

    if (date != NULL) {
        std::cout << "date != NULL" << std::endl;
    }
    else {
        std::cout << "date == NULL" << std::endl;
    }

    Date d1;
    Date d2;

    std::cout << "введите дату № 1" << std::endl;
    std::cin >> d1;
    std::cout << "введите дату № 2" << std::endl;
    std::cin >> d2;

    smart_ptr<Date> date1 = &d1;
    smart_ptr<Date> date2 = &d2;

    if (dateBiger(date1, date2)) {
        std::cout << "date1 > date 2" << std::endl;
    }
    else {
        std::cout << "date2 > date 1" << std::endl;
    }

    std::cout << date1->getDay() << " / " << date1->getMonth() << " / " << date1->getYear() << std::endl;
    std::cout << date2->getDay() << " / " << date2->getMonth() << " / " << date2->getYear() << std::endl;
    swap_ptr(date1, date2);
    std::cout << "swap ptr" << std::endl;
    std::cout << date1->getDay() << " / " << date1->getMonth() << " / " << date1->getYear() << std::endl;
    std::cout << date2->getDay() << " / " << date2->getMonth() << " / " << date2->getYear() << std::endl;
}
