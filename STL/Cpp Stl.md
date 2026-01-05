# C++ STL Containers & Language Internals – Ultra-Deep Interview & Problem-Solving Guide
---

# 🧠 Big Picture: STL Mental Model (IMPORTANT)

STL is NOT syntax. STL is about:

```
DATA ORGANIZATION + ACCESS PATTERN + TIME/SPACE TRADEOFF
```

Interviewers test:

* Can you pick the RIGHT container?
* Can you access elements safely?
* Do you understand iterator & memory behavior?

---
# 📌 StringStream in C++
`stringstream` is a powerful utility provided by the C++ Standard Library that allows developers to **treat strings as input/output streams**, similar to `cin` and `cout`.

It is extremely useful for:
- Parsing strings
- Tokenizing input
- Converting strings to numbers
- Handling formatted and delimited data

🔹 What is stringstream?

stringstream belongs to the <sstream> header and provides an interface to:

Read data from strings

Write data into strings

Parse structured text easily

It works exactly like standard streams (cin, cout) but operates on strings instead of stdin/stdout.


  
    string sst = "1,2,3,4,5,6,";
    stringstream st(sst);
    string token;
    while (getline(st, token, ',')) {
        cout << token << endl;
    }
    Output
    1 2 3 4 5 6


# 1️⃣ vector (Dynamic Array)

## Internal Structure

* Stored in **contiguous memory**
* Doubles capacity when full

```
Capacity: 8
Size:     5
[10][20][30][40][50][_][_][_]
```

## Access Patterns

```cpp
v[i];          // O(1)
v.at(i);       // O(1) + bounds check
v.front();     // first element
v.back();      // last element
```

## Insert / Delete

```cpp
v.push_back(x);        // amortized O(1)
v.pop_back();          // O(1)
v.insert(v.begin()+i); // O(n)
v.erase(v.begin()+i);  // O(n)
```

## Iterator Behavior

```cpp
auto it = v.begin();
v.push_back(100); // ❌ may invalidate iterator
```

### Iterator Invalidation Rule (VERY IMPORTANT)

* `push_back` → invalidates iterators if reallocation occurs
* `erase` → invalidates iterators after erased position

## When to Use vector

✔ Random access needed
✔ Stack-like usage
✔ Cache-friendly loops

## When NOT to Use

✖ Frequent middle insertions

---

# 2️⃣ map (Ordered Map – Red Black Tree)

## Internal Structure

Balanced BST (Red-Black Tree)

```
Keys always sorted
Height = O(log n)
```

## Access Patterns (INTERVIEW CRITICAL)

### Insert / Update

```cpp
mp[key] = value;      // insert OR update
mp.insert({k, v});   // insert only
```

### Find

```cpp
auto it = mp.find(key);
if(it != mp.end()) {
    cout << it->second;
}
```

### First & Last Element (VERY IMPORTANT)

```cpp
auto first = mp.begin();           // smallest key
auto last  = prev(mp.end());       // largest key
```

### Erase

```cpp
mp.erase(key);
mp.erase(it);
```

---

## lower_bound & upper_bound (FREQUENTLY ASKED)

### Definitions

* `lower_bound(x)` → first key ≥ x
* `upper_bound(x)` → first key > x

```cpp
auto lb = mp.lower_bound(10);
auto ub = mp.upper_bound(10);
```

### Use Case Example

> Count elements in range [L, R]

```cpp
int cnt = distance(mp.lower_bound(L), mp.upper_bound(R));
```

---

## Iterator Safety in map

✔ Insert does NOT invalidate iterators
✔ Erase invalidates only erased iterator

---

# 3️⃣ unordered_map (Hash Table)

## Internal Structure

* Hash buckets
* No ordering

## Complexity Reality (INTERVIEW TRAP)

| Case              | Time |
| ----------------- | ---- |
| Average           | O(1) |
| Worst (collision) | O(n) |

## Access

```cpp
mp[key];        // inserts if not exists
mp.at(key);    // throws exception if missing
```

## When NOT to Use

✖ When order matters
✖ When worst-case guarantees needed

---

# 4️⃣ set / multiset

## Key Differences

| Feature   | set    | multiset |
| --------- | ------ | -------- |
| Duplicate | ❌      | ✔        |
| Ordering  | Sorted | Sorted   |

## Access First / Last

```cpp
auto first = *st.begin();
auto last  = *prev(st.end());


auto result = st.insert(x);
auto it = result.first;

```
For std::set, the insert() function returns a pair:

pair<iterator, bool>

Meaning of the pair:

first → iterator pointing to the element in the set

second → true if insertion happened, false if element already existed

```
set<int> st = {2, 5, 8};

auto it = st.insert(5).first;
cout << *it; --> 5
cout << it.second --> true inserted successfully 5
```
---

# 5️⃣ priority_queue (Heap)

## Internal Structure

Binary Heap

```cpp
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;
```

## Access

```cpp
pq.top();   // max or min
pq.push();
pq.pop();
```

## Why Used in Dijkstra / Greedy

* Always extracts best candidate

---

# 6️⃣ queue & stack

## queue (FIFO)

```cpp
q.front();
q.back();
```

## stack (LIFO)

```cpp
st.top();
```

---

# 7️⃣ pair & tuple

```cpp
pair<int,int> p;
tuple<int,int,int> t;
```

Used heavily in graphs & heaps.

---

# 8️⃣ Iterators vs Pointers (VERY IMPORTANT)

| Aspect         | Iterator | Pointer |
| -------------- | -------- | ------- |
| Abstraction    | High     | Low     |
| Safety         | Safer    | Risky   |
| STL compatible | ✔        | ❌       |

```cpp
vector<int> v;
auto it = v.begin();
int* p = &v[0];
```

---

# 9️⃣ Common Interview Mistakes

❌ Using `mp.end()` directly
❌ Dereferencing invalid iterator
❌ Assuming unordered_map always O(1)
❌ Forgetting iterator invalidation

---

# 🔄 STL Decision Table (GOLD)

| Problem Need       | Best STL       |
| ------------------ | -------------- |
| Frequency          | unordered_map  |
| Sorted keys        | map            |
| Max/Min repeatedly | priority_queue |
| BFS                | queue          |
| DFS                | stack          |
| Random access      | vector         |

---

# 🌍 Real-World Usage

* Backend caches
* Search engines
* Databases
* OS schedulers
* Graph algorithms

---

# 💬 Interview Q&A

### Q1: How to get last element of map?

`prev(mp.end())`

### Q2: Why unordered_map can be slow?

Hash collision → O(n)

### Q3: lower_bound vs binary_search?

One returns iterator, other boolean.

### Q4: vector vs deque?

vector contiguous, deque segmented.

---

# 🎯 Final Takeaway

STL mastery is not about remembering functions — it’s about **choosing the correct container and accessing it safely and optimally during problem solving**.

This document is designed to be used **during live coding interviews**.

---

Repository complete.
