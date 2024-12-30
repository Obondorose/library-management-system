#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Abstract Class for Library Users (Renamed to Librarian)
class Librarian {
protected:
    string name;
    int id;

public:
    Librarian(const string &name, int id) : name(name), id(id) {}
    virtual ~Librarian() {}
    virtual void displayDetails() const = 0; // Pure virtual function
};

// Book Class
class Book {
private:
    string title;
    string author;
    int bookID;

public:
    Book(const string &title, const string &author, int bookID)
        : title(title), author(author), bookID(bookID) {}

    void displayBook() const {
        cout << "Book Title: " << title << ", Author: " << author
             << ", Book ID: " << bookID << endl;
    }

    int getBookID() const {
        return bookID;
    }

    const string &getTitle() const { return title; }
    const string &getAuthor() const { return author; }

    // Save Book to a file
    void saveToFile(ofstream &outFile) const {
        outFile << bookID << "," << title << "," << author << endl;
    }

    // Load Book from a file
    static Book loadFromFile(const string &line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        int bookID = stoi(line.substr(0, pos1));
        string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1);

        return Book(title, author, bookID);
    }
};

// Derived Class: Borrower
class Borrower : public Librarian {
private:
    string membershipType;
    vector<int> borrowedBooks; // Stores book IDs

public:
    Borrower(const string &name, int id, const string &membershipType)
        : Librarian(name, id), membershipType(membershipType) {}

    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
        cout << "Book with ID " << bookID << " borrowed by " << name << "." << endl;
    }

    void returnBook(int bookID) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            cout << "Book with ID " << bookID << " returned by " << name << "." << endl;
        } else {
            cout << "Error: You did not borrow this book (ID: " << bookID << ")." << endl;
        }
    }

    void viewBorrowingHistory() const {
        if (borrowedBooks.empty()) {
            cout << "Error: No borrowing history for " << name << "." << endl;
        } else {
            cout << "Borrowing History for " << name << ": ";
            for (int bookID : borrowedBooks) {
                cout << bookID << " ";
            }
            cout << endl;
        }
    }

    void displayDetails() const override {
        cout << "Borrower Name: " << name << ", ID: " << id
             << ", Membership Type: " << membershipType << endl;
        if (borrowedBooks.empty()) {
            cout << "Currently Borrowed Books: None" << endl;
        } else {
            cout << "Currently Borrowed Books: ";
            for (int bookID : borrowedBooks) {
                cout << bookID << " ";
            }
            cout << endl;
        }
    }

    // Save Borrower to a file
    void saveToFile(ofstream &outFile) const {
        outFile << id << "," << name << "," << membershipType << endl;
    }

    // Load Borrower from a file
    static Borrower loadFromFile(const string &line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string membershipType = line.substr(pos2 + 1);

        return Borrower(name, id, membershipType);
    }
};

// Derived Class: Librarian Staff
class LibrarianStaff : public Librarian {
private:
    string position;

public:
    LibrarianStaff(const string &name, int id, const string &position)
        : Librarian(name, id), position(position) {}

    void displayDetails() const override {
        cout << "Librarian Name: " << name << ", ID: " << id
             << ", Position: " << position << endl;
    }

    void addBook(vector<Book> &books, const Book &book) {
        books.push_back(book);
        cout << "Book added: " << book.getTitle() << endl;
    }

    void removeBook(vector<Book> &books, int bookID) {
        auto it = find_if(books.begin(), books.end(), [bookID](const Book &book) {
            return book.getBookID() == bookID;
        });
        if (it != books.end()) {
            cout << "Book removed: " << it->getTitle() << endl;
            books.erase(it);
        } else {
            cout << "Error: Book with ID " << bookID << " not found." << endl;
        }
    }

    // Save LibrarianStaff to a file
    void saveToFile(ofstream &outFile) const {
        outFile << id << "," << name << "," << position << endl;
    }

    // Load LibrarianStaff from a file
    static LibrarianStaff loadFromFile(const string &line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string position = line.substr(pos2 + 1);

        return LibrarianStaff(name, id, position);
    }
};

