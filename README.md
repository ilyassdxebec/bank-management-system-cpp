🏦 Bank Management System (C++)

A console-based Bank Management System built with C++ that allows you to manage client accounts stored in a text file.

This project simulates basic banking operations and focuses on practicing file handling, structs, vectors, and modular programming.

✨ Features
📋 Show all clients
➕ Add a new client
❌ Delete a client by account number
✏️ Update client information
🔎 Find a client by account number
💰 Deposit money
💸 Withdraw money
📊 Show total balances
🔐 User & Access Management
🔑 Login system
👤 Manage users (CRUD operations)
🛡️ Admin permissions
🚪 Logout functionality
💾 Users stored in a separate file
🖥️ Program Screens
Main Menu

Transactions Menu

▶️ How to Run
Clone the repository
git clone https://github.com/ilyassdxebec/bank-management-system-cpp.git
Open the project in Visual Studio or any C++ compiler
Build and run:
main.cpp
Make sure the file Clients.txt exists in the same directory as the executable.
💾 Data Storage

Client data is stored in a .txt file using a custom delimiter format:

#//#

Example record:

A150#//#1234#//#John Doe#//#555-1234#//#5000

User data (for login and permissions) is stored in a separate file and handled similarly.

All data operations are handled manually using C++ file streams (fstream).
No external database is used.

🧠 What I Practiced
Using Structs to model client and user data
File handling with fstream
Working with vectors and iteration
String parsing and splitting
Writing modular functions for cleaner code
Building console menu systems
Implementing authentication & authorization (login system)
Managing users with CRUD operations and roles (admin)
🛠 Built With
C++
Visual Studio
