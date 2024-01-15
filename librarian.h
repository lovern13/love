#ifndef LIBRARIAN_H_
#define LIBRARIAN_H_

#include <vector>
#include "Person.h"
#include "Member.h"
#include "Book.h"
#include "Date.h"

class Librarian : public Person {
public:
    Librarian(const std::string& name, const std::string& address, int staffID, int salary);

    // Methods for managing members
    bool addMember(Member& member);
    std::vector<Member> displayAllMembers() const;

    // Methods for managing books
    bool addBook(Book& book);
    bool issueBook(int memberID, int bookID, Date dueDate, const std::string& finame);
   
    bool returnBook(int memberID, int bookID);
    std::vector<Book*> displayBorrowedBooks(int memberID) const;
    int calculateFine(const Book& book) const;
    
    int calculateFineForMember(const Member& member) const;

    // Additional methods
    void setStaffID(int staffID);
    void setSalary(int salary);

    bool findMember(int memberID) const;
    bool findBook(int bookID) const;
    Book* getBook(int bookID) const;

    int getStaffID() const;
    int getSalary() const;
    static const int FINE_PER_DAY;

    // New method for reading books from CSV
    void readBooksFromCSV(const std::string& filename);

private:
    int bookID_;
    int staffID_;
    int salary_;
    
    mutable std::vector<Book> books_;
    std::vector<Member> members_;
    
    

};

#endif // LIBRARIAN_H_
