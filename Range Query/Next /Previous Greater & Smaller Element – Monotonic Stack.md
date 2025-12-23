# Next / Previous Greater & Smaller Element – Monotonic Stack Master Guide

* Next Greater Element (NGE)
* Next Smaller Element (NSE)
* Previous Greater Element (PGE)
* Previous Smaller Element (PSE)

using the **Monotonic Stack technique**.

These patterns appear **extremely frequently** in SDE interviews and competitive programming.

---

# 🧠 Big Picture (INTERVIEW MENTAL MODEL)

> **Whenever a problem asks about nearest greater/smaller element to left or right → think MONOTONIC STACK.**

This technique converts **O(n²)** brute force solutions into **O(n)**.

---

# 🔑 Core Idea: Monotonic Stack

A **Monotonic Stack** is a stack that maintains elements in either:

* **Increasing order** (for smaller-element queries)
* **Decreasing order** (for greater-element queries)

Each element is pushed and popped **at most once** → linear time.

---

# 📊 Visual Diagram (Example)

Array:

```
[4, 5, 2, 10, 8]
```

### Next Greater Element (Right)

```
Index:  0  1  2  3  4
Value:  4  5  2 10  8
NGE:    5 10 10 -1 -1
```

---

# 1️⃣ Next Greater Element (NGE)

## Definition

For each element, find the **first greater element to its right**.

---

## Algorithm (Using Stack)

* Traverse from **right to left**
* Maintain **decreasing stack**

---

## C++ Code – NGE

```cpp
vector<int> nextGreater(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() && st.top() <= arr[i])
            st.pop();
        ans[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return ans;
}
```

---

## Time & Space Complexity

* **Time:** O(n)
* **Space:** O(n)

---

# 2️⃣ Next Smaller Element (NSE)

## Definition

For each element, find the **first smaller element to its right**.

---

## C++ Code – NSE

```cpp
vector<int> nextSmaller(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i = n - 1; i >= 0; i--) {
        while(!st.empty() && st.top() >= arr[i])
            st.pop();
        ans[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return ans;
}
```

---

# 3️⃣ Previous Greater Element (PGE)

## Definition

For each element, find the **first greater element to its left**.

---

## C++ Code – PGE

```cpp
vector<int> prevGreater(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i = 0; i < n; i++) {
        while(!st.empty() && st.top() <= arr[i])
            st.pop();
        ans[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return ans;
}
```

---

# 4️⃣ Previous Smaller Element (PSE)

## Definition

For each element, find the **first smaller element to its left**.

---

## C++ Code – PSE

```cpp
vector<int> prevSmaller(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for(int i = 0; i < n; i++) {
        while(!st.empty() && st.top() >= arr[i])
            st.pop();
        ans[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return ans;
}
```

---

# 🧩 ALL MAJOR PROBLEMS USING THIS PATTERN (INTERVIEW GOLD)

## 🔥 Next / Previous Greater

* Next Greater Element I / II (LeetCode)
* Stock Span Problem
* Daily Temperatures
* Circular Next Greater Element

## 🔥 Next / Previous Smaller

* Largest Rectangle in Histogram
* Maximal Rectangle (Matrix)
* Sum of Subarray Minimums
* Minimum Cost Tree From Leaf Values

## 🔥 Mixed (Greater + Smaller)

* Trapping Rain Water
* Sliding Window Maximum
* Remove K Digits
* Asteroid Collision
* Online Stock Span

---

# 🔄 Comparison with Other Approaches

| Approach         | Time       | Space | Notes   |
| ---------------- | ---------- | ----- | ------- |
| Brute Force      | O(n²)      | O(1)  | TLE     |
| Divide & Conquer | O(n log n) | O(n)  | Complex |
| Monotonic Stack  | **O(n)**   | O(n)  | Optimal |

---

# 🎯 When to Use Monotonic Stack

✔ Nearest greater/smaller problems
✔ Range dominance problems
✔ Histogram / subarray problems

---

# 🛑 When NOT to Use

✖ When order does not matter
✖ When random access required

---

# 🌍 Real-World Applications

* Stock price analysis
* Weather forecasting (temperature trends)
* Skyline problems
* Financial risk modeling
* Signal processing

---

# 💬 Interview-Ready Q&A

### Q1: Why is monotonic stack O(n)?

Each element is pushed and popped once.

### Q2: Why traverse from right for NGE?

Because we need nearest element on the right.

### Q3: Can this be done with queue?

No, stack is required for backtracking.

### Q4: Why stack stores values not indices sometimes?

Depends on whether distance or value is needed.

---

# 🎯 Final Takeaway

> **If a problem asks for nearest greater/smaller element, a monotonic stack is almost always the optimal solution.**

Mastering this pattern unlocks **dozens of hard interview problems**.

---

Repository complete.
