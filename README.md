# 🏦 Bank Management System (C++)

A console-based Bank Management System built with C++ that manages client accounts stored in a text file.  
It simulates basic banking operations and focuses on practicing file handling, structs, vectors, and modular programming.

---

## ✨ Features

### 👥 Client Management
- 📋 Show all clients
- ➕ Add a new client
- ❌ Delete a client by account number
- ✏️ Update client information
- 🔎 Find a client by account number

### 💰 Transactions
- 💰 Deposit money
- 💸 Withdraw money
- 📊 Show total balances

### 🔐 User & Access Management
- 🔑 Login system
- 👤 Manage users (CRUD operations)
- 🛡️ Admin permissions
- 🚪 Logout functionality
- 💾 Users stored in a separate file

---

## 🖥️ Program Screens

**Main Menu**

> *(screenshot here)*

**Transactions Menu**

> *(screenshot here)*

---

## ▶️ How to Run

**1. Clone the repository**
```bash
git clone https://github.com/ilyassdxebec/bank-management-system-cpp.git
```

**2. Open the project**  
Use Visual Studio or any C++ compiler.

**3. Run the program**
```bash
main.cpp
```

**4. Important**  
Make sure `Clients.txt` exists in the same directory as the executable.

---

## 💾 Data Storage

Client data is stored in a `.txt` file using a custom delimiter:
```
#//#
```

Example:
```
A150#//#1234#//#John Doe#//#555-1234#//#5000
```

User data (login & permissions) is stored in a separate file using a similar format.  
All operations use C++ file streams (`fstream`) — no database.

---

## 🧠 What I Practiced

- Structs for modeling data
- File handling (`fstream`)
- Vectors & iteration
- String parsing & splitting
- Modular programming
- Console menu systems
- Authentication (login system)
- User management (CRUD + roles)

---

## 🛠️ Built With

- C++
- Visual Studio
