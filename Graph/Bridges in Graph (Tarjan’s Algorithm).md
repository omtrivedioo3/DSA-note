# Bridges in Graph (Tarjan’s Algorithm) 
---

# 📘 Introduction

A **Bridge** (also called a **critical connection**) in a graph is an edge whose removal **increases the number of connected components** in the graph.

In simple terms:

> If removing an edge disconnects the graph, that edge is a **bridge**.

This problem is commonly solved using **Tarjan’s Algorithm** based on **DFS + discovery time + low-link values**.

---

# 🧠 Core Idea

During DFS traversal of a graph:

* Each node is assigned a **discovery time (tin)**
* Each node also maintains a **low value (low)** → the earliest discovered node reachable from its subtree

An edge `(u, v)` is a **bridge** if:

```
low[v] > tin[u]
```

Meaning: subtree rooted at `v` cannot reach any ancestor of `u`.

---

# 📊 ASCII Diagram – Bridge Intuition

Graph:

```
0 —— 1 —— 2
      |
      3
```

Bridges:

```
(1 — 2), (1 — 3)
```

Removing either edge disconnects the graph.

---

# 🧮 Algorithm (Tarjan’s – DFS Based)

### Steps:

1. Initialize discovery time and low arrays
2. Run DFS from any unvisited node
3. Update low values using back edges
4. Identify bridges using condition `low[v] > tin[u]`

---

# 📘 Full C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
   private:
    int timer = 0;
    void fun(int node, int parent, vector<int> &vis, vector<int> &tin,
             vector<int> &low, vector<int> adj[], vector<vector<int>> &ans) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        for (auto it : adj[node]) {
            if (it == parent) continue;
            if (vis[it] == 0) {
                fun(it, node, vis, tin, low, adj, ans);
                low[node] = min(low[node], low[it]);
                if (tin[node] < low[it]) {
                    ans.push_back({node, it});
                }
            } else {
                low[node] = min(low[node], low[it]);
            }
        }
    }

   public:
    vector<vector<int>> criticalConnections(int V, vector<vector<int>> &E) {
        vector<int> adj[V];
        for (int i = 0; i < E.size(); i++) {
            adj[E[i][0]].push_back(E[i][1]);
            adj[E[i][1]].push_back(E[i][0]);
        }
        vector<int> vis(V, 0), tin(V, 0), low(V, 0);
        vector<vector<int>> ans;
        fun(0, -1, vis, tin, low, adj, ans);
        return ans;
    }
};

```

---

# 🧩 Use Cases of Bridges in Graph

Bridges are preferred when:

✔ You need to find **critical connections**
✔ Network reliability analysis
✔ Identifying single points of failure
✔ Connectivity analysis

Common problems:

* LeetCode: Critical Connections in a Network
* GFG: Bridges in Graph
* Network design problems

---

# ⏱ Time & Space Complexity

### Time Complexity

```
O(N + M)
```

Where:

* N = number of nodes
* M = number of edges

### Space Complexity

```
O(N + M)
```

For adjacency list + recursion stack.

---

# 🎯 When to Use This Algorithm

Use bridge-finding algorithm when:

* Graph is **undirected**
* Need to identify critical edges
* Graph size is large (linear-time solution needed)

---

# 🛑 When NOT to Use This Algorithm

Do NOT use when:

* Graph is **directed** (bridge definition differs)
* You need articulation points instead
* Graph is very small (simpler checks suffice)

---

# 🔄 Comparison with Other Graph Algorithms

| Algorithm           | Purpose                           |
| ------------------- | --------------------------------- |
| Bridges (Tarjan)    | Critical edges                    |
| Articulation Points | Critical nodes                    |
| DFS/BFS             | Traversal only                    |
| DSU                 | Connectivity (not critical edges) |

---

# 🌍 Real-World Applications

* Internet backbone reliability
* Power grid failure analysis
* Road network vulnerability detection
* Social network critical connections
* Distributed systems fault tolerance

---

# 💬 Interview Questions & Answers

### Q1: What is a bridge in a graph?

An edge whose removal increases the number of connected components.

### Q2: Why DFS is used?

DFS naturally explores subtrees and back edges, enabling low-link analysis.

### Q3: Condition for a bridge?

`low[v] > tin[u]`

### Q4: Can bridges exist in directed graphs?

Definition differs; Tarjan’s bridge algorithm is for undirected graphs.

### Q5: Time complexity?

O(N + M)

---

# 🎯 Final Summary

Bridges identify **critical connections** in an undirected graph. Using Tarjan’s DFS-based algorithm, bridges can be found in linear time, making it essential for network reliability, system design, and interview problems.

---
