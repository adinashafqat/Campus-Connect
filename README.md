# CAMPUS MANAGEMENT & COLLABORATION SYSTEM

---

## **PROJECT OVERVIEW**

The Campus Management & Collaboration System is a console-based C++ application designed to simulate core campus operations such as student management, room booking, event handling, campus navigation, and study partner matching.

The system integrates multiple data structures to efficiently manage and organize data while providing role-based access for students and administrators.

---

## **PROJECT OBJECTIVES**

- Manage student registration and login securely  
- Represent campus layout using graph data structures  
- Enable room booking with priority-based scheduling  
- Organize campus events efficiently  
- Recommend study partners based on shared interests  
- Maintain logs and persistent data using files  
- Apply multiple Data Structures and Algorithms (DSA) concepts in one system  

---

## **REAL-WORLD PROBLEM**

Modern university campuses face challenges such as:

- Difficulty in finding available study spaces  
- Inefficient event coordination  
- Lack of collaboration tools  
- Fragmented systems causing inconsistency  

This system provides a centralized solution to manage all these operations efficiently.

---

## **JUSTIFICATION**

- Centralized management of campus operations  
- Faster data access using optimized data structures  
- Efficient scheduling and prioritization  
- Demonstrates real-world application of DSA concepts  

---

## **DATA STRUCTURES USED**

### **Graph**
- Used for campus navigation  
- Models locations as nodes and paths as edges  

### **Hash Tables**
- Used for student lookup (email, ID)  
- Provides O(1) average time complexity  

### **Heap (Priority Queue)**
- Used for room booking  
- Handles priority-based scheduling  

### **Binary Search Tree (BST)**
- Used for event management  
- Stores events in sorted order  

### **Stack**
- Used for undo/redo operations  
- Follows LIFO principle  

### **Arrays**
- Used for activity logs  

---

## **SYSTEM ARCHITECTURE**

                ┌──────────────────────────────┐
                │        START PROGRAM          │
                └──────────────┬───────────────┘
                               │
                ┌──────────────▼───────────────┐
                │     USER INTERFACE LAYER      │
                │ ─ Menu System                 │
                │ ─ Input Validation            │
                │ ─ Screen Management           │
                └──────────────┬───────────────┘
                               │
                ┌──────────────▼───────────────┐
                │     BUSINESS LOGIC LAYER      │
                │                               │
                │  ┌────────────────────────┐ │
                │  │ Student Management      │ │
                │  └────────────────────────┘ │
                │  ┌────────────────────────┐ │
                │  │ Booking Management      │ │
                │  └────────────────────────┘ │
                │  ┌────────────────────────┐ │
                │  │ Event Management        │ │
                │  └────────────────────────┘ │
                │  ┌────────────────────────┐ │
                │  │ Partner Matching        │ │
                │  └────────────────────────┘ │
                │  ┌────────────────────────┐ │
                │  │ Campus Navigation       │ │
                │  └────────────────────────┘ │
                │  ┌────────────────────────┐ │
                │  │ Activity Logging        │ │
                │  └────────────────────────┘ │
                └──────────────┬───────────────┘
                               │
                ┌──────────────▼───────────────┐
                │    DATA STRUCTURE LAYER       │
                │                               │
                │ ─ Hash Tables (Email, ID)     │
                │ ─ Min Heap (Bookings)         │
                │ ─ BST (Events)                │
                │ ─ Graph (Campus Map)          │
                │ ─ Stacks (Undo / Redo)        │
                │ ─ Arrays (Logs)               │
                └──────────────┬───────────────┘
                               │
                ┌──────────────▼───────────────┐
                │      PERSISTENCE LAYER        │
                │ ─ pupils.dat                  │
                │ ─ books.dat                   │
                │ ─ events.dat                  │
                │ ─ File Read / Write           │
                └──────────────┬───────────────┘
                               │
                ┌──────────────▼───────────────┐
                │        END PROGRAM            │


---

## **TECHNOLOGY STACK**

- Programming Language: C++  

### **Concepts Used**
- Data Structures and Algorithms  
- File Handling  
- Modular Programming  
- Role-based system design  

---

## **CONCLUSION**

The Campus Management & Collaboration System demonstrates the practical use of multiple data structures to solve real-world campus problems.

It efficiently manages student data, bookings, events, and collaboration while ensuring data persistence and system organization.

The project highlights strong understanding of DSA concepts, file handling, and structured programming in C++.
