# Trie (Prefix Tree) 
It covers:

* Core concept & intuition
* Proper tree diagrams
* Detailed C++ implementation
* Advanced Trie operations
* Time & space complexity
* When to use / not use
* Comparisons with other data structures
* Real-world applications
* Interview-ready notes & Q&A

---

# 📘 Introduction

A **Trie (Prefix Tree)** is a tree-based data structure used to efficiently store and retrieve strings, especially when **prefix-based searching** is required.

Instead of storing whole strings at nodes, a Trie stores **characters level by level**, where each path from root to a node represents a prefix.

---

# 🧠 Core Idea (INTUITION)

* Each node represents **one character**
* Root represents **empty string**
* Each edge represents adding one character
* Complete word ends when `isEnd = true`

Searching, inserting, and prefix matching are all **proportional to string length**, not number of words.

---

# 🌳 Trie Structure – Text-Based Diagram

Example words: `cat`, `car`, `dog`

```
(root)
  |
  c
  |
  a
 / \
t   r
|   |
*   *

(root)
  |
  d
  |
  o
  |
  g
  |
  *

* => end of word
```

---

# 🧩 Trie Node Design

Each Trie node contains:

* Array / map of child pointers
* Boolean flag `isEnd`

```cpp
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for(int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};
```

---

# ⚙️ Supported Operations

1. Insert a word
2. Search a word
3. StartsWith (prefix search)
4. Count words with prefix
5. Delete a word (advanced)

---

# 📘 Complete C++ Implementation

```cpp
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert word
    void insert(string word) {
        TrieNode* node = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    // Search complete word
    bool search(string word) {
        TrieNode* node = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    // Prefix check
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for(char ch : prefix) {
            int idx = ch - 'a';
            if(!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
};
```

---

# ⏱ Time & Space Complexity

## Time Complexity

| Operation | Time |
| --------- | ---- |
| Insert    | O(L) |
| Search    | O(L) |
| Prefix    | O(L) |

L = length of word

## Space Complexity

```
O(N * L * ALPHABET)
```

Where N = number of words

---

# 🎯 When to Use Trie

✔ Prefix-based search
✔ Dictionary / autocomplete
✔ Spell checker
✔ Word games
✔ Fast string queries

---

# 🛑 When NOT to Use Trie

✖ When memory is constrained
✖ When only full-string lookup needed (use hash set)
✖ When alphabet is very large

---

# 🔄 Comparison with Other Data Structures

| Data Structure | Search   | Prefix Search | Memory |
| -------------- | -------- | ------------- | ------ |
| Trie           | O(L)     | O(L)          | High   |
| Hash Set       | O(1) avg | ❌             | Low    |
| BST            | O(log N) | ❌             | Medium |

---

# 🌍 Real-World Applications

* Autocomplete (Google Search)
* Spell checkers
* Dictionary apps
* IP routing (Longest Prefix Match)
* DNA sequence analysis

---

# 💬 Interview-Ready Q&A

### Q1: Why is Trie faster than hash table for prefix search?

Because Trie stores prefixes explicitly.

### Q2: Why is Trie memory expensive?

Each node stores multiple child pointers.

### Q3: Can Trie handle uppercase or digits?

Yes, by increasing alphabet size.

### Q4: Difference between Trie and BST?

Trie is character-based; BST is key-based.

### Q5: Can Trie be optimized?

Yes, using compressed Trie (Radix Tree).

---

# 🎯 Final Takeaway

> **Trie is the go-to data structure when prefix-based searching dominates the problem.**

Understanding Trie structure and operations deeply is a **must-have skill for SDE interviews**.

---

Repository complete.
