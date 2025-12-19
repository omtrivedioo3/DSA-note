# Minimum Spanning Tree (MST) – Prim’s & Kruskal’s Algorithms

---

# 📘 Introduction to Minimum Spanning Tree (MST)

A **Minimum Spanning Tree** of a connected, undirected, weighted graph is a subset of edges such that:

* All vertices are connected
* No cycles are formed
* The total edge weight is **minimum possible**

If a graph has `N` vertices, an MST always has exactly `N - 1` edges.

---

# 🧠 Core Idea

MST focuses on **connecting all nodes at minimum cost**, not on shortest paths between nodes.

Two most important algorithms:

1. **Prim’s Algorithm** → grows MST node by node
2. **Kruskal’s Algorithm** → grows MST edge by edge

---

# 📊 ASCII Diagram – MST Example

```
Graph:
   1 --(4)-- 2
   | \       |
  (1) (3)   (2)
   |    \    |
   3 --(5)-- 4

MST:
   1 --(1)-- 3
    \        |
     (3)    (2)
       \    |
        2 -- 4
Total Weight = 1 + 3 + 2 = 6
```

---

# 🌱 Prim’s Algorithm

## Idea

* Start from any node
* Always pick the **minimum weight edge** connecting MST to a new node
* Uses **priority queue (min-heap)**

Prim’s is similar to Dijkstra but focuses on **edge weight**, not path cost.

---

## 📘 C++ Implementation – Prim’s Algorithm

```cpp
#include <bits/stdc++.h>
using namespace std;

int primMST(int V, vector<vector<int>> adj[]) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    vector<bool> inMST(V, false);
    pq.push({0, 0}); // {weight, node}

    int mstWeight = 0;

    while (!pq.empty()) {
        auto [wt, node] = pq.top(); pq.pop();
        if (inMST[node]) continue;

        inMST[node] = true;
        mstWeight += wt;

        for (auto &it : adj[node]) {
            int v = it[0];
            int w = it[1];
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    return mstWeight;
}
```

---

# 🔗 Kruskal’s Algorithm

## Idea

* Sort all edges by weight
* Pick the smallest edge that does NOT form a cycle
* Uses **Disjoint Set Union (DSU)**

---

## 📘 C++ Implementation – Kruskal’s Algorithm

```cpp
class DisjointSet {
    /* To store the ranks, parents and 
    sizes of different set of vertices */
    vector<int> rank, parent, size;
    
public:

    // Constructor
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    // Function to find ultimate parent
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    // Function to implement union by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

// Solution class
class Solution{
public:

    // Function to get the sum of weights of edges in MST
    int spanningTree(int V, vector<vector<int>> adj[]) {
        
        // To store the edges
        vector<pair<int, pair<int, int>>> edges;
        
        // Getting all edges from adjacency list
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int v = it[0]; // Node v
                int wt = it[1]; // edge weight
                int u = i; // Node u
                edges.push_back({wt, {u, v}});
            }
        }
        
        // Creating a disjoint set of V vertices
        DisjointSet ds(V);
        
        // Sorting the edges based on their weights
        sort(edges.begin(), edges.end());
        
        // To store the sum of edges in MST
        int sum = 0;
        
        // Iterate on the edges
        for (auto it : edges) {
            int wt = it.first; // edge weight
            int u = it.second.first; // First node
            int v = it.second.second; // Second node
            
            // Join the nodes if not in the same set 
            if (ds.findUPar(u) != ds.findUPar(v)) {
                
                // Update the sum of edges in MST
                sum += wt;
                
                // Unite the nodes 
                ds.unionBySize(u, v);
            }
        }
        
        // Return the computed sum
        return sum;
    }
};
```

---

# 🧩 Use Cases

✔ Network design
✔ Road and cable laying
✔ Clustering
✔ Image segmentation
✔ Cost optimization problems

---

# ⏱ Time & Space Complexity

| Algorithm | Time Complexity | Space Complexity |
| --------- | --------------- | ---------------- |
| Prim (PQ) | O(E log V)      | O(V + E)         |
| Kruskal   | O(E log E)      | O(V)             |

---

# 🎯 When to Use Prim’s Algorithm

Use Prim when:

* Graph is **dense**
* Adjacency list/matrix available
* You want to grow MST from a source

---

# 🎯 When to Use Kruskal’s Algorithm

Use Kruskal when:

* Graph is **sparse**
* Edge list is available
* DSU is already implemented

---

# 🛑 When NOT to Use MST Algorithms

Do NOT use when:

* Graph is directed
* Graph is disconnected (unless computing forest)
* You need shortest path, not minimum cost tree

---

# 🔄 Comparison: Prim vs Kruskal

| Feature        | Prim           | Kruskal       |
| -------------- | -------------- | ------------- |
| Strategy       | Node-based     | Edge-based    |
| Best for       | Dense graphs   | Sparse graphs |
| Data Structure | Priority Queue | DSU           |
| Cycle Handling | Implicit       | Explicit      |

---

# 🌍 Real-World Applications

* Internet backbone layout
* Electrical grid design
* Transportation networks
* Data clustering
* Wireless sensor networks

---

# 💬 Interview Questions & Answers

### Q1: Difference between MST and shortest path?

MST minimizes total edge weight, shortest path minimizes distance between two nodes.

### Q2: Can MST be unique?

No, if multiple edges have same weight.

### Q3: Why Kruskal uses DSU?

To efficiently detect cycles.

### Q4: Can Prim work on disconnected graph?

No, it only builds MST for one component.

---

# 🎯 Final Summary

Prim’s and Kruskal’s are the two fundamental MST algorithms. Prim’s grows MST from nodes, Kruskal’s from edges. Choosing the right one depends on graph density and representation, a key interview insight.
