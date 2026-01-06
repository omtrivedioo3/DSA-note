# Minimum Cost Array Conversion (Monotonic)

> **Goal:** Convert an integer array into either **non-decreasing** or **non-increasing** order with **minimum total cost**, and also return the **modified array** that achieves this minimum cost.

---

## 🧠 Problem Statement

Given an integer array `nums`, you are allowed to **decrease elements** (not increase them).

* The **cost** of decreasing an element is the absolute amount decreased.
* You need to:

  1. Convert the array into **non-decreasing** order OR
  2. Convert the array into **non-increasing** order
* Return:

  * The **minimum possible cost**
  * The **modified array** that achieves this cost

---

## 💡 High-Level Idea

We solve **two subproblems**:

1. Minimum cost to make the array **non-decreasing**
2. Minimum cost to make the array **non-increasing**

Then we return the result with the **smaller cost**.

Key technique used:

> **Greedy + Max Heap (Priority Queue)**

---

## 🔑 Core Insight

For a **non-decreasing array**:

```
a[0] ≤ a[1] ≤ a[2] ≤ ...
```

If at any position `i`, a previous element is **greater** than `a[i]`, we must reduce it.

To minimize cost:

* Always reduce the **largest violating element first**
* This is why we use a **max heap**

---

## 🧮 Algorithm Explanation

### Case 1: Non-Decreasing Array

1. Traverse array left → right
2. Maintain a **max heap of (value, index)**
3. At each index `i`:

   * Push `(value, index)` into heap
   * If `heap.top().value > current_value`:

     * Reduce that value to `current_value`
     * Add difference to cost
     * Update result array

### Case 2: Non-Increasing Array

* Negate all values in the array
* Apply **same non-decreasing logic**
* Negate the result back

This avoids writing duplicate logic.

---

## 🖼️ Text-Based Diagram

Example: `nums = [3, 1, 2, 1]`

```
Step 1: 3
Heap: [3]

Step 2: 1
Heap: [3,1]  → violation (3 > 1)
Reduce 3 → 1, cost += 2
Heap: [1,1]

Step 3: 2
Heap: [2,1,1]

Step 4: 1
Heap: [2,1,1,1] → violation
Reduce 2 → 1, cost += 1

Final array: [1,1,1,1]
Total cost: 3
```

---

## ✅ Complete C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    pair<long long, vector<int>> makeNonDecreasing(vector<int> nums) {
        int n = nums.size();
        vector<int> res = nums;
        priority_queue<pair<int,int>> maxHeap; // {value, index}
        long long cost = 0;

        for (int i = 0; i < n; i++) {
            maxHeap.push({res[i], i});

            if (maxHeap.top().first > res[i]) {
                auto [val, idx] = maxHeap.top();
                maxHeap.pop();

                cost += val - res[i];
                res[idx] = res[i];

                maxHeap.push({res[i], idx});
            }
        }
        return {cost, res};
    }

    pair<long long, vector<int>> makeNonIncreasing(vector<int> nums) {
        for (int &x : nums) x = -x;
        auto [cost, modified] = makeNonDecreasing(nums);
        for (int &x : modified) x = -x;
        return {cost, modified};
    }

    pair<long long, vector<int>> convertArray(vector<int>& nums) {
        auto inc = makeNonDecreasing(nums);
        auto dec = makeNonIncreasing(nums);
        return (inc.first <= dec.first) ? inc : dec;
    }
};
```

---

## ⏱️ Complexity Analysis

| Metric           | Value        |
| ---------------- | ------------ |
| Time Complexity  | `O(n log n)` |
| Space Complexity | `O(n)`       |

Reason:

* Each element is pushed/popped from heap once

---

## 🧪 Example

```
Input:  [1, 3, 2]

Non-decreasing → cost = 1, array = [1,2,2]
Non-increasing → cost = 2, array = [3,2,2]

Output:
Cost = 1
Array = [1,2,2]
```

---

## 🧩 When to Use This Algorithm

* When **only decreasing elements is allowed**
* When you need **minimum modification cost**
* When monotonic array constraints are required
* Interview problems involving **greedy + heap**

---

## 🚫 When NOT to Use This Algorithm

* When elements can be freely increased
* When array size is extremely large and `O(n log n)` is too slow
* When exact target array is predefined

---

## 🔍 Comparison with Other Approaches

| Approach      | Time       | Space | Notes       |
| ------------- | ---------- | ----- | ----------- |
| Brute Force   | O(n²)      | O(1)  | Inefficient |
| DP            | O(n²)      | O(n²) | Overkill    |
| Greedy + Heap | O(n log n) | O(n)  | ✅ Optimal   |

---

## 🌍 Real-World Applications

* Smoothing noisy sensor data
* Normalizing time-series data
* Budget adjustment problems
* Load balancing systems
* Financial risk normalization

---

## 🎤 Interview-Ready Notes

* Greedy strategy: fix worst violation first
* Max heap guarantees minimum cost
* Negation trick avoids duplicate logic
* Multiple valid arrays possible, cost is unique

---

## ❓ Interview Q&A

**Q: Why max heap and not min heap?**
A: We must reduce the *largest* violating value to minimize cost.

**Q: Why negation works for non-increasing?**
A: Non-increasing in original = non-decreasing in negated array.

**Q: Can this be optimized further?**
A: Not below `O(n log n)` with this constraint.

---

## ✅ Final Takeaway

> This problem is a textbook example of **Greedy + Heap optimization** and is highly valuable for **SDE interviews at top MNCs**.

---

⭐ If this README helped you, consider starring the repo and practicing similar heap-based greedy problems.
