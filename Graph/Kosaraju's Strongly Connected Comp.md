# Kosaraju’s Algorithm – Strongly Connected Components (SCC)

## 📌 Repository: `kosaraju-strongly-connected-components`

This repository provides a **deep, interview-grade explanation of Kosaraju’s Algorithm** for finding **Strongly Connected Components (SCCs)** in a **directed graph**.

It explains **every design decision**, especially:

* **Why we store nodes in a stack (finishing order)**
* **Why graph reversal is required**
* **Why DFS order matters**

This document is structured exactly like a **GitHub README.md** and is meant for **SDE interviews in top MNCs**.

---

# 📘 Introduction

In a **directed graph**, a **Strongly Connected Component (SCC)** is a group of vertices such that:

```
For every u and v in SCC:
  u → v AND v → u (paths exist in both directions)
```

Kosaraju’s Algorithm efficiently finds **all SCCs in linear time**.

---

# 🧠 High-Level Intuition (VERY IMPORTANT)

Kosaraju’s Algorithm works because:

1. **DFS finishing times capture dependency order**
2. **Reversing edges preserves SCC structure**
3. **Processing nodes in decreasing finish time isolates SCCs**

The algorithm cleverly combines these ideas.

---

# 🧩 Algorithm Overview (3 Steps)

### Step 1️⃣: DFS and push nodes to stack (by finish time)

### Step 2️⃣: Reverse the graph

### Step 3️⃣: DFS in stack order on reversed graph

Each DFS in Step 3 gives **one SCC**.

---

# ❓ Why Do We Use a Stack? (INTERVIEW MUST-KNOW)

### Key Insight

> Nodes with **no outgoing edges to other SCCs** finish **last** in DFS.

Thus:

* Stack stores nodes in **decreasing finishing time**
* Top of stack = **good SCC starting point**

If we don’t follow this order, SCCs can merge incorrectly.

---

# 📊 Text-Based Diagram (Core Idea)

Original Graph:

```
1 → 2 → 3
↑   ↓   ↓
└── 4 ←─5
```

SCCs:

```
{1,2,4} , {3,5}
```

Finish order stack (top first):

```
[ 1, 2, 4, 3, 5 ]
```

---

# 🔁 Step 2: Reverse the Graph (WHY?)

Reversing edges ensures:

* We **cannot leave an SCC** once we start DFS
* We only collect nodes that can reach each other

Without reversing:
❌ DFS may spread across multiple SCCs

---

# 🧮 Detailed Algorithm Steps

### Step 1: DFS + Stack

* Run DFS on original graph
* Push node to stack **after all neighbors are visited**

### Step 2: Reverse Graph

* Reverse all edges

### Step 3: DFS Using Stack Order

* Pop node from stack
* If unvisited, DFS on reversed graph
* All visited nodes form **one SCC**

---

# 📘 Complete C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    /* Function to perform DFS for storing the 
    nodes in stack based on their finishing time */
    void dfs(int node, vector<int> &vis, vector<int> adj[],
             stack<int> &st) {

        // Mark the node as visited
        vis[node] = 1;
        
        // Traverse all its neighbors
        for (auto it : adj[node]) {
            if (!vis[it]) {
                // Recursively perform DFS is not visited already
                dfs(it, vis, adj, st);
            }
        }
        
        // Push the node in stack
        st.push(node);
    }
    
    /* Helper function to perform DFS for finding
    number of Strongly connected components */
    void helperDFS(int node, vector<int> &vis, 
                   vector<int> adjT[]) {
                       
        // Mark the node as visited
        vis[node] = 1;
        
        // Traverse all its neighbors
        for (auto it : adjT[node]) {
            if (!vis[it]) {
                // Recursively perform DFS if not already visited
                helperDFS(it, vis, adjT);
            }
        }
    }
public:

    /* Funtion call to find the number of 
    strongly connected components */
    int kosaraju(int V, vector<int> adj[]) {
        
        // Visited array
        vector<int> vis(V, 0);
        
        // Stack data structure 
        stack<int> st;
        
        /* Perform initial DFS to store the nodes 
        in stack based on their finishing time */
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }
        
        // To store the revered graph
        vector<int> adjT[V];
        
        /* Reverse all the edges of original 
        graph to the reversed graph */
        for (int i = 0; i < V; i++) {
            
            // Mark the node as unvisited
            vis[i] = 0;
            
            // Add the reversed edge
            for (auto it : adj[i]) {
                adjT[it].push_back(i);
            }
        }
        
        /* To store the count of strongly 
        connected components */
        int count = 0;
        
        /* Start DFS call from every unvisited 
        node based on their finishing time */
        while (!st.empty()) {
            // Get the node
            int node = st.top();
            st.pop();
            
            // If not visited already
            if (!vis[node]) {
                count += 1;
                helperDFS(node, vis, adjT);
            }
        }
        
        // Return the result
        return count;
    }
};

int main() {

    int n = 5;
    int edges[5][2] = {
        {1, 0}, {0, 2},
        {2, 1}, {0, 3},
        {3, 4}
    };
    
    // Creating the adjacency list
    vector<int> adj[n];
    for (int i = 0; i < n; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }
    
    // Creating an instance of Solution class
    Solution obj;
    
    /* Funtion call to find the number of 
    strongly connected components */
    int ans = obj.kosaraju(n, adj);
    
    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}
```

---

# ⏱ Time & Space Complexity

## Time Complexity

```
O(V + E)
```

* DFS 1 → O(V + E)
* Graph reversal → O(E)
* DFS 2 → O(V + E)

## Space Complexity

```
O(V + E)
```

* Adjacency list
* Stack
* Visited arrays

---

# 🎯 When to Use Kosaraju’s Algorithm

✔ Need to find SCCs
✔ Directed graphs
✔ Graph condensation problems
✔ Dependency analysis

---

# 🛑 When NOT to Use

✖ Undirected graphs
✖ Only need to detect cycle
✖ When single-pass SCC needed (use Tarjan)

---

# 🔄 Comparison with Other SCC Algorithms

| Algorithm | Passes | Extra Graph | Stack | Complexity |
| --------- | ------ | ----------- | ----- | ---------- |
| Kosaraju  | 2 DFS  | Yes         | Yes   | O(V+E)     |
| Tarjan    | 1 DFS  | No          | Yes   | O(V+E)     |
| Gabow     | 1 DFS  | No          | Yes   | O(V+E)     |

---

# 🌍 Real-World Applications

* Deadlock detection
* Social network clusters
* Compiler optimization (control flow)
* Package dependency resolution
* Web graph analysis

---

# 💬 Interview-Ready Q&A

### Q1: Why do we push nodes after DFS finishes?

To record finishing time order.

### Q2: Why reverse the graph?

To isolate SCCs during DFS.

### Q3: Why not use BFS?

DFS finishing times are required.

### Q4: Kosaraju vs Tarjan?

Tarjan uses one DFS, Kosaraju uses two.

### Q5: Can SCC exist in undirected graph?

Every connected component is an SCC.

---

# 🎯 Final Takeaway

> **Kosaraju’s Algorithm works because DFS finishing times reveal SCC dependency order, and reversing the graph prevents SCC leakage.**

If you can explain **why the stack is used**, you fully understand the algorithm.

---

Repository complete.
