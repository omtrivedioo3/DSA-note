# C++ STL Functions That Return Iterators – Ultra‑Deep Interview & Problem‑Solving Guide

# 🧠 Big Picture: Why Iterator‑Returning Functions Matter

Most STL algorithms **do NOT return values** — they return **iterators**.

Interviewers expect you to know:

* What iterator you got
* Whether it can be incremented / decremented
* Whether you can get an index from it
* Whether it can be dereferenced safely

> ❗ Misusing iterators is one of the **most common causes of wrong answers in interviews**.

---

# 📐 What an Iterator Actually Holds (Quick Recap)

| Container     | What Iterator Refers To Internally |
| ------------- | ---------------------------------- |
| vector        | Memory address (pointer‑like)      |
| deque         | Block + offset                     |
| map / set     | Tree node pointer                  |
| unordered_map | Hash bucket node                   |

This explains **why iterator arithmetic works only for vector/deque**.

---

# 1️⃣ vector – Functions That Return Iterators

## Common Iterator‑Returning Functions

```cpp
v.begin();
v.end();
v.rbegin();
v.rend();
v.cbegin();
v.cend();

find(v.begin(), v.end(), x);
lower_bound(v.begin(), v.end(), x);
upper_bound(v.begin(), v.end(), x);

v.insert(pos, value);   // returns iterator to inserted element
v.erase(pos);           // returns iterator to next element
```

---

## How to Get Value from vector Iterator

```cpp
int value = *it;
```

---

## How to Get Index from vector Iterator (VERY IMPORTANT)

```cpp
int index = it - v.begin();  // O(1)
```

### Why This Works

Because vector iterators are **random‑access iterators**.

---

## Example – Typical Interview Pattern

```cpp
auto it = lower_bound(v.begin(), v.end(), x);
if(it != v.end()) {
    int idx = it - v.begin();
    int val = *it;
}
```

---

## Time Complexity (vector)

| Operation      | Time     |
| -------------- | -------- |
| begin / end    | O(1)     |
| lower_bound    | O(log n) |
| find           | O(n)     |
| erase / insert | O(n)     |

---

# 2️⃣ set – Functions That Return Iterators

## Iterator‑Returning Functions

```cpp
st.begin();
st.end();
st.find(x);
st.lower_bound(x);
st.upper_bound(x);
st.insert(x);    // returns pair<iterator, bool>
st.erase(it);    // returns iterator to next element
```

---

## How to Get Value from set Iterator

```cpp
int value = *it;
```

---

## ❌ Getting Index from set Iterator

```cpp
it - st.begin(); // ❌ NOT ALLOWED
```

### Correct (but slow) way

```cpp
int index = distance(st.begin(), it); // O(n)
```

---

## Time Complexity (set)

| Operation          | Time     |
| ------------------ | -------- |
| find / lower_bound | O(log n) |
| distance           | O(n)     |

---

# 3️⃣ map – Functions That Return Iterators

## Iterator‑Returning Functions

```cpp
mp.begin();
mp.end();
mp.find(key);
mp.lower_bound(key);
mp.upper_bound(key);
mp.insert({k, v});  // returns pair<iterator, bool>
mp.erase(it);       // returns iterator to next element
```

---

## How to Get Key & Value from map Iterator

```cpp
int key = it->first;
int value = it->second;
```

---

## ❌ Index from map Iterator

Not possible directly.

```cpp
it - mp.begin(); // ❌ compilation error
```

Reason: map iterators are **bidirectional**, not random‑access.

---

## First & Last Element (Interview Favorite)

```cpp
auto first = mp.begin();
auto last  = prev(mp.end());
```

---

## Time Complexity (map)

| Operation          | Time     |
| ------------------ | -------- |
| find / lower_bound | O(log n) |
| insert / erase     | O(log n) |

---

# 4️⃣ unordered_map – Iterator Functions

## Iterator‑Returning Functions

```cpp
ump.begin();
ump.end();
ump.find(key);
ump.insert({k, v});  // returns pair<iterator, bool>
```

---

## How to Get Key & Value

```cpp
int key = it->first;
int value = it->second;
```

---

## ⚠️ Important Interview Notes

* No order guarantee
* Iterator arithmetic NOT allowed
* Worst‑case operations O(n)

---

# 🔄 Comparison Summary (VERY IMPORTANT)

| Container     | Iterator Type | Can get Index? | Typical Use           |
| ------------- | ------------- | -------------- | --------------------- |
| vector        | Random‑access | ✔ O(1)         | Binary search, arrays |
| set           | Bidirectional | ❌              | Ordered unique values |
| map           | Bidirectional | ❌              | Ordered key‑value     |
| unordered_map | Forward       | ❌              | Fast lookup           |

---

# 🎯 When to Use Iterator‑Returning Functions

✔ Binary search problems
✔ Range queries
✔ Ordered data traversal
✔ Greedy algorithms

---

# 🛑 When NOT to Use

✖ When only existence is needed (`count` may suffice)
✖ When index is mandatory but container is non‑random access

---

# 🌍 Real‑World Applications

* Database indexing
* Scheduling systems
* Search engines
* Financial order books
* Interval problems

---

# 💬 Interview Q&A

### Q1: Why do STL algorithms return iterators instead of values?

To remain generic across containers.

### Q2: How do you safely check iterator validity?

Compare with `end()` before dereferencing.

### Q3: Why `it - begin()` works only for vector?

Because only vector provides random‑access iterators.

### Q4: What does `erase()` return?

Iterator to the next valid element.

---

# 🎯 Final Takeaway

> **Understanding iterator‑returning functions is essential for writing correct STL‑based solutions in interviews.**

If you know what iterator you got and what operations are allowed on it, you avoid 90% of STL bugs.

---

Repository complete.
