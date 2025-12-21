# Fenwick Tree (Binary Indexed Tree) 

---

# 📘 Introduction

A **Fenwick Tree**, also known as a **Binary Indexed Tree (BIT)**, is a data structure that efficiently supports:

* **Prefix sum queries**
* **Point updates**

It provides both operations in **O(log n)** while requiring only **O(n)** space.

Fenwick Tree is simpler and more memory-efficient than Segment Tree.

---

# 🧠 Core Idea

The Fenwick Tree stores partial prefix sums using the binary representation of indices.
Each index is responsible for maintaining the sum of a range of elements.

Key insight:

```
Last significant bit (LSB) of index i = i & (-i)
```

This tells us how far each Fenwick node extends.

---

# 📊 ASCII Diagram – How Fenwick Tree Stores Data

For an array of size 8:

```
Index (i):        1  2  3  4  5  6  7  8
Binary:        001 010 011 100 101 110 111 1000
LSB(i):        1   2   1   4   1   2   1   8

Ranges stored:
BIT[1] = A[1]
BIT[2] = A[1..2]
BIT[3] = A[3]
BIT[4] = A[1..4]
BIT[5] = A[5]
BIT[6] = A[5..6]
BIT[7] = A[7]
BIT[8] = A[1..8]
```

Prefix sum uses LSB to jump "backwards".
Update uses LSB to jump "forwards".

---

# 🧮 Operations

### **1️⃣ Update index i by +val**

```
while i <= n:
    BIT[i] += val
    i += LSB(i)
```

### **2️⃣ Query prefix sum from 1 to i**

```
while i > 0:
    sum += BIT[i]
    i -= LSB(i)
```

Both operations take **O(log n)**.

---

# 📘 Full C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FenwickTree {
    int n;
    vector<int> bit;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // Add value 'val' at index 'i'
    void update(int i, int val) {
        while(i <= n) {
            bit[i] += val;
            i += (i & -i);
        }
    }

    // Prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while(i > 0) {
            sum += bit[i];
            i -= (i & -i);
        }
        return sum;
    }

    // Range sum [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    vector<int> arr = {0, 3, 2, -1, 6, 5, 4, -3, 3};
    int n = arr.size() - 1;
    FenwickTree ft(n);

    for(int i = 1; i <= n; i++) ft.update(i, arr[i]);

    cout << "Prefix sum till index 5 = " << ft.query(5);
}
```

---

# 🧩 Use Cases of Fenwick Tree

Fenwick Tree is ideal when you need:

✔ Frequent updates
✔ Frequent prefix queries
✔ Low memory usage
✔ Simple implementation

### Common problems:

* Prefix sums
* Range sum queries (RSQ)
* Inversion count problem
* Frequency tables
* Order statistics
* Competitive programming

---

# ⏱ Time & Space Complexity

| Operation | Time                         |
| --------- | ---------------------------- |
| Update    | O(log n)                     |
| Query     | O(log n)                     |
| Build     | O(n log n) OR O(n) optimized |
| Space     | O(n)                         |

---

# 🎯 When to Use Fenwick Tree

Use a BIT when:

* You need **fast prefix sum queries**
* You need **point updates**
* Memory is limited
* Implementation simplicity matters
* You need dynamic frequency tables

---

# 🛑 When NOT to Use Fenwick Tree

Do NOT use BIT when:

* You need **range updates + range queries** (use Segment Tree)
* You need **min/max/gcd queries** (Segment Tree again)
* You need **lazy propagation**
* You need very complex custom operations

---

# 🔄 Comparison: Fenwick Tree vs Segment Tree

| Feature                | BIT        | Segment Tree |
| ---------------------- | ---------- | ------------ |
| Memory                 | O(n)       | O(4n)        |
| Implementation         | Simple     | Complex      |
| Supports RSQ           | Yes        | Yes          |
| Supports Range Updates | No         | Yes          |
| Supports Min/Max       | No         | Yes          |
| Build Time             | O(n log n) | O(n)         |

BIT is simpler and lighter; Segment Tree is more powerful.

---

# 🌍 Real-World Applications

* Stock market cumulative analysis
* Leaderboards (updating & querying ranks)
* Counting inversions in arrays
* Live score updates
* Fenwick tree inside CP platforms (Codeforces, AtCoder)

---

# 💬 Interview Questions & Answers

### **Q1: Why use Fenwick Tree over Segment Tree?**

Because BIT uses less memory, is easier to code, and sufficient for prefix sum + point update problems.

### **Q2: Can BIT handle range updates?**

Not naturally — requires a *double BIT* trick. Segment Tree is preferred.

### **Q3: Why is BIT faster than a naive prefix sum?**

Prefix sum update = O(n), BIT update = O(log n).

### **Q4: Can BIT work with negative values?**

Yes, values can be any integers.

### **Q5: What is the intuition behind LSB (i & -i)?**

It isolates the rightmost set bit, representing the size of segment stored at that index.

---

# 🎯 Final Summary

Fenwick Tree is a lightweight and efficient data structure perfect for prefix sum queries and point updates.
It is simpler than Segment Trees and widely used in competitive programming and real-world analytics systems.

