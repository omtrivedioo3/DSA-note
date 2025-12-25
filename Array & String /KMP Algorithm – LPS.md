# KMP Algorithm (Knuth–Morris–Pratt) – LPS Array Deep Dive

## 📌 Repository: `kmp-string-matching`

This repository provides a **complete, interview-grade explanation of the KMP Algorithm**, with a **deep focus on the LPS (Longest Prefix Suffix) array**, which is the heart of KMP.

KMP is one of the **most frequently asked string algorithms** in SDE interviews because it tests:

* Pattern preprocessing intuition
* Failure-function logic
* Ability to eliminate redundant comparisons

This README is written exactly like a **professional GitHub repository** for **top MNC SDE interviews**.

---

# 📘 Problem Statement

Given:

* A **text string** `T`
* A **pattern string** `P`

Find all indices where `P` occurs in `T`.

Example:

```
Text    = "ababcababcabc"
Pattern = "ababc"
Output  = [0, 5]
```

---

# 🧠 Core Idea (INTERVIEW MUST-KNOW)

> **When a mismatch occurs, do not restart matching from the beginning of the pattern.**

Instead:

* Use information from the pattern itself
* Jump the pattern using the **LPS array**

This avoids unnecessary comparisons and guarantees **linear time**.

---

# 🔑 What is LPS Array?

`LPS[i]` = length of the **longest proper prefix** of `pattern[0..i]` which is also a **suffix**.

* Proper prefix → prefix ≠ whole string

Example:

```
Pattern = "abab"
Index   =  0 1 2 3
LPS     = [0 0 1 2]
```

---

# 📊 Visualizing LPS Construction

Pattern: `ababaca`

```
i:        0 1 2 3 4 5 6
pattern:  a b a b a c a
lps:      0 0 1 2 3 0 1
```

Explanation:

* At index 4 → `ababa` → prefix `aba` = suffix `aba`

---

# 🧮 How LPS Helps Avoid Re-comparison

Text:    `ababcababcabc`
Pattern: `ababc`

```
Match till ababc
Mismatch here
Jump pattern using LPS
No need to re-check prefix
```

---

# 1️⃣ Step 1: Build LPS Array

## Algorithm

* Use two pointers: `len` and `i`
* `len` tracks length of previous LPS

---

## C++ Code – LPS Construction

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Compute the Longest prefix suffix array for the combined string
    vector<int> computeLPS(string s) {
        int n = s.size(); // size of string
        
        // To store the longest prefix suffix
        vector<int> LPS(n, 0);
        
        int i = 1, j = 0;
        
        // Iterate on the string
        while(i < n) {
            // If the character matches
            if(s[i] == s[j]) {
                LPS[i] = j+1;
                i++, j++;
            }
            
            // Otherwise
            else {
                // Trace back j pointer till it does not match
                while(j > 0 && s[i] != s[j]) {
                    j = LPS[j-1];
                }
                
                // If a match is found
                if(s[i] == s[j]) {
                    LPS[i] = j+1;
                    j++;
                }
                i += 1;
            }
        }
        
        return LPS; // Return the computed LPS array
    }
    
public:
    // Function to find all indices of pattern in text
    vector<int> search(string pattern, string text)   {
        string s = pattern + '$' + text; // Combined string
        
        // Function call to find the Z array for the combined string
        vector<int> LPS = computeLPS(s);
        
        // Length of pattern and text
        int n = text.size(), m = pattern.size();
        
        // To store the result
        vector<int> ans;
        
        // Iterate on the combined string after the delimiter
        for(int i = m+1; i < s.size(); i++) {
            if(LPS[i] == m) ans.push_back(i - 2*m);
        }
        
        return ans;
    }
};

int main() {
    string text = "xyzabxyzabxyz";
    string pattern = "xyz";
    
    // Creating an instance of the solution class
    Solution sol;
    
    // Function call to find all indices of pattern in text
    vector<int> ans = sol.search(pattern, text);
    
    for(auto ind : ans) cout << ind << " ";
    return 0;
}
```

# ⏱ Time & Space Complexity

## Time Complexity

```
O(n + m)
```

* LPS construction → O(m)
* Pattern search → O(n)

## Space Complexity

```
O(m)
```

* LPS array

---

# 🎯 When to Use KMP

✔ Single pattern search
✔ Worst-case linear guarantee needed
✔ Competitive programming

---

# 🛑 When NOT to Use KMP

✖ Multiple pattern search (use Aho–Corasick)
✖ When hashing-based solutions are simpler

---

# 🔄 Comparison with Other String Algorithms

| Algorithm   | Time       | Space | Worst Case |
| ----------- | ---------- | ----- | ---------- |
| Naive       | O(n×m)     | O(1)  | ❌          |
| Rabin–Karp  | O(n+m) avg | O(1)  | ❌          |
| **KMP**     | **O(n+m)** | O(m)  | ✔          |
| Z-Algorithm | O(n+m)     | O(n)  | ✔          |

---

# 🌍 Real-World Applications

* Text editors (find/replace)
* Search engines
* DNA pattern matching
* Log analysis
* Intrusion detection systems

---

# 💬 Interview-Ready Q&A

### Q1: Why is KMP O(n+m)?

Each character is processed at most once.

### Q2: Why do we use LPS array?

To avoid rechecking matched prefix.

### Q3: KMP vs Rabin–Karp?

KMP guarantees worst-case linear time.

### Q4: Can KMP find overlapping patterns?

Yes.

### Q5: What is hardest part of KMP?

Understanding and building LPS.

---

# 🎯 Final Takeaway

> **KMP achieves optimal string matching by preprocessing the pattern and eliminating redundant comparisons using the LPS array.**

If you truly understand LPS, you truly understand KMP.

---

Repository complete.
