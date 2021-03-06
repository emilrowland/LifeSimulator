#include <stdexcept>
#include <sstream>
#include <iostream>

#include "Date.h"

DeltaTime::DeltaTime(){
    DeltaTime::year = 0;
    DeltaTime::month = 0;
    DeltaTime::day = 0;
    DeltaTime::hour = 0;
    DeltaTime::minute = 0;
    DeltaTime::second = 0;
}

DeltaTime::DeltaTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second){
    DeltaTime::year = year;
    DeltaTime::month = month;
    DeltaTime::day = day;
    DeltaTime::hour = hour;
    DeltaTime::minute = minute;
    DeltaTime::second = second;
}

Date::Date(){
    Date::year = 0;
    Date::month = 0;
    Date::day = 0;
    Date::hour = 0;
    Date::minute = 0;
    Date::second = 0;
}

Date::Date(unsigned int year, unsigned short int month, unsigned short int day, unsigned short int hour, unsigned short int minute, unsigned short int second){
    if(month > 12 || hour >= 24|| minute >= 60 || second >= 60){
        throw std::invalid_argument("Not an valid Date!");
    }
    if(month > 0 && day > Date::daysInMonth[month-1]-1){
        throw std::invalid_argument("Not an valid Date!");
    }
    Date::year = year;
    Date::month = month;
    Date::day = day;
    Date::hour = hour;
    Date::minute = minute;
    Date::second = second;
}

Date::Date(const Date& obj){
    Date::year = obj.year;
    Date::month = obj.month;
    Date::day = obj.day;
    Date::hour = obj.hour;
    Date::minute = obj.minute;
    Date::second = obj.second;
}

Date::Date(std::string str){
    //Phrase string as yyyy-mm-dd hh:mm:ss
    Date::year = std::stoi(str.substr(0,4));
    Date::month = std::stoi(str.substr(5,2));
    Date::day = std::stoi(str.substr(8,2));
    Date::hour = std::stoi(str.substr(11,2));
    Date::minute = std::stoi(str.substr(14,2));
    Date::second = std::stoi(str.substr(17,2));
}

std::string Date::toString(){
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

void Date::add(DeltaTime date){
    int s = (Date::second + date.second);
    Date::second = s % 60;
    int m = (Date::minute + date.minute + s / 60);
    Date::minute = m % 60;
    int h = (Date::hour + date.hour + m / 60);
    Date::hour = h % 24;
    int d = (Date::day + date.day + h / 24);
    Date::day = (d % Date::daysInMonth[Date::month-1]);
    if(d >= Date::daysInMonth[Date::month-1]){
        Date::day++;
    }
    if(Date::day == 0){
        Date::day++;
    }
    int mo = (Date::month + date.month + d / Date::daysInMonth[Date::month-1]);
    Date::month = mo % 13;
    if(Date::month == 0){
        Date::month++;
    }
    Date::year = (Date::year + date.year + mo / 13);

    //Calculate extra days
    while(Date::day > (Date::daysInMonth[Date::month-1]-1)){
        Date::day -= Date::daysInMonth[Date::month-1]-1;
        Date::month++;
        if(Date::month > 12){
            Date::year++;
            Date::month = 1;
        }
    }
}

void Date::tick(unsigned short int second){
    if(second >= 60){
        throw std::invalid_argument("Not an valid Date!");
    }
    Date::add(DeltaTime(0,0,0,0,0,second));
}

bool Date::operator <=(const Date& other) const{
    if(this->year < other.year){
        return true;
    }else if(this->year > other.year){
        return false;
    }
    if(this->month < other.month){
        return true;
    }else if(this->month > other.month){
        return false;
    }
    if(this->day < other.day){
        return true;
    }else if(this->day > other.day){
        return false;
    }
    if(this->hour < other.hour){
        return true;
    }else if(this->hour > other.hour){
        return false;
    }
    if(this->minute < other.minute){
        return true;
    }else if(this->minute > other.minute){
        return false;
    }
    if(this->second < other.second){
        return true;
    }else if(this->second > other.second){
        return false;
    }
    return true; //They are equal
}

bool Date::operator <(const Date& other) const{
    if(this->year < other.year){
        return true;
    }else if(this->year > other.year){
        return false;
    }
    if(this->month < other.month){
        return true;
    }else if(this->month > other.month){
        return false;
    }
    if(this->day < other.day){
        return true;
    }else if(this->day > other.day){
        return false;
    }
    if(this->hour < other.hour){
        return true;
    }else if(this->hour > other.hour){
        return false;
    }
    if(this->minute < other.minute){
        return true;
    }else if(this->minute > other.minute){
        return false;
    }
    if(this->second < other.second){
        return true;
    }else if(this->second > other.second){
        return false;
    }
    return false;//Should never come here
}

bool Date::operator ==(const Date& other) const{
    if(this->year == other.year && this->month == other.month && this->day == other.day &&
       this->hour == other.hour && this->minute == other.minute && this->second == other.second){
        return true;
    }
    return false;
}
