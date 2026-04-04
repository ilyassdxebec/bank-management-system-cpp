# 🏦 Bank Management System (C++)

A console-based Bank Management System built in C++ that manages client accounts stored in text files.
It simulates basic banking operations and focuses on practicing file handling, structs, vectors, and modular programming.

## ✨ Features

### 👥 Client Management

📋 Show all clients
➕ Add a new client
❌ Delete a client by account number
✏️ Update client information
🔎 Find a client by account number

### 💰 Transactions

💰 Deposit money
💸 Withdraw money
📊 Show total balances

### 🔐 User & Access Management

🔑 Login system
👤 Manage users (CRUD operations)
➕ Add user ✔️
❌ Delete user – TODO
✏️ Update user – TODO
🔎 Find user – TODO
🛡️ Admin permissions
🚪 Logout functionality
💾 Users stored in a separate file

## 🖥️ Program Screens

### Main Menu
(screenshot placeholder)

### Transactions Menu
(screenshot placeholder)

### Manage Users Menu
(screenshot placeholder)

## ▶️ How to Run

### 1. Clone the repository

git clone https://github.com/ilyassdxebec/bank-management-system-cpp.git

### 2. Open the project
Use Visual Studio or any C++ compiler.

### 3. Run the program
Execute main.cpp.

## 💾 Data Storage

Client data is stored in a .txt file using a custom delimiter:

#//#

Example:

A150#//#1234#//#John Doe#//#555-1234#//#5000

User data (login & permissions) is stored in a separate file using the same format.
All operations use C++ file streams (fstream) — no database.

## 🧠 What I Practiced

Structs for modeling data
File handling (fstream)
Vectors & iteration
String parsing & splitting
Modular programming
Console menu systems
Authentication (login system)
User management (CRUD + roles, partial)
Permission/role-based access control

## 🛠️ Built With

C++
Visual Studio
