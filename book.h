#ifndef BOOK_H_
#define BOOK_H_


#include "Member.h"
#include "Date.h"
#include <string>
#include <vector>

// Consider including Date or similar class if using for due dates
class Member;

class Book {
public:
  // Constructor (include relevant attributes like title, author, type, page count)
  Book(int bookID, const std::string& title, const std::string& author, const std::string& type, int pageCount);
  // Add a new constructor that takes a CSV line as input
  explicit Book(const std::string& csvLine);


  // Getters and setters
  int getBookID() const;
  void setBookID(int bookID);

  const std::string& getBookName() const;

  const std::string& getTitle() const;
  void setTitle(const std::string& title);

  const std::string& getAuthor() const;
  void setAuthor(const std::string& author);
  const Date& getDueDate() const; // Change the return type to const Date&
  void setDueDate(const Date& dueDate);

  std::string toString() const;
 

  const std::string& getType() const;
  void setType(const std::string& type);

  int getPageCount() const;
  void setPageCount(int pageCount);

  // Borrowing and returning
  Member* getBorrower() const;
  void setBorrower(Member* borrower);



  // Additional methods (optional)
  // e.g., isAvailable(), calculateFine(), toString()

private:
  // Private member variables
  int bookID_;
  std::string title_;
  std::string author_;
  std::string bookName;
  std::string type_;
  int pageCount_;
  Member* borrower_; // Pointer to currently borrowing member (nullptr if not borrowed)
  Date dueDate_; // Replace with appropriate type if not using "Date" class

};

#endif // BOOK_H_

