# 🏦 Bank Management System (C++)

A **console-based Bank Management System** built with **C++** that allows you to manage client accounts stored in a text file.

This project simulates basic banking operations and focuses on practicing **file handling, structs, vectors, and modular programming**.

---

## ✨ Features

* 📋 Show all clients
* ➕ Add a new client
* ❌ Delete a client by account number
* ✏️ Update client information
* 🔎 Find a client by account number

---

## ▶️ How to Run

1. Clone the repository
2. Open the project in **Visual Studio** or any C++ compiler
3. Build and run `main.cpp`
4. Make sure `Clients.txt` exists in the same directory as the executable

---

## 💾 Data Storage

Client data is stored in a **`.txt` file** using a custom delimiter format:

```
#//#
```

Example record:

```
A150#//#1234#//#John Doe#//#555-1234#//#5000
```

All data operations are handled manually using **C++ file streams (`fstream`)**.
No external database is used.

---

## 🧠 What I Practiced

* Using **Structs** to model client data
* **File handling** with `fstream`
* Working with **vectors** and iteration
* **String parsing and splitting**
* Writing **modular functions** for cleaner code

---

## 🛠 Built With

* **C++**
* **Visual Studio**
