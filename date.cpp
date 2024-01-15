#include "Date.h"
#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

Date Date::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    return Date(localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
}

Date Date::getDefaultDate() {
    return Date(2000, 1, 1); // Adjust this depending on your default date logic
}

// Constructor
Date::Date(int year, int month, int day) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

// Default constructor
Date::Date() : year_(2000), month_(1), day_(1) {
}

// Accessor methods
int Date::getYear() const {
    return year_;
}

int Date::getMonth() const {
    return month_;
}

int Date::getDay() const {
    return day_;
}

// Mutator methods
void Date::setYear(int year) {
    year_ = year;
}

void Date::setMonth(int month) {
    if (month >= 1 && month <= 12) {
        month_ = month;
    } else {
        std::cerr << "Invalid month value. Month set to 1." << std::endl;
        month_ = 1;
    }
}

void Date::setDay(int day) {
    if (day >= 1 && day <= 31) {
        day_ = day;
    } else {
        std::cerr << "Invalid day value. Day set to 1." << std::endl;
        day_ = 1;
    }
}

// Comparison operators
bool Date::operator<(const Date& other) const {
    if (year_ < other.year_) {
        return true;
    } else if (year_ == other.year_ && month_ < other.month_) {
        return true;
    } else if (year_ == other.year_ && month_ == other.month_ && day_ < other.day_) {
        return true;
    }
    return false;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return !(other < *this);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

bool Date::operator==(const Date& other) const {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

// Implementation for daysBetween
int Date::daysBetween(const Date& other) const {
    // Convert both dates to time_t
    std::tm tm1 = {0, 0, 0, day_, month_ - 1, year_ - 1900};
    std::tm tm2 = {0, 0, 0, other.day_, other.month_ - 1, other.year_ - 1900};

    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    // Calculate the difference in seconds
    std::time_t difference = std::difftime(time1, time2);

    // Calculate the difference in days
    int days = difference / (60 * 60 * 24);

    return days;
}

// Date arithmetic methods
void Date::addDays(int days) {
    std::tm tmDate = {0, 0, 0, day_, month_ - 1, year_ - 1900};
    std::time_t time = std::mktime(&tmDate);
    
    // Add seconds for the given number of days
    time += days * (60 * 60 * 24);

    // Update tmDate
    std::tm* updatedTm = std::localtime(&time);
    day_ = updatedTm->tm_mday;
    month_ = updatedTm->tm_mon + 1;
    year_ = updatedTm->tm_year + 1900;
}

void Date::subtractDays(int days) {
    addDays(-days); // Reuse the addDays method for subtraction
}


// Output formatting
std::string Date::toString() const {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << year_ << '-'
       << std::setw(2) << month_ << '-' << std::setw(2) << day_;
    return ss.str();
}
