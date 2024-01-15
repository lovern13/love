#ifndef PERSON_H_
#define PERSON_H_

#include <string>

class Person {
public:
    // Default constructor 
    Person() = default;

    // Constructor with name and address
    Person(const std::string& name, const std::string& address);

    // Getters and setters
    const std::string& getName() const;
    void setName(const std::string& name);
    const std::string& getAddress() const;
    void setAddress(const std::string& address);

    // Additional methods
    std::string toString() const;  // Declaration for toString()

private:
    // Private member variables
    std::string name_;
    std::string address_;
};

#endif // PERSON_H_
