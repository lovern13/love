#include "Member.h"
#include <algorithm> // Include for std::remove
#include <chrono>
#include "Book.h"

Member::Member(const std::string& name, const std::string& address, int memberID,
               const std::string& membershipType)
    : Person(name, address), memberID_(memberID), membershipType_(membershipType) {}

int Member::getMemberID() const {
    return memberID_;
}

void Member::setMemberID(int memberID) {
    memberID_ = memberID;
}

bool Member::addBorrowedBook(Book* book) {
    borrowedBooks_.push_back(book);
    return true; // Return true for successful addition
}

bool Member::removeBorrowedBook(Book* book) {
    auto it = std::remove(borrowedBooks_.begin(), borrowedBooks_.end(), book);
    if (it != borrowedBooks_.end()) {
        borrowedBooks_.erase(it, borrowedBooks_.end());
        return true; // Return true for successful removal
    }
    return false; // Return false if book was not found
}

std::vector<Book*> Member::getBorrowedBooks() const {
    return borrowedBooks_;
}

std::string Member::toString() const {
    std::string output = Person::toString();
    output += "Member ID: " + std::to_string(memberID_) + "\n";
    output += "Borrowed Books:\n";
    for (auto& book : borrowedBooks_) {
        output += "- " + book->getTitle() + "\n";
    }
    return output;
}

Date Member::calculateDueDate(const Date& issueDate) const {
    Date dueDate = issueDate;
    dueDate.addDays(5); // Add 3 days

    return dueDate;
}
