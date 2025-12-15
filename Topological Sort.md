# Topological Sort 

# 📘 Introduction

**Topological Sort** is a linear ordering of vertices of a **Directed Acyclic Graph (DAG)** such that:

> For every directed edge `u → v`, vertex `u` appears **before** vertex `v` in the ordering.

Topological sort is only possible **if the graph has no cycles**.

---

# 🧠 Core Idea

A node can be placed in the ordering **only after all its dependencies are processed**.

Two standard approaches:

1. **DFS + Stack** (post-order)
2. **Kahn’s Algorithm** (BFS + indegree)

---

# 📊 ASCII Diagram – Example DAG

```
Graph:
5 → 0 ← 4
↓         ↑
2 → 3 → 1

One valid topological order:
5 4 2 3 1 0
```

Dependencies are always respected.

---

# 🧮 Algorithm 1: DFS Based Topological Sort

### Idea

* Perform DFS
* Push node into stack **after visiting all neighbors**
* Pop stack to get topological order

### Steps

1. Visit unvisited node
2. DFS on its neighbors
3. Push node into stack

---

# 📘 C++ Implementation (DFS Based)

```cpp
#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool>& vis, stack<int>& st) {
    vis[node] = true;
    for(int v : adj[node]) {
        if(!vis[v]) dfs(v, adj, vis, st);
    }
    st.push(node);
}

vector<int> topoSort(int N, vector<int> adj[]) {
    vector<bool> vis(N, false);
    stack<int> st;

    for(int i = 0; i < N; i++) {
        if(!vis[i]) dfs(i, adj, vis, st);
    }

    vector<int> topo;
    while(!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}
```

---

# 🧮 Algorithm 2: Kahn’s Algorithm (BFS Based)

### Idea

* Count indegree of each node
* Push nodes with indegree = 0 into queue
* Remove edges and update indegrees

---

# 📘 C++ Implementation (Kahn’s Algorithm)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> topoSort(int N, vector<int> adj[]) {
    vector<int> indeg(N, 0);
    for(int i = 0; i < N; i++) {
        for(int v : adj[i]) indeg[v]++;
    }

    queue<int> q;
    for(int i = 0; i < N; i++)
        if(indeg[i] == 0) q.push(i);

    vector<int> topo;
    while(!q.empty()) {
        int node = q.front(); q.pop();
        topo.push_back(node);
        for(int v : adj[node]) {
            if(--indeg[v] == 0) q.push(v);
        }
    }

    return topo;
}
```

---

# 🧩 Use Cases of Topological Sort

Topological sort is preferred when:

✔ Task scheduling with dependencies
✔ Ordering problems
✔ DAG shortest path
✔ Course prerequisite problems
✔ Build systems

---

# ⏱ Time & Space Complexity

| Algorithm | Time     | Space    |
| --------- | -------- | -------- |
| DFS-based | O(N + M) | O(N + M) |
| Kahn’s    | O(N + M) | O(N + M) |

---

# 🎯 When to Use Topological Sort

Use Topological Sort when:

* Graph is **directed**
* Graph has **dependencies**
* Graph is guaranteed to be **acyclic (DAG)**

---

# 🛑 When NOT to Use Topological Sort

Do NOT use when:

* Graph has **cycles**
* Graph is **undirected**
* You need shortest path in general graphs

---

# 🔄 Comparison with Other Algorithms

| Algorithm        | Graph Type | Use Case                          |
| ---------------- | ---------- | --------------------------------- |
| Topological Sort | DAG        | Ordering / DAG shortest path      |
| Dijkstra         | General    | Shortest path (no negative edges) |
| Bellman–Ford     | General    | Negative edges                    |
| BFS              | Unweighted | Level traversal                   |

---

# 🌍 Real-World Applications

* Course scheduling systems
* Task dependency resolution
* Build tools (Make, Maven)
* Compiler design (instruction ordering)
* DAG-based job scheduling

---

# 💬 Interview Questions & Answers

### Q1: Why topological sort works only for DAG?

Because cycles create circular dependencies, making ordering impossible.

### Q2: Can a DAG have multiple topological orders?

Yes, many valid orders may exist.

### Q3: How do you detect a cycle?

Using Kahn’s algorithm (if topo size < N) or DFS recursion stack.

### Q4: Why topo sort is used in DAG shortest path?

Because nodes are processed only after all predecessors.

---

# 🎯 Final Summary

Topological Sort is a fundamental DAG algorithm used to resolve dependencies efficiently.
It forms the backbone of scheduling, DAG shortest paths, and many real-world systems.

