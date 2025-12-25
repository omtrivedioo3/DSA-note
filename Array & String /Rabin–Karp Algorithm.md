# Rabin–Karp Algorithm – Rolling Hash Based String Matching

## 📌 Repository: `rabin-karp-string-matching`

This repository provides a **deep, interview-grade explanation of the Rabin–Karp Algorithm**, a classic **string matching algorithm** based on **rolling hash**.

Rabin–Karp is frequently asked in **SDE interviews** to test:

* Hashing fundamentals
* Sliding window technique
* Collision handling understanding

This README is structured exactly like a **professional GitHub repository**.

---

# 📘 Problem Statement

Given:

* A **text string** `T`
* A **pattern string** `P`

Find **all starting indices** in `T` where `P` occurs.

Example:

```
Text    = "abedabcabc"
Pattern = "abc"
Output  = [4, 7]
```

---

# 🧠 Core Idea (INTERVIEW MUST-KNOW)

> Instead of comparing characters repeatedly, **compare hash values of substrings**.

Rabin–Karp uses:

* **Hashing** to convert strings to numbers
* **Rolling hash** to update hash in O(1) time while sliding the window

---

# 🔑 Rolling Hash Concept

For a string `s[0…k-1]`:

```
Hash(s) = s[0]*p^(k-1) + s[1]*p^(k-2) + ... + s[k-1]
```

Where:

* `p` = base (usually 31 or 101)
* All operations are done modulo a large prime

---

# 📊 Step-by-Step Visualization

Text = `abedabcabc`
Pattern = `abc`

Window size = 3

```
Window  Text     Hash Compare
------  -------  ------------
[0..2]  abe      ❌
[1..3]  bed      ❌
[2..4]  eda      ❌
[3..5]  dab      ❌
[4..6]  abc      ✔ MATCH
[5..7]  bca      ❌
[6..8]  cab      ❌
[7..9]  abc      ✔ MATCH
```

Hash matches → verify characters to avoid collision.

---

# 🔁 Rolling Hash Update Formula

When sliding window by one position:

```
newHash = (oldHash - leftChar * power) * p + rightChar
```

This update happens in **O(1)** time.

---

# 📘 Complete C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the starting index of all occurrences of pattern in text
    vector<int> search(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        
        // Primes for Rabin karp algorithm
        int p = 7, mod = 101;
        
        // To store the hash values of pattern and susbtring of text
        int hashPat = 0, hashText = 0;
        
        int pRight = 1, pLeft = 1;
        
        // Computing the initial hash values
        for(int i=0; i < n; i++) {
            hashPat += ((pat[i]-'a'+1) * pRight) % mod;
            hashText += ((txt[i]-'a'+1) * pRight) % mod;
            pRight = (pRight * p) % mod;
        }
        
        // List to store the result
        vector<int> ans;
        
        // Traverse the text string
        for(int i=0; i <= m-n; i++) {
            
            // If the hash value matches
            if(hashPat == hashText) {
                // Add the index of the result if the substring matches
                if(txt.substr(i, n) == pat) ans.push_back(i);
            }
            
            // Updating the hash values
            hashText = (hashText - ((txt[i] - 'a'+1) * pLeft) % mod + mod) % mod;
            hashText = (hashText + ((txt[i+n] - 'a'+1) * pRight) % mod) % mod;
            hashPat = (hashPat * p) % mod;
            
            // Updating the prime multiples
            pLeft = (pLeft * p) % mod;
            pRight = (pRight * p) % mod;
        }
        
        return ans; // Return the stored result
    } 
};

int main(){
    string txt = "ababcabcababc";
    string pat = "abc";
    
    // Creating an instance of Solution class
    Solution sol; 
    
    /* Function call to find the starting index
    of all occurrences of pattern in text */
    vector<int> ans = sol.search(pat, txt);
    
    // Output
    cout << "The starting indices of all occureneces of "
         << pat << " in " << txt << " are: ";
    for(auto it : ans) cout << it << " ";
    
    return 0;
}
```

---

# ⏱ Time & Space Complexity

## Time Complexity

| Case              | Complexity |
| ----------------- | ---------- |
| Best / Average    | O(n + m)   |
| Worst (collision) | O(n × m)   |

## Space Complexity

```
O(1) (excluding output)
```

---

# 🎯 When to Use Rabin–Karp

✔ Multiple pattern searches
✔ Substring search problems
✔ Plagiarism detection
✔ Rolling window hash problems

---

# 🛑 When NOT to Use Rabin–Karp

✖ Single pattern search (KMP preferred)
✖ High collision risk without double hashing
✖ Cryptographic hashing needs

---

# 🔄 Comparison with Other String Matching Algorithms

| Algorithm      | Time       | Space | Handles Multiple Patterns |
| -------------- | ---------- | ----- | ------------------------- |
| Naive          | O(n×m)     | O(1)  | ❌                         |
| KMP            | O(n+m)     | O(m)  | ❌                         |
| **Rabin–Karp** | O(n+m) avg | O(1)  | ✔                         |
| Boyer–Moore    | O(n/m) avg | O(m)  | ❌                         |

---

# 🌍 Real-World Applications

* Plagiarism detection systems
* Search engines
* Malware signature detection
* Data deduplication
* DNA sequence matching

---

# 💬 Interview-Ready Q&A

### Q1: Why Rabin–Karp is faster than naive?

Because hash comparison avoids repeated character checks.

### Q2: What is hash collision?

Different strings producing same hash value.

### Q3: How do we handle collisions?

Verify characters or use double hashing.

### Q4: Why rolling hash is O(1)?

Previous hash is reused instead of recomputing.

### Q5: Rabin–Karp vs KMP?

Rabin–Karp is better for multiple patterns.

---

# 🎯 Final Takeaway

> **Rabin–Karp trades guaranteed worst-case time for simplicity and average-case efficiency using rolling hash.**

Understanding hashing and collision handling is key to mastering this algorithm.

---

Repository complete.
