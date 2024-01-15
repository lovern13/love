#include <iostream>
#include "Librarian.h"
#include <climits>

int main() {
    Librarian librarian = Librarian("John Doe", "123 Main St", 1234, 50000);
    librarian.readBooksFromCSV("library_books.csv");
    

    bool running = true;
    while (running) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add a member\n";
        std::cout << "2. Issue a book\n";
        std::cout << "3. Return a book\n";
        std::cout << "4. Display all books borrowed by a member\n";
        std::cout << "5. Calculate fine for a member\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "Enter your choice: "; // Add this line for user input
        std::cin >> choice;
	if (std::cin.fail()) {
	  std::cin.clear();                 // Clear the error flag
          std::cin.ignore(INT_MAX, '\n');  // Discard invalid input
          std::cout << "Invalid input. Please enter a number.\n";
          continue;
        }

        // Clear the input buffer
        std::cin.ignore(INT_MAX, '\n');
        switch (choice) {
	    case 1: {
	      std::string name, address;
	      int memberID;
	      std::cout << "Enter member details:\n";
	      std::cout << "Name: ";
	      std::cin >> name;
	      std::cout << "Address: ";
	      std::cin >> address;
	      std::cout << "Member ID: ";
	      std::cin >> memberID;

	      // Clear any remaining characters in the input buffer
	      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	      Member memberToAdd(name, address, memberID);
	      if (librarian.addMember(memberToAdd)) {
		std::cout << "Member added successfully:\n";
	      } else {
		std::cout << "Failed to add member (duplicate ID).\n";
	      }
	      break;
	    }

            case 2: {
	      int memberID, bookID;
	      std::cout << "Enter member ID and book ID to issue a book:\n";
	      std::cin >> memberID >> bookID;

    // Debugging checks
	      if (!librarian.findMember(memberID)) {
		std::cout << "Member not found.\n";
		break;
	      }

	      Book* bookToIssue = librarian.getBook(bookID);
	      if (!bookToIssue) {
		std::cout << "Book not found.\n";
		break;
	      }

	      if (bookToIssue->getBorrower()) {
		std::cout << "Book already borrowed.\n";
		break;
	      }

    // Example due date initialization, adjust as needed
	      Date dueDate(2024, 1, 10);

	      if (librarian.issueBook(memberID, bookID, dueDate, "library_books.csv")) {
		std::cout << "Book issued successfully.\n";
	      } else {
		std::cout << "Failed to issue book.\n";
	      }

	      break;

	    }

	    case 3: {
	      int memberID, bookID;
	      std::cout << "Enter member ID and book ID to return a book:\n";
	      std::cin >> memberID >> bookID;

	      if (librarian.returnBook(memberID, bookID)) {
		std::cout << "Book returned successfully.\n";
	      } else {
		std::cout << "Failed to return book.\n";
	      }

	      break;
	    }

            case 4: {
	      int memberID;
	      std::cout << "Enter member ID to display borrowed books: ";
	      std::cin >> memberID;
	      librarian.displayBorrowedBooks(memberID);
	      break;
	    }
			    case 5: {
        // Add code for case 5 (Calculate fine for a member)
        	int memberID;
        	std::cout << "Enter member ID to calculate fine: ";
        	std::cin >> memberID;

        // Debugging check
        	if (!librarian.findMember(memberID)) {
            	std::cout << "Member not found.\n";
            	break;
        	}

        // Get the member's borrowed books
        	std::vector<Book*> borrowedBooks = librarian.displayBorrowedBooks(memberID);

        // Calculate fine for each borrowed book
        	int totalFine = 0;
        	for (const auto& borrowedBook : borrowedBooks) {
            	int fine = librarian.calculateFine(*borrowedBook);
            	totalFine += fine;
        	}

        	std::cout << "Total fine for Member " << memberID << ": " << totalFine << " dollars\n";

        	break;
    	}



            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
