# Dijkstra Algorithm – Git Repository File

## 📌 Repository: `dijkstra-shortest-path`

This repository contains:

* Full implementation of **Dijkstra’s Algorithm**
* Use cases
* Limitations
* Why we should NOT use Bellman–Ford instead

---

# 🚀 Dijkstra’s Algorithm

Dijkstra’s algorithm is a **greedy shortest‑path algorithm** used to find the minimum distance from a source node to all other nodes **in a graph with non‑negative edge weights**.

---

## ✔️ Features

* Single‑source shortest path
* Efficient for large graphs
* Works with adjacency list + min‑heap
* Time complexity: **O(E log V)**

---

# 🧠 When to Use Dijkstra

Use Dijkstra when:

* Graph has **NO negative weights**
* Need fast shortest‑path computation
* Graph is large (millions of nodes/edges)
* Used in maps, routing, network optimization, etc.

---

# ⚠️ When NOT to Use Dijkstra

Do **NOT** use Dijkstra if:

* Graph contains **negative edge weights**
* You need **negative cycle detection**

If negatives exist → algorithm becomes incorrect.

---

# ❌ Why NOT Use Bellman–Ford Instead of Dijkstra?

Bellman–Ford:

* Works with negative edges
* Detects negative cycles
* BUT is **very slow** → O(V × E)

For large graphs, Bellman–Ford is up to **100× slower**.
Dijkstra is far more efficient when all edges are non‑negative.

---

# 📘 Full C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int N, vector<vector<int>>& edges) {
    vector<vector<pair<int,int>>> adj(N);
    for(auto &e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
    }

    vector<int> dist(N, INT_MAX);
    dist[0] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 0});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;

        for(auto &p : adj[u]){
            int v = p.first;
            int w = p.second;

            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

---

# 🧪 Example

### Input

Graph edges:

```
0 → 1 (4)
0 → 2 (1)
2 → 1 (2)
1 → 3 (1)
2 → 3 (5)
```

### Output

```
Shortest distances from source 0:
0 3 1 4
```

---

# 🧩 Use Cases

* Google Maps routing
* Network routing (OSPF uses Dijkstra)
* Game pathfinding (A*)
* Robot navigation
* Distributed systems routing

---

# 🛑 Limitations

* Does not work with **negative weights**
* Cannot detect negative cycles
* Greedy nature fails in edge cases with negatives



# 🎯 Summary

Dijkstra is the optimal shortest‑path algorithm for **non‑negative weighted graphs** and is widely used in real‑world routing systems. Bellman–Ford is more powerful but far slower, and should only be used when negative weights are present.

---

Reply **B** when you're ready for the Bellman–Ford repository file!
