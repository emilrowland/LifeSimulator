#include <stdexcept>
#include <sstream>
#include <iostream>

#include "Date.h"

Date::Date(int year, int month, int day, int hour, int minute, int second){
    Date::year = year;
    Date::month = month;
    Date::day = day;
    Date::hour = hour;
    Date::minute = minute;
    Date::second = second;
}

Date::~Date(){
}

std::string Date::toString(){
    std::ostringstream oss;
    oss << Date::year << "-" << Date::month << "-" << Date::day << " " << Date::hour << ":" << Date::minute << ":" << Date::second;
    return oss.str();
}

void Date::add(Date date){
    //int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInMonth[12] = {32, 29, 32, 31, 32, 31, 32, 32, 31, 32, 31, 32};
    int s = (Date::second + date.second);
    Date::second = s % 60;
    int m = (Date::minute + date.minute + s / 60);
    Date::minute = m % 60;
    int h = (Date::hour + date.hour + m / 60);
    Date::hour = h % 24;
    int d = (Date::day + date.day + h / 24);
    Date::day = (d % daysInMonth[Date::month-1]);
    if(Date::day == 0){
        Date::day++;
    }
    int mo = (Date::month + date.month + d / daysInMonth[Date::month-1]);
    Date::month = mo % 13;
    if(Date::month == 0){
        Date::month++;
    }
    Date::year = (Date::year + date.year + mo / 13);
}

void Date::tick(int second){
    if(second >= 60){
        throw std::invalid_argument("Not an valid Date!");
    }
    Date::add(Date(0,0,0,0,0,second));
}
