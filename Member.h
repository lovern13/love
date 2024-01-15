#ifndef MEMBER_H_
#define MEMBER_H_

#include <vector>
#include "Book.h"
#include "Person.h" // Include Person class header
#include "Date.h"   // Include Date class header

class Book;

class Member : public Person {
public:
    // Constructor with meaningful parameters
    Member(const std::string& name, const std::string& address, int memberID,
           const std::string& membershipType = "Basic");

    // Getters and setters for all attributes
    int getMemberID() const;
    void setMemberID(int memberID);
    std::string toString() const;

    // Book borrowing and returning methods with safety checks
    bool addBorrowedBook(Book* book);      // Returns true if successful, false if not
    bool removeBorrowedBook(Book* book);   // Returns true if successful, false if not
    std::vector<Book*> getBorrowedBooks() const;

    Date calculateDueDate(const Date& issueDate) const;

private:
    int memberID_;
    std::string membershipType_;
    std::vector<Book*> borrowedBooks_;
};

#endif // MEMBER_H_
