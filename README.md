# 📘 DSA-note  
A complete and structured guide covering **Data Structures**, **Algorithms**, **Patterns**, **Time & Space complexities**, and **use-cases** — perfect for interview preparation and competitive programming.

---

# 📂 Contents
- [Introduction](#introduction)
- [Data Structures](#data-structures)
- [Algorithmic Patterns](#algorithmic-patterns)
- [Time & Space Complexity Table](#time--space-complexity-table)
- [When to Use Which Data Structure](#when-to-use-which-data-structure)
- [Mathematical & Utility Concepts](#mathematical--utility-concepts)
- [Cheat Sheets](#cheat-sheets)
- [Learning Path](#learning-path)

---

# 🧠 Introduction
This repository contains well-structured notes for DSA, covering:

- Essential data structures  
- Core algorithms  
- Reusable patterns  
- Detailed complexities  
- When and why to use each structure  
- Templates for coding interviews  

Use this as a **master reference** while preparing for FAANG, product-based companies, and competitive programming.

---

# 🌳 Data Structures

Each section includes:  
✔ Description  
✔ Operations  
✔ Time complexities  
✔ Use-cases  

---

## **1. Array**
| Operation | Time |
|----------|------|
| Access   | O(1) |
| Insert at end | O(1) amortized |
| Delete | O(n) |
| Search | O(n) |

➤ Used when: random access needed, iteration-heavy problems.

---

## **2. Linked List**
| Operation | Time |
|----------|------|
| Insert/Delete at head | O(1) |
| Search | O(n) |

➤ Use when frequent insert/delete operations exist.

---

## **3. Stack**
| Operation | Time |
|----------|------|
| Push/Pop | O(1) |
| Top | O(1) |

➤ Used for: DFS, expression evaluation, parentheses matching, monotonic structures.

---

## **4. Queue**
| Operation | Time |
|----------|------|
| Enqueue/Dequeue | O(1) |

➤ Used for BFS, scheduling, streaming data.

---

## **5. HashMap / HashSet**
| Operation | Avg Time |
|-----------|----------|
| Insert/Delete/Search | O(1) |

➤ Used for constant-time lookup, frequency maps, caching.

---

## **6. Heap (Priority Queue)**
| Operation | Time |
|----------|------|
| Insert | O(log n) |
| Extract-min/max | O(log n) |

➤ Used for Dijkstra, scheduling, top-k elements, median streams.

---

## **7. Tree**
Basic traversals:
- Preorder  
- Inorder  
- Postorder  
- Level order  

Time: **O(n)**  
Space: **O(h)**

---

## **8. Binary Search Tree (BST)**
| Operation | Avg | Worst |
|-----------|------|---------|
| Insert/Delete/Search | O(log n) | O(n) |

➤ Use when ordered data + logarithmic operations needed.

---

## **9. Trie**
| Operation | Time |
|-----------|------|
| Insert | O(key_length) |
| Search | O(key_length) |

➤ Use for predictive search, autocomplete, string problems.

---

## **10. Graphs**
Representations:
- Adj List → O(V + E)  
- Adj Matrix → O(V²)

Use BFS/DFS for traversal.

---

## **11. Union-Find (Disjoint Set Union)**
| Operation | Time |
|----------|------|
| Find | α(n) ≈ O(1) |
| Union | α(n) ≈ O(1) |

➤ Use for connected components, MST (Kruskal), grouping problems.

---

## **12. Segment Tree**
| Operation | Time | Space |
|----------|------|--------|
| Query | O(log n) |
| Update | O(log n) |
| Build | O(n) |
| Space | O(4n) |

➤ Use for range queries (sum, min, max, gcd) and range updates (lazy propagation).

---

## **13. Fenwick Tree (Binary Indexed Tree)**
| Operation | Time | Space |
|----------|------|--------|
| Update | O(log n) |
| Prefix Sum | O(log n) |
| Space | O(n) |

➤ Use when only **point update + range sum** is needed.

---

## **14. Sparse Table**
| Operation | Time |
|----------|------|
| Build | O(n log n) |
| Query | O(1) |

➤ Best for **static array** + idempotent operations (min, max, gcd).

---

# 🧩 Algorithmic Patterns

## **1. Sliding Window**
Used for:
- Subarray problems
- Longest substring
- Frequency windows  
Time: **O(n)**

---

## **2. Two Pointers**
Used when searching pairs, sorted arrays, or partitions.
Time: **O(n)**

---

## **3. Fast & Slow Pointers**
Used for:
- Cycle detection
- Middle of linked list  
Time: **O(n)**

---

## **4. Binary Search Patterns**
Used when:
- Array is sorted  
- Answer is monotonic  
Time: **O(log n)**

---

## **5. Monotonic Stack**
Used for:
- Next greater element  
- Histogram problems  
- Stock span  

---

## **6. DP Patterns**
- 0/1 Knapsack  
- Unbounded Knapsack  
- LIS  
- LCS  
- Kadane’s (max subarray sum)  
- Matrix DP (grid-based)  

---

## **7. Graph Patterns**
- BFS → shortest path in unweighted graph  
- DFS → connectivity, components  
- Dijkstra → shortest path weighted  
- Floyd–Warshall → all-pairs shortest path  
- Topological Sort → DAG ordering  

---

# 🧮 Time & Space Complexity Table

| Structure/Algorithm | Build | Query | Update | Space |
|---------------------|--------|--------|---------|--------|
| Array | O(1) | O(1) | O(1) | O(n) |
| HashMap | — | O(1) | O(1) | O(n) |
| Heap | O(n) | O(log n) | O(log n) | O(n) |
| Stack/Queue | O(1) | O(1) | O(1) | O(n) |
| BST | O(n log n) | O(log n)* | O(log n)* | O(n) |
| Segment Tree | O(n) | O(log n) | O(log n) | O(n) |
| Fenwick Tree | O(n) | O(log n) | O(log n) | O(n) |
| Sparse Table | O(n log n) | O(1) | — | O(n log n) |

---

# ❓ When to Use Which Data Structure

## ✔ Segment Tree  
Use when:
- Need range queries  
- Need range updates  
- Need min/max/gcd/sum  

## ✔ Fenwick Tree  
Use when:
- Only sum queries  
- Point updates  
- Need faster & simpler structure  

## ✔ Trie  
Use when:
- Prefix search  
- Dictionary  
- Autocomplete  

## ✔ Union-Find  
Use when:
- Dynamic connectivity  
- Group merging  
- Cycle detection  

## ✔ Heap  
Use when:
- Need smallest/largest quickly  
- Dijkstra  
- K largest elements  

---

# 🧰 Mathematical & Utility Concepts

- Prefix Sum  
- Difference Array  
- Modulo Arithmetic  
- Fast Power (Binary exponentiation)  
- Sieve of Eratosthenes  
- Bit Manipulation (LSB, MSB, masks)  

---

# 📘 Cheat Sheets

| Topic | Link |
|-------|------|
| Sliding Window | Pattern summary |
| Binary Search | Template & problems |
| DP | State transition cheat sheet |
| Graph Theory | BFS/DFS/Dijkstra templates |
| Trees | Traversals, LCA |

(You can add links as you expand your repo.)

---

# 🛣 Learning Path

1. Arrays, Strings  
2. Hashing  
3. Stack, Queue  
4. Pointers & Sliding Window  
5. Trees + BST  
6. Recursion + Backtracking  
7. DP (start with 1D → 2D → Knapsack → LCS → Trees DP)  
8. Graph Algorithms  
9. Segment Tree, Fenwick Tree  
10. Hard problems + patterns  

---

# 🎉 Contribute

Feel free to add:
- Example problems  
- Notes  
- Visual diagrams  
- Templates  
- Competitive programming tricks  

---

# ⭐ Final Note

This repository is designed to become a **single-stop reference for DSA** — covering core concepts, patterns, and complexities that every software engineer or competitive programmer should know.

Happy Coding! 🚀  
