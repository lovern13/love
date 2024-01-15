#include "Person.h"

// Constructor with name and address
Person::Person(const std::string& name, const std::string& address) : name_(name), address_(address) {}

// Getters and setters (returning const references)
const std::string& Person::getName() const { return name_; }
void Person::setName(const std::string& name) { name_ = name; }
const std::string& Person::getAddress() const { return address_; }
void Person::setAddress(const std::string& address) { address_ = address; }

// Additional methods
std::string Person::toString() const {
    return "Name: " + name_ + "\nAddress: " + address_;
}
