# Library Management System

A C++ application for managing a library's books, borrowers, and staff. The system allows librarians to add or remove books, borrowers to borrow and return books, and tracks borrowing histories. Data persistence is achieved through file storage for books and user details.

## Features

- **Book Management**
  - Add and remove books.
  - Display the list of books in the library.
  - Persist book details to a file.

- **User Management**
  - Add and display users (Librarian and Borrower).
  - Borrow and return books with tracking of borrowing history.
  - Save user details to a file.

- **File Persistence**
  - Save and load books and user data from files (`books.txt`, `users.txt`).

- **Menu-driven Interface**
  - Easy-to-use console interface for managing library operations.

## Concepts Demonstrated

- **Object-Oriented Programming (OOP)**
  - Classes and Objects
  - Inheritance and Polymorphism
  - Abstraction and Encapsulation

- **File Handling**
  - Saving and loading data from text files.

- **Algorithmic Features**
  - Searching for books by ID.
  - Managing collections of books and users using STL `vector`.

## Setup and Usage

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/LibraryManagementSystem.git
   cd LibraryManagementSystem
