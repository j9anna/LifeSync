# LifeSync Program (C++)

## Overview
LifeSync is a console-based personal productivity program developed in C++. It allows a single user to manage tasks, events, and notes in one unified application. The program focuses on organization, prioritization, and efficient data management using core data structures.

---

## Features
- Console-based interface
- Task planner with priority-based sorting
- Event planner ordered by time
- Notes manager with update and undo functionality
- Search and display options for tasks and notes
- File loading support for tasks, events, and notes
- Input validation for reliable user interaction

---

## Program Modules
- **Tasks**
  - Add, remove, search, and display tasks
  - Tasks are sorted by priority using a doubly linked list
- **Events**
  - Add, remove, and view events
  - Events are managed using a min-heap based on time
- **Notes**
  - Add, update, undo updates, and display notes
  - Notes are stored using hashing with quadratic probing
  - Undo functionality implemented using a stack

---

## System Details
- Interface: Console based
- User type: Single user
- Data storage: File input supported
- Platform: Cross-platform (any system with a C++ compiler)
- Libraries: Standard C++ only

---

## Installation and Running
### Requirements
- C++ compiler (such as g++)

### Steps
1. Clone or download the repository
2. Open a terminal in the project directory
3. Compile the program:
   ```bash
   g++ main.cpp -o lifesync
## Run the program
./lifesync

## Technologies Used

1. C++
2. Standard Template
3. LibraryFile handling and streams
