#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
#include<vector>
#include<string>
#include <map>
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date() = default;
    class Invalid_day_leap_year{};
    class Invalid_month{};
    class Invalid_day{};

    void setDay(int d)
    {

        if (d <= 0 || d >31) {
            throw Invalid_day();
        }

        if (month == 2) {
            // Handle the case for February
            if (isLeapYear(year)) {
                if (d > 29) {
                    throw Invalid_day_leap_year();
                }
            }
            else {
                if (d > 28) {
                    throw Invalid_day();
                }
            }
        }
        day = d;
    }
    int getDay(){return day;}

    void setMonth(int m)
    {

        if(m < 1|| m > 12){
            throw Invalid_month();
        }
        else{
            month = m;
        }
    }
    int getMonth(){return month;}

    void setYear(int y){year = y;}
    int getYear(){return year;}

    void printDate()
    {
        map <int,string> MONTH = {{1,"January"},{2, "February"},{3,"March"},{4,"April"}, {5,"May"},
        {6, "June"},{7,"July"}, {8,"August"}, {9,"September"}, {10,"October"}, {11,"November"}, {12,"December"}};

        //cout<<"Date: "<<endl;
        cout<<month<<"/"<<day<<"/"<<year<<endl;
        //cout<<MONTH[month]<<" "<<day<<", "<<year<<endl;
        //cout<<day<< " "<<MONTH[month]<< " "<<year<<endl;
    }

    int toJulianDay()const {
        int y = year, m = month, d = day;
        if (m <= 2) {
            y--;
            m += 12;
        }
        int A = y / 100;
        int B = 2 - A + A / 4;
        return static_cast<int>(365.25 * (y + 4716)) + static_cast<int>(30.6001 * (m + 1)) + d + B - 1524;
    }
    /***************************************************************************************
        *Title: Julian Day Calculation in C++
        * Author : Derived from Julian Day Number formula(widely available in astronomy)
        * Availability : Commonly referenced in date difference algorithms.
        * Example : https ://en.wikipedia.org/wiki/Julian_day
        ****************************************************************************************/



    // calculate the number of days between two dates 
    int calculateDateDifference( Date date2) {
        int julianDay1 = this->toJulianDay();
        int julianDay2 = date2.toJulianDay();
        return abs(julianDay1 - julianDay2); // Return the absolute value
    }




};



#endif // DATE_H_INCLUDED
