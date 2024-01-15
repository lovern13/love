

#include "Librarian.h"
#include "Member.h"
#include "Book.h"
#include "Date.h"
#include <iostream> 
#include <fstream>
#include <sstream>

// Static member initialization
const int Librarian::FINE_PER_DAY = 1;

Librarian::Librarian(const std::string& name, const std::string& address, int staffID, int salary)
    : Person(name, address), staffID_(staffID), salary_(salary) {}

int Librarian::getStaffID() const { return staffID_; }

void Librarian::setStaffID(int staffID) { staffID_ = staffID; }

int Librarian::getSalary() const { return salary_; }

void Librarian::setSalary(int salary) { salary_ = salary; }

void Librarian::readBooksFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    getline(file, line);  // Read and discard the header line

    while (getline(file, line)) {
        std::istringstream iss(line);

        // Define variables to store CSV fields
        std::string bookID, bookName, pageCount, authorFirstName, authorLastName, bookType;

        // Use getline to handle quoted strings and commas within a field
        if (getline(iss, bookID, ',') &&
            getline(iss, bookName, ',') &&
            getline(iss, pageCount, ',') &&
            getline(iss, authorFirstName, ',') &&
            getline(iss, authorLastName, ',') &&
            getline(iss, bookType)) {

            try {
                // Convert data after checking for errors
                int id = std::stoi(bookID);
                int pages = std::stoi(pageCount);
                std::string author = authorFirstName + " " + authorLastName;

                Book newBook(id, bookName, author, bookType, pages);
                books_.push_back(newBook);
            } catch (const std::invalid_argument& e) {
                std::cerr << " " << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: Out of range data in CSV line: " << line << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid CSV line format: " << line << std::endl;
        }
    }

    file.close();
}



bool Librarian::findBook(int bookID) const {
    for (const auto& book : books_) {
        if (book.getBookID() == bookID) {
            return true;
        }
    }
    return false;
}

Book* Librarian::getBook(int bookID) const {
    for (auto& existingBook : books_) {
        if (existingBook.getBookID() == bookID) {
            return &existingBook;
        }
    }
    return nullptr;
}





bool Librarian::addMember(Member& member) {
    // Check if member already exists
    for (const auto& existingMember : members_) {
        if (existingMember.getMemberID() == member.getMemberID()) {
            return false; // Member already exists
        }
    }
    // Add member to list
    members_.push_back(member);
    return true; // Member added successfully
}

bool Librarian::issueBook(int memberID, int bookID, Date dueDate, const std::string& filename) {
    if (!filename.empty()) {
        // Handle CSV file logic (if needed)
        readBooksFromCSV(filename);
    }

    // Find member object
    Member* member = nullptr;
    for (auto& existingMember : members_) {
        if (existingMember.getMemberID() == memberID) {
            member = &existingMember;
            break;
        }
    }

    // Check if member exists
    if (!member) {
        std::cout << "Member not found." << std::endl;
        return false; // Invalid member ID
    }

    // Find book object by ID
    Book* book = nullptr;
    for (auto& existingBook : books_) {
        if (existingBook.getBookID() == bookID) {
            book = &existingBook;
            break;
        }
    }

    // Check if book exists
    if (!book) {
        std::cout << "Book not found." << std::endl;
        return false; // Invalid book ID
    }

    // Check if book is already borrowed
    if (book->getBorrower()) {
        std::cout << "Book already borrowed." << std::endl;
        return false; // Book already borrowed
    }

    // Issue book to member and set due date
    book->setBorrower(member);
    book->setDueDate(dueDate);
    member->addBorrowedBook(book);

    // Display information about the issued book
    std::cout << "Book issued successfully:\n";
    std::cout << "Book ID: " << book->getBookID() << "\n";
    std::cout << "Book Name: " << book->getBookName() << "\n";
    std::cout << "Author: " << book->getAuthor() << "\n";
    std::cout << "Due Date: " << dueDate.toString() << "\n";

    return true; // Book issued successfully
}



bool Librarian::returnBook(int memberID, int bookID) {
    // Find member and book objects
    Member* member = nullptr;
    Book* book = nullptr;

    // Locate the member
    for (auto& existingMember : members_) {
        if (existingMember.getMemberID() == memberID) {
            member = &existingMember;
            break;
        }
    }

    // Locate the book
    for (auto& existingBook : books_) {
        if (existingBook.getBookID() == bookID) {
            book = &existingBook;
            break;
        }
    }

    // Check if member and book exist
    if (!member || !book) {
        return false; // Invalid member or book ID
    }

    // Check if the book is borrowed by the member
    if (book->getBorrower() != member) {
        return false; // Book not borrowed by this member
    }

    // Calculate fine if the book is overdue
    int fine = calculateFine(*book);

    // Handle fine payment logic here
    if (fine > 0) {
        std::cout << "Fine amount: " << fine << std::endl;
        
    }

    // Return book and clear borrower information
    book->setBorrower(nullptr);
    book->setDueDate(Date());
    member->removeBorrowedBook(book);

    return true; // Book returned successfully
}



std::vector<Book*> Librarian::displayBorrowedBooks(int memberID) const {
    std::vector<Book*> borrowedBooks;

    // Find the member
    const Member* member = nullptr;
    for (const auto& existingMember : members_) {
        if (existingMember.getMemberID() == memberID) {
            member = &existingMember;
            break;
        }
    }

    // Check if the member exists
    if (!member) {
        std::cout << "Member not found." << std::endl;
        return borrowedBooks; // Return an empty vector
    }

    // Iterate through the books and find those borrowed by the member
    for (const auto& book : books_) {
        if (book.getBorrower() && book.getBorrower()->getMemberID() == memberID) {
            borrowedBooks.push_back(const_cast<Book*>(&book));
        }
    }

    // Display borrowed books
    if (borrowedBooks.empty()) {
        std::cout << "No books borrowed by the member." << std::endl;
    } else {
        std::cout << "Books borrowed by Member " << memberID << ":\n";
        for (const auto& borrowedBook : borrowedBooks) {
            std::cout << "Book ID: " << borrowedBook->getBookID() << " - "
                      << "Book Name: " << borrowedBook->getBookName() << std::endl;
        }
    }

    return borrowedBooks;
}




int Librarian::calculateFine(const Book& book) const {
    // Check if book is overdue
    Date today = Date::getCurrentDate();
    if (book.getDueDate() < today) {
        int daysOverdue = today.daysBetween(book.getDueDate());
        return daysOverdue * FINE_PER_DAY; // Calculate fine based on overdue days and rate
    } else {
        return 0; // No fine if book is not overdue
    }
}

// Implement private members and methods here (e.g., members_, books)
bool Librarian::findMember(int memberID) const {
    for (const auto& member : members_) {
        if (member.getMemberID() == memberID) {
            return true;
        }
    }
    return false;
}

int Librarian::calculateFineForMember(const Member& member) const {
    int totalFine = 0;

    // Iterate through the borrowed books of the member
    for (const Book* borrowedBook : member.getBorrowedBooks()) {
        int fineForBook = calculateFine(*borrowedBook);
        totalFine += fineForBook;
    }

    return totalFine;
}