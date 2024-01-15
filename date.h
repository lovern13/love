#ifndef DATE_H_
#define DATE_H_

#include <ctime>
#include <chrono>
#include <string>

class Date {
public:
    // Constructors
    Date();  // Default constructor
    Date(int year, int month, int day);

    // Accessor methods
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // Mutator methods
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);

    // Comparison methods
    bool isBefore(const Date& other) const;
    bool isAfter(const Date& other) const;
    bool isEqual(const Date& other) const;

    // Date arithmetic methods
    void addDays(int days);
    void subtractDays(int days);
        // Comparison operators
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;

    // Output formatting
    std::string toString() const;
      // Get the current date
    static Date getCurrentDate();
    static Date getDefaultDate();

    // Calculate days between dates
    int daysBetween(const Date& other) const;

private:
    int year_;
    int month_;
    int day_;
    std::tm tm; 
};

#endif // DATE_H_
