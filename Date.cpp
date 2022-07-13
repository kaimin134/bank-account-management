#include "Date.h"
#include "Account.h"
#include <string>
#include<iostream>
#include <stdlib.h> 

using namespace std;
//set month, day, year, hour
void Date::set(int month_, int day_, int year_, int hour_)
{
    month = month_;
    day = day_;
    year = year_;
    hour = hour_;;
}
//accessor get day
int Date::getDayFromDate() const 
{ 
    return day; 
}
//accessor get month
int Date::getMonthFromDate() const 
{ 
    return month; 
}
//accessor get year
int Date::getYearFromDate() const 
{ 
    return year; 
}
//accessor get hour
int Date::getHourFromDate() const
{
    return hour;
}
//overloaded operator
bool Date::operator<(const Date &rdate)
{
    if(year < rdate.year)
        return true;

    else if(year == rdate.year && month < rdate.month)
        return true;

    else if(year == rdate.year && month == rdate.month && day < rdate.day)
        return true;

    else if(year == rdate.year && month == rdate.month && day == rdate.day && hour < rdate.hour)
        return true;
    return false;
}
//display date
void Date::print() const
{
    string monthArray[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    cout << monthArray[month - 1] << " " << day << ", " << year << ", " << hour << ":00";
}

