# Disjoint Set Union (DSU) / Union-Find

A complete, interview-ready guide to **Disjoint Set Union (DSU)**, also known as **Union-Find**. This repository-style README explains the concept, implementation, use cases, comparisons, and real-world applications—tailored for **SDE interviews at top MNCs**.

---

## 📌 What is Disjoint Set Union?

Disjoint Set Union (DSU) is a data structure that efficiently maintains a collection of **disjoint (non-overlapping) sets** and supports two primary operations:

* **Find(x)** → Determine which set element `x` belongs to
* **Union(x, y)** → Merge the sets containing `x` and `y`

DSU is optimized using:

* **Path Compression** (during find)
* **Union by Rank / Size** (during union)

These optimizations make DSU extremely fast in practice.

---

## 🧠 Core Operations

1. **MakeSet(x)** – Initialize a set containing only `x`
2. **Find(x)** – Find the representative (ultimate parent) of `x`
3. **Union(x, y)** – Merge the sets of `x` and `y`

---

## 📊 Text-Based Diagram

### Initial State

```
1   2   3   4   5
|   |   |   |   |
1   2   3   4   5   (each element is its own parent)
```

### After Union(1, 2) and Union(3, 4)

```
1   3   5
|   |
2   4
```

### After Union(2, 3)

```
1
|
2
|
3
|
4      5
```

(With path compression, all nodes point directly to `1`)

---

## 🧩 Complete C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
private:
    // To store the rank of each node
    vector<int> rank;
    
    /* To store the size of components 
    that each node belongs to */
    vector<int> size;
    
    // To store the ultimate parent of each node
    vector<int> parent;
    
public:
    
    // Constructor
    DisjointSet(int n) {
        
        // Resize the arrays
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n+1, 1);
        // Initialise each node with its own value
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    /* Helper function to find ultimate
    parent along with path compression */
    int findUPar(int node) {
        // Base case
        if (node == parent[node])
            return node;
            
        // Backtracking step for path compression
        return parent[node] = findUPar(parent[node]);
    }
    
    /* Function to detemine if two nodes 
    are in the same component or not */
    bool find(int u, int v) {
        // Return true if both have same ultimate parent 
        return (findUPar(u) == findUPar(v));
    }
    
    /* Function to perform union of 
    two nodes based on ranks */
    void unionByRank(int u, int v) {
        
        // Get the ultimate parents of both nodes
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        // Return if nodes already belong to the same component
        if (ulp_u == ulp_v) return;
        
        /* Otherwise, join the node to the other 
        node having higher ranks among the two */
        if (rank[ulp_u] < rank[ulp_v]) {
            // Update the parent
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            // Update the parent
            parent[ulp_v] = ulp_u;
        }
        
        /* If both have same rank, join any node to the 
        other and increment the rank of the parent node */
        else {
            // Update the parent
            parent[ulp_v] = ulp_u;
            
            // Update the rank
            rank[ulp_u]++;
        }
    }
    
    /* Function to perform union of 
    two nodes based on ranks */
    void unionBySize(int u, int v) {
        
        // Get the ultimate parents of both nodes
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        // Return if nodes already belong to the same component
        if (ulp_u == ulp_v) return;
        
        /* Otherwise, join the node belonging to the smaller 
        component to the node belonging to bigger component */
        if (size[ulp_u] < size[ulp_v]) {
            // Update the parent
            parent[ulp_u] = ulp_v;
            
            // Update the size 
            size[ulp_v] += size[ulp_u];
        }
        else {
            // Update the parent
            parent[ulp_v] = ulp_u;
            
            // Update the size
            size[ulp_u] += size[ulp_v];
        }
    }
};


int main() {
    // Disjoint Data structure
    DisjointSet ds(7);
    ds.unionByRank(1, 2); // Adding edge between 1 and 2
    ds.unionByRank(2, 3); // Adding edge between 2 and 3
    ds.unionByRank(4, 5); // Adding edge between 4 and 5
    ds.unionByRank(6, 7); // Adding edge between 6 and 7
    ds.unionByRank(5, 6); // Adding edge between 5 and 6
    
    /* Checking if node 3 and node 7 
    are in the same component */
    if (ds.find(3, 7)) 
        cout << "They belong to the same components.\n";
    else 
        cout << "They do not belong to the same components.\n";
        
    ds.unionByRank(3, 7); // Adding edge between 3 and 7

    /* Checking again if node 3 and node 7 
    are in the same component */
    if (ds.find(3, 7)) 
        cout << "They belong to the same components.\n";
    else 
        cout << "They do not belong to the same components.\n";
    
    return 0;
}
```

---

## ⏱️ Time and Space Complexity

| Operation | Complexity |
| --------- | ---------- |
| MakeSet   | O(1)       |
| Find      | O(α(N))    |
| Union     | O(α(N))    |

Where **α(N)** is the inverse Ackermann function, which grows extremely slowly and is ≤ 4 for all practical inputs.

**Space Complexity:** O(N)

---

## ✅ When to Use DSU

* When you need to dynamically track **connected components**
* When performing **merge and query operations** repeatedly
* Graph problems where edges are added incrementally
* Problems requiring **cycle detection** in undirected graphs

---

## ❌ When NOT to Use DSU

* When you need to support **edge deletions** frequently
* When relationships are **directional** and dynamic
* When full graph traversal or path enumeration is required

---

## 🔍 Comparison with Similar Techniques

| Technique      | Best Use Case          | Difference                  |
| -------------- | ---------------------- | --------------------------- |
| DFS/BFS        | Static connectivity    | Slower for repeated queries |
| DSU            | Dynamic connectivity   | Very fast union/find        |
| Floyd–Warshall | All-pairs connectivity | O(N³), too slow             |
| Graph Coloring | Bipartite checks       | Different purpose           |

---

## 🌍 Real-World Applications

* Network connectivity (LANs, distributed systems)
* Social network friend groups
* Kruskal’s algorithm (Minimum Spanning Tree)
* Image processing (connected components)
* Dynamic island counting problems

---

## 💡 Common Interview Problems Using DSU

* Number of Connected Components
* Detect Cycle in Undirected Graph
* Kruskal’s Minimum Spanning Tree
* Accounts Merge (LeetCode)
* Number of Islands II

---

## 🧠 Interview-Ready Notes

* DSU works best with **path compression + union by rank/size**
* Always clarify if the graph is **directed or undirected**
* DSU does NOT support deletions efficiently
* Often combined with **sorting** (e.g., Kruskal)

---

## ❓ Interview Q&A

**Q1. Why is DSU almost O(1)?**
Because path compression flattens the tree and union by rank keeps it shallow.

**Q2. Can DSU detect cycles?**
Yes, in **undirected graphs**. If two nodes already share the same parent, adding an edge creates a cycle.

**Q3. Why not use DSU for directed graphs?**
DSU cannot model direction-based relationships.

**Q4. Rank vs Size — which is better?**
Both work similarly. Size is often easier to reason about.

---

## 📚 Summary

Disjoint Set Union is a **fundamental data structure** for connectivity problems. Mastering DSU is essential for SDE interviews, especially for graph-based problems in top product-based companies.

---

⭐ If this helped you, consider adding DSU to your **core DSA revision checklist**.
