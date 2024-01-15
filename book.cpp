#include "Book.h"
#include "Date.h"
#include <sstream>

Book::Book(int bookID, const std::string& title, const std::string& author, const std::string& type, int pageCount)
    : bookID_(bookID), title_(title), author_(author), type_(type), pageCount_(pageCount), borrower_(nullptr),
      dueDate_(Date::getDefaultDate()) {}

// New constructor to initialize book properties from a CSV line
Book::Book(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string token;

    // Read and initialize book properties from the CSV line
    std::getline(ss, token, ',');
    bookID_ = std::stoi(token);
    std::getline(ss, title_, ',');
    std::getline(ss, author_, ',');
    std::getline(ss, type_, ',');
    std::getline(ss, token, ',');
    pageCount_ = std::stoi(token);
    borrower_ = nullptr;
    dueDate_ = Date::getDefaultDate();
}

int Book::getBookID() const { return bookID_; }

const std::string& Book::getBookName() const {
    return title_;
}


void Book::setBookID(int bookID) { bookID_ = bookID; }

const std::string& Book::getTitle() const { return title_; }

void Book::setTitle(const std::string& title) { title_ = title; }

const std::string& Book::getAuthor() const { return author_; }

void Book::setAuthor(const std::string& author) { author_ = author; }

const std::string& Book::getType() const { return type_; }

void Book::setType(const std::string& type) { type_ = type; }

int Book::getPageCount() const { return pageCount_; }

void Book::setPageCount(int pageCount) { pageCount_ = pageCount; }

Member* Book::getBorrower() const { return borrower_; }

void Book::setBorrower(Member* borrower) { borrower_ = borrower; }

const Date& Book::getDueDate() const {
    return dueDate_;
}

void Book::setDueDate(const Date& dueDate) {
    dueDate_ = dueDate;
}

std::string Book::toString() const {
    std::string output = "Book ID: " + std::to_string(bookID_) + "\n";
    output += "Title: " + title_ + "\n";
    output += "Author: " + author_ + "\n";
    output += "Borrowed by: " + (borrower_ ? borrower_->getName() : "None") + "\n";
    output += "Due Date: " + dueDate_.toString() + "\n";
    return output;
}
