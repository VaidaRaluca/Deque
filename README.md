# Block-Based Deque Implementation in C++

## Overview
This project implements a **block-based deque (double-ended queue)** in C++ using **templates and arrays**. The deque supports efficient insertions and deletions at both ends, ensuring optimal performance.

## Key Features
- **Efficient Insertions & Deletions**: Uses a **block-based memory structure** to allow fast `push_front` and `push_back` operations.
- **Dynamic Expansion**: Adds new blocks dynamically when the deque reaches capacity.
- **Indexing Support**: Implements **operator overloading** for direct access using `operator[]`.
- **Custom Memory Management**: Uses a structured **MemoryBlock** to manage addresses.
- **Interactive CLI**: A menu-driven interface enables easy user interaction.

## Core Components

### 1. **Deque Class Template**
The `Deque<T, BlockSize>` class defines a **generic deque** that can store any data type (`T`) and operates with a fixed block size (`BlockSize`).

#### **Memory Management**
- Uses a **2D array** (`std::array<std::array<T, BlockSize>, 2>`) to store elements efficiently.
- A `MemoryBlock` struct manages memory addresses, enabling **fast block access**.

#### **Push & Pop Operations**
- `push_front(const T& val)`: Inserts an element at the **front**.
- `push_back(const T& val)`: Inserts an element at the **back**.
- `pop_front()`: Removes an element from the **front**.
- `pop_back()`: Removes an element from the **back**.

### 2. **Block Expansion**
When a block is **full**, a new block is added dynamically:
- `addBlockAtFront()`
- `addBlockAtBack()`

### 3. **Element Access & Modification**
- `operator[](size_t i)`: Allows **direct indexed access**.
- `insert(const T& val, size_t pos)`: Inserts a value at a **specific position**.
- `deletePosition(size_t pos)`: Removes an element from a **specific index**.
- `front()` & `back()`: Retrieve the **first** and **last** elements.
- `size()` & `empty()`: Check the **current size** and **empty status**.

### 4. **Memory Cleanup & Printing**
- `clear()`: Resets the deque by **removing all elements**.
- `print()`: Displays the deque elements in **console output**.

## Conclusion
By developing this application, I gained a deeper understanding of template programming and efficient data structure design in C++. I strengthened my skills in algorithm optimization by implementing a block-based deque that enables fast insertions and deletions.

## User Interface
The `main()` function implements an **interactive menu**, allowing users to:
1. Push elements to the front/back.
2. Pop elements from the front/back.
3. Access and modify elements at specific positions.
4. Insert or delete elements dynamically.
5. Display size, check empty status, and clear the deque.

### **Example Usage**
```cpp
Deque<int, 8> deque;
deque.push_back(1);
deque.push_front(2);
deque.push_back(3);
deque.push_front(4);
deque.print();  // Output: 4 2 1 3
