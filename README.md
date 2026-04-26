# Gaming Cafe Management System

A console-based C++ application that simulates the management of a gaming café. It handles PC availability, user registration (Regular and VIP), session tracking, hourly billing, and persistent data storage — all built using core Object-Oriented Programming principles.



## Group Members

| Name           | Student ID |
|----------------|------------|
| Hamza Rashid   | 25K-0945   |
| Syed Wajih     | 25K-0797   |

---

## Use Cases

1. **Register a Regular User** — Add a walk-in customer with a name, contact number, and initial wallet balance.
2. **Register a VIP User** — Add a premium member with a discounted hourly rate (Rs. 60/hr vs Rs. 80/hr) and membership expiry tracking.
3. **Start a Gaming Session** — Assign an available PC to a user; the system timestamps the session start and marks the PC as Occupied.
4. **End a Session & Generate Bill** — Enter hours played; the system calculates cost using the user's rate (polymorphism), deducts from balance, and prints a formatted bill.
5. **Search for a User** — Find a user by ID or partial name match.
6. **Manage PC Status** — Add PCs, remove them, or toggle Maintenance mode to prevent bookings on faulty machines.
7. **Persist Data** — All users, PCs, and sessions are saved to text files and reloaded automatically on the next run.
8. **View Active Sessions** — See which PCs are currently in use and by which user.

---

## How to Compile

Make sure you have `g++` with C++17 support installed.

**Using Make:**
```bash
make
```

**Manually:**
```bash
g++ -std=c++17 -Wall -o gaming_cafe main.cpp User.cpp Member.cpp PC.cpp Session.cpp Billing.cpp CafeManager.cpp
```

---

## How to Run

```bash
./gaming_cafe
```
On Windows:
```bash
gaming_cafe.exe
```

---

## How to Use the System

When launched, you will see the **Main Menu**:

```
1. User Management
2. PC Management
3. Session Management
4. Save Data
0. Exit
```

### Typical Workflow

1. Go to **PC Management → Add PC** to register gaming machines.
2. Go to **User Management → Add Regular/VIP User** to register customers.
3. Go to **Session Management → Start Session** — pick a PC and a User ID.
4. When done playing, go to **Session Management → End Session**, enter the PC ID and hours played. A bill is printed automatically.
5. Data is saved automatically on exit or manually via **Save Data**.

### Input Validation
- All numeric inputs are validated; invalid entries prompt re-entry.
- You cannot start a session on an Occupied or Maintenance PC.
- You cannot end a session if the user's balance is insufficient.
- You cannot delete an occupied PC.

---

## OOP Concepts Used

| Concept | Where Applied |
|---|---|
| Classes & Objects | `User`, `PC`, `Session`, `Billing`, `CafeManager` |
| Encapsulation | All member variables are `private`; accessed via getters/setters |
| Inheritance | `RegularUser` and `VIPUser` derive from abstract `User` |
| Polymorphism | `getHourlyRate()` and `getUserType()` are virtual; `Billing` calls them via `User*` |
| Abstraction | `User` is an abstract class (pure virtual methods) |
| Dynamic Memory | `new`/`delete` used for all `User*`, `PC*`, `Session*` objects |
| Exception Handling | `try/catch` blocks wrap all user inputs and operations |
| File Handling | `saveData()` / `loadData()` persist all data to `.txt` files |
| Modular Design | Separate `.h` header and `.cpp` source files for each class |

---

## File Structure

```
gaming_cafe/
├── main.cpp          # Entry point, menu interface
├── User.h / .cpp     # Abstract base class
├── Member.h / .cpp   # RegularUser and VIPUser derived classes
├── PC.h / .cpp       # PC entity
├── Session.h / .cpp  # Session entity
├── Billing.h / .cpp  # Billing logic (uses polymorphism)
├── CafeManager.h/.cpp# Central controller (CRUD, file I/O)
├── Makefile
├── users.txt         # Auto-generated on save
├── pcs.txt           # Auto-generated on save
└── sessions.txt      # Auto-generated on save
```

---

## Assumptions & Limitations

- Time is recorded using the system clock. Hours played are **manually entered** by the operator when ending a session (the system does not automatically compute elapsed time).
- Billing uses a wallet/balance system. Users must have a sufficient balance before a session can be closed.
- VIP hourly rate: **Rs. 60/hr** | Regular hourly rate: **Rs. 80/hr**.
- Data is stored in plain-text pipe-delimited files (`|`). Names and specs should not contain the `|` character.
- The system is single-operator (no login/authentication system).
- No concurrent multi-user GUI — this is a console application designed for one operator at a time.
