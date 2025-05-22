# Restaurant Billing Management System

A comprehensive console-based restaurant billing management system developed in **C**. This project helps restaurant staff efficiently manage food orders, tables, and billing in real-time.

---

## Features

### Menu Management
- Add new food items with name and price
- View all items with ID and price
- Pre-loaded sample menu items on startup

### Order Management
- Place orders per table by item ID and quantity
- Multiple orders allowed per table

### Billing System
- Generate an itemized bill per table
- Displays name, quantity, unit price, and total amount

### Table Management
- Track up to 50 tables
- View table occupancy and order status

---

## How to Compile and Run

```bash
gcc -o restaurant restaurant.c
./restaurant
```

---

### Tech Stack
- Language: C
- Compiler: GCC
- Platform: Terminal (Linux/Windows)

---

## Team Members

- **Sai Mani Ritish** (Lead)
- **Phalgun**
- **Sameer**
- **Sai Kiran**

---

### Future Scope
- Add persistent storage using file I/O or database integration
- Apply taxes and discount features
- Develop a web or GUI version
- Add user roles (e.g., admin and waiter login systems)