// Library Management System
class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Librarian *> users;

public:
    ~LibraryManagementSystem() {
        for (auto user : users)
            delete user;
    }

    void addBook(const Book &book) {
        books.push_back(book);
    }

    void removeBook(int bookID) {
        auto it = find_if(books.begin(), books.end(), [bookID](const Book &book) {
            return book.getBookID() == bookID;
        });
        if (it != books.end()) {
            cout << "Book removed: " << it->getTitle() << endl;
            books.erase(it);
        } else {
            cout << "Error: Book with ID " << bookID << " not found." << endl;
        }
    }

    void addUser(Librarian *user) {
        users.push_back(user);
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "Error: No books available in the library." << endl;
        } else {
            cout << "Books in the Library:" << endl;
            for (const auto &book : books) {
                book.displayBook();
            }
        }
    }

    void displayUsers() const {
        if (users.empty()) {
            cout << "Error: No users found in the system." << endl;
        } else {
            cout << "Users in the Library:" << endl;
            for (const auto &user : users) {
                user->displayDetails();
            }
        }
    }

    void saveToFile(const string &booksFile, const string &usersFile) {
        ofstream bookOutFile(booksFile);
        if (bookOutFile.is_open()) {
            for (const auto &book : books) {
                book.saveToFile(bookOutFile);
            }
            bookOutFile.close();
        }

        ofstream userOutFile(usersFile);
        if (userOutFile.is_open()) {
            for (const auto &user : users) {
                if (auto borrower = dynamic_cast<Borrower *>(user)) {
                    borrower->saveToFile(userOutFile);
                } else if (auto librarian = dynamic_cast<LibrarianStaff *>(user)) {
                    librarian->saveToFile(userOutFile);
                }
            }
            userOutFile.close();
        }
    }

    void loadFromFile(const string &booksFile, const string &usersFile) {
        ifstream bookInFile(booksFile);
        string line;
        while (getline(bookInFile, line)) {
            books.push_back(Book::loadFromFile(line));
        }

        ifstream userInFile(usersFile);
        while (getline(userInFile, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                if (line.find("Borrower") != string::npos) {
                    users.push_back(new Borrower(Borrower::loadFromFile(line)));
                } else {
                    users.push_back(new LibrarianStaff(LibrarianStaff::loadFromFile(line)));
                }
            }
        }
    }

    void displayMenu() {
        while (true) {
            cout << "\nLibrary Management System Menu:\n";
            cout << "1. Display Books\n";
            cout << "2. Display Users\n";
            cout << "3. Add Book\n";
            cout << "4. Remove Book\n";
            cout << "5. Borrow a Book\n";
            cout << "6. Return a Book\n";
            cout << "7. View Borrowing History\n";
            cout << "8. Exit\n";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: displayBooks(); break;
                case 2: displayUsers(); break;
                case 3: {
                    string title, author;
                    int id;
                    cout << "Enter Book ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Enter Book Title: ";
                    getline(cin, title);
                    cout << "Enter Author Name: ";
                    getline(cin, author);
                    addBook(Book(title, author, id));
                    break;
                }
                case 4: {
                    int bookID;
                    cout << "Enter Book ID to remove: ";
                    cin >> bookID;
                    removeBook(bookID);
                    break;
                }
                case 5: {
                    int bookID;
                    cout << "Enter Book ID to borrow: ";
                    cin >> bookID;
                    // Implement borrowing logic for the selected Borrower
                    break;
                }
                case 6: {
                    int bookID;
                    cout << "Enter Book ID to return: ";
                    cin >> bookID;
                    // Implement return logic for the selected Borrower
                    break;
                }
                case 7: {
                    // Implement Borrower history viewing
                    break;
                }
                case 8: return;
                default: cout << "Invalid choice! Try again.\n"; break;
            }
        }
    }
};

// Main Function
int main() {
    LibraryManagementSystem library;

    // Load data from files
    library.loadFromFile("books.txt", "users.txt");

    // Display Menu and handle user choices
    library.displayMenu();

    // Save data to files before exiting
    library.saveToFile("books.txt", "users.txt");

    return 0;
}
