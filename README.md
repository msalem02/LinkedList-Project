# Linked List Project  
### Data Structure Implementation, Operations, and Applications in C / C++

---

## 1. Overview

The **Linked List Project** is a comprehensive implementation and study of **linked data structures**, focusing on the creation, manipulation, and traversal of singly and doubly linked lists.  
It demonstrates fundamental computer science principles such as **dynamic memory allocation**, **pointer manipulation**, and **algorithmic operations** on linear data structures.

This project provides a modular and extensible base for implementing **insertions, deletions, searches, sorting, merging**, and **reversing** operations, serving as a strong foundation for understanding dynamic data management in memory-constrained environments.

---

## 2. Objectives

- Implement **Singly Linked List**, **Doubly Linked List**, and **Circular Linked List**.  
- Perform complete CRUD (Create, Read, Update, Delete) operations.  
- Demonstrate traversal, searching, sorting, and merging algorithms.  
- Manage dynamic memory efficiently and safely.  
- Visualize and test operations using menu-based input from the user.  
- Provide a codebase that adheres to clean, reusable, and maintainable design principles.

---

## 3. Project Structure

```
LinkedList-Project/
│
├── src/
│   ├── linkedlist_singly.c / .cpp     # Singly Linked List implementation
│   ├── linkedlist_doubly.c / .cpp     # Doubly Linked List implementation
│   ├── linkedlist_circular.c / .cpp   # Circular Linked List implementation
│   ├── operations.c / .cpp            # Insert, delete, search, sort, reverse functions
│   ├── utils.c / .cpp                 # Helper functions and validation routines
│   └── main.c / main.cpp              # Main driver with menu interface
│
├── include/
│   ├── linkedlist.h                   # Function prototypes and struct definitions
│   ├── operations.h
│   ├── utils.h
│   └── menu.h                         # CLI functions
│
├── tests/
│   ├── test_singly.txt
│   ├── test_doubly.txt
│   ├── test_circular.txt
│   └── run_tests.sh
│
├── Makefile / CMakeLists.txt          # Build automation file
├── input.txt                          # Example input for menu system
├── output.txt                         # Expected output log
└── README.md
```

---

## 4. Data Structure Design

### 4.1 Singly Linked List
```c
struct Node {
    int data;
    struct Node* next;
};
```
- Linear sequence of nodes.  
- Traversed only in one direction.  
- Efficient insertion/deletion at head.

### 4.2 Doubly Linked List
```c
struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
};
```
- Bidirectional traversal (forward and backward).  
- Efficient insertions/deletions from both ends.  
- Slightly more memory usage due to extra pointer.

### 4.3 Circular Linked List
- Last node’s next pointer points to the head node.  
- Can be singly or doubly circular.  
- Commonly used in queue-like structures and process scheduling.

---

## 5. Core Operations

| Operation | Description | Time Complexity |
|------------|--------------|-----------------|
| `insertAtBeginning()` | Insert new node at start | O(1) |
| `insertAtEnd()` | Insert new node at end | O(n) |
| `insertAtPosition()` | Insert at specific index | O(n) |
| `deleteAtBeginning()` | Delete first node | O(1) |
| `deleteAtEnd()` | Delete last node | O(n) |
| `deleteAtPosition()` | Delete at specific index | O(n) |
| `search()` | Find node by key | O(n) |
| `reverse()` | Reverse linked list | O(n) |
| `sort()` | Sort nodes (ascending/descending) | O(n²) typical |
| `merge()` | Merge two linked lists | O(n + m) |

---

## 6. Implementation Notes

- All operations dynamically allocate memory via `malloc()` or `new` (in C++).  
- Memory cleanup (`free()` / `delete`) is implemented for all delete operations.  
- The project uses **function modularization** for clarity (separate source and header files).  
- Safety checks for **NULL pointers** and **empty lists** are implemented.  
- Debugging macros or print statements can be toggled in `utils.h`.

---

## 7. Example Usage

**Example Menu (Main CLI Program):**
```
========== LINKED LIST MENU ==========
1. Insert at Beginning
2. Insert at End
3. Delete at Position
4. Search Element
5. Display List
6. Reverse List
7. Sort List
8. Exit
======================================
Enter your choice:
```

**Sample Execution:**
```
Enter your choice: 1
Enter value: 10
Node inserted successfully.

Enter your choice: 2
Enter value: 20
Node inserted successfully.

Enter your choice: 5
Linked List: 10 -> 20 -> NULL
```

---

## 8. Example Input / Output

### Input (input.txt)
```
1 10
1 5
2 20
4 5
3 2
5
```

### Output (output.txt)
```
Inserted 10 at beginning.
Inserted 5 at beginning.
Inserted 20 at end.
Found element 5 at position 2.
Deleted node at position 2.
List: 5 -> 20 -> NULL
```

---

## 9. Algorithmic Insights

| Algorithm | Concept Demonstrated | Benefit |
|------------|----------------------|----------|
| Traversal | Sequential pointer iteration | Foundation for all operations |
| Insertion | Pointer re-linking logic | Dynamic memory handling |
| Deletion | Safe node removal | Prevents dangling references |
| Sorting | Bubble/Insertion/Selection sort | Reinforces algorithm analysis |
| Reversal | In-place pointer reversal | Efficient manipulation without arrays |

---

## 10. Build & Run Instructions

### Using GCC
```bash
gcc src/*.c -o linkedlist_app
./linkedlist_app
```

### Using Makefile
```bash
make
./linkedlist_app
```

### Using CMake
```bash
mkdir build
cd build
cmake ..
make
./linkedlist_app
```

---

## 11. Testing

- Automated scripts (`tests/run_tests.sh`) execute input files against expected outputs.  
- Manual testing supported through interactive mode.  
- Boundary conditions tested (empty list, invalid index, null insertions).

---

## 12. Error Handling

- Attempts to delete from an empty list trigger friendly warnings.  
- Insertion at invalid positions safely rejected.  
- Memory allocation failures handled gracefully.  
- Prevents segmentation faults via null-check guards.  

---

## 13. Educational Outcomes

Through this project, students gain hands-on experience with:
- **Dynamic data structure management.**
- **Pointer arithmetic and memory referencing.**
- **Linked data organization for sequential and circular lists.**
- **Algorithmic thinking in structure manipulation.**
- **Error prevention and modular C programming design.**

---

## 14. Future Enhancements

- Add **Generic Linked List** using templates (C++).  
- Implement **Doubly Circular Linked List**.  
- Integrate **Graph adjacency list** using linked structures.  
- Create **Visualization GUI** to display node links dynamically.  
- Add persistent storage (save/load lists to files).

---

## 15. Author

Mohammed Salem  
Email: salemmohamad926@gmail.com  
LinkedIn: https://www.linkedin.com/in/msalem02  
GitHub: https://github.com/msalem02

---

## 16. License

This project is licensed under the **MIT License**.  
You may use, modify, and distribute it freely with attribution.  

---

## 17. Acknowledgements

- Birzeit University — Department of Computer Engineering  
- Data Structures course instructors and mentors  
- Open-source documentation and C reference materials  
- Peers and testers for feedback during development  

---

## 18. Version History

| Version | Date | Description |
|----------|------|-------------|
| 1.0 | February 2024 | Singly Linked List core functions |
| 1.1 | March 2024 | Added doubly linked list module |
| 1.2 | April 2024 | Added circular list and sorting functions |
| 2.0 | June 2024 | Refined modular architecture and test framework |

---
