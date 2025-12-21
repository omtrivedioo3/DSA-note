# Segment Tree

# 📘 Introduction

A **Segment Tree** is a powerful tree‑based data structure used to efficiently answer **range queries** and handle **updates** on an array.

Unlike Fenwick Tree, Segment Tree supports:

* Range queries (sum / min / max / gcd)
* Point updates
* Range updates (with Lazy Propagation)

All major operations run in **O(log n)** time.

---

# 🧠 Core Idea

The array is recursively divided into segments.
Each node of the tree stores information about a **range (segment)** of the array.

Root → entire array
Children → left & right halves

---

# 📊 ASCII Diagram – Segment Tree Structure

For array: `[1, 3, 5, 7, 9, 11]`

```
                       [1..6]
                   /               \
              [1..3]               [4..6]
            /        \            /        \
        [1..2]      [3]        [4..5]      [6]
       /      \                 /     \
    [1]      [2]             [4]     [5]
```

Each node stores information (sum / min / max) for its range.

---

# 🧮 Operations Supported

* Build Tree
* Range Query (sum / min / max)
* Point Update
* Range Update (Lazy Propagation)

All operations take **O(log n)** time.

---

# 📘 Full C++ Implementation (Range Sum + Point Update)

```cpp
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> seg;
    int n;

public:
    SegmentTree(int n) {
        this->n = n;
        seg.assign(4 * n, 0);
    }

    void build(int idx, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int query(int idx, int low, int high, int l, int r) {
        if (r < low || high < l) return 0;          // No overlap
        if (l <= low && high <= r) return seg[idx]; // Total overlap

        int mid = (low + high) / 2;
        return query(2 * idx + 1, low, mid, l, r)
             + query(2 * idx + 2, mid + 1, high, l, r);
    }

    void update(int idx, int low, int high, int pos, int val) {
        if (low == high) {
            seg[idx] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (pos <= mid)
            update(2 * idx + 1, low, mid, pos, val);
        else
            update(2 * idx + 2, mid + 1, high, pos, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
};
```

---

# 🧩 Use Cases of Segment Tree

Segment Tree is preferred when:

✔ Range queries are frequent
✔ Updates are frequent
✔ Queries are complex (min/max/gcd)
✔ Lazy propagation is required

Common problems:

* Range sum / min / max queries
* Competitive programming problems
* Interval queries
* Stock price analysis
* Gaming leaderboards

---

# ⏱ Time & Space Complexity

| Operation | Time     |
| --------- | -------- |
| Build     | O(n)     |
| Query     | O(log n) |
| Update    | O(log n) |
| Space     | O(4n)    |

---

# 🎯 When to Use Segment Tree

Use Segment Tree when:

* You need **range queries + updates**
* Query operation is not just sum
* Lazy propagation is required
* Fenwick Tree is insufficient

---

# 🛑 When NOT to Use Segment Tree

Do NOT use Segment Tree when:

* Only prefix sums are required (use Fenwick Tree)
* Memory is extremely limited
* Simpler solution works

---

# 🔄 Comparison: Segment Tree vs Fenwick Tree

| Feature       | Segment Tree    | Fenwick Tree |
| ------------- | --------------- | ------------ |
| Range Queries | ✔ Yes           | ❌ Limited    |
| Range Updates | ✔ Yes (Lazy)    | ❌ No         |
| Memory        | High            | Low          |
| Complexity    | Harder          | Easier       |
| Use Case      | Complex queries | Prefix sums  |

---

# 🌍 Real‑World Applications

* Financial analytics dashboards
* Stock market range analysis
* Game score tracking
* Database indexing
* Network traffic monitoring

---

# 💬 Interview Questions & Answers

### Q1: Why Segment Tree over Fenwick Tree?

Because Segment Tree supports complex range queries and lazy propagation.

### Q2: What is lazy propagation?

A technique to defer updates to child nodes to optimize range updates.

### Q3: Time complexity of Segment Tree?

O(log n) for query and update.

### Q4: Can Segment Tree handle negative values?

Yes.

### Q5: Why space is 4n?

Worst‑case complete binary tree representation.

---

# 🎯 Final Summary

Segment Tree is a powerful data structure for handling dynamic range queries and updates.
It is more flexible than Fenwick Tree but comes with higher memory and implementation complexity.

---
