# Floyd–Warshall Algorithm 


# 📘 Introduction

The **Floyd–Warshall Algorithm** is a **dynamic programming algorithm** used to compute **shortest paths between ALL pairs of vertices** in a weighted graph.

Key properties:

* Works for **directed and undirected graphs**
* Handles **negative edge weights**
* Can **detect negative cycles**
* Computes **all-pairs shortest paths (APSP)** in one run

---

# 🧠 Core Idea (Dynamic Programming)

Floyd–Warshall is based on the idea:

> *Is the shortest path from i to j shorter if we allow node k as an intermediate node?*

We progressively allow intermediate nodes from `0` to `k`.

---

# 📊 DP State Definition

Let:

```
dp[i][j] = shortest distance from node i to node j
```

Transition:

```
dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j])
```

We try every node `k` as an intermediate.

---

# 📊 ASCII Diagram – Intuition

```
Before considering node k:
 i  ------10------>  j

Through node k:
 i ----3----> k ----4----> j

Update:
 dp[i][j] = min(10, 3 + 4) = 7
```

---

# 🧮 Algorithm Steps

1. Initialize distance matrix
2. Set dist[i][i] = 0
3. For each intermediate node k:

   * For each pair (i, j):

     * Relax using node k

---

# 📘 Full C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist, int n) {
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> dist = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    floydWarshall(dist, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}
```

---

# 🧩 Use Cases of Floyd–Warshall

Floyd–Warshall is preferred when:

✔ All-pairs shortest paths are needed
✔ Graph is **small to medium size**
✔ Negative weights exist
✔ Simplicity is preferred over performance

Typical problems:

* All-pairs distance matrix
* Transitive closure
* Graph reachability
* Detecting negative cycles

---

# ⏱ Time & Space Complexity

### Time Complexity

```
O(N³)
```

### Space Complexity

```
O(N²)
```

---

# 🎯 When to Use Floyd–Warshall

Use Floyd–Warshall when:

* N ≤ 400 (practical limit)
* Need shortest paths between every pair
* Graph may have negative edges
* Code simplicity matters

---

# 🛑 When NOT to Use Floyd–Warshall

Do NOT use Floyd–Warshall when:

* Graph is large (N > 500)
* Need single-source shortest path only
* Memory is constrained

---

# 🔄 Comparison: Floyd–Warshall vs Dijkstra vs Bellman–Ford

| Feature                  | Floyd–Warshall | Dijkstra      | Bellman–Ford  |
| ------------------------ | -------------- | ------------- | ------------- |
| Shortest Path Type       | All-pairs      | Single-source | Single-source |
| Negative Weights         | ✔ Yes          | ❌ No          | ✔ Yes         |
| Negative Cycle Detection | ✔ Yes          | ❌ No          | ✔ Yes         |
| Time Complexity          | O(N³)          | O(M log N)    | O(NM)         |
| Space                    | O(N²)          | O(N+M)        | O(N)          |
| Graph Size               | Small          | Large         | Medium        |

---

# 🌍 Real-World Applications

* Network routing tables
* Traffic flow analysis
* City distance matrices
* Graph reachability problems
* Currency arbitrage detection

---

# 💬 Interview Questions & Answers

### Q1: Why Floyd–Warshall is O(N³)?

Three nested loops over nodes i, j, k.

### Q2: How to detect negative cycles?

If dist[i][i] < 0 after algorithm.

### Q3: Can Floyd–Warshall handle negative edges?

Yes, but not negative cycles.

### Q4: When would you prefer Dijkstra over Floyd–Warshall?

When graph is large and only single-source paths are required.

### Q5: Is Floyd–Warshall greedy?

No, it is dynamic programming.

---

# 🎯 Final Summary

Floyd–Warshall is a simple yet powerful APSP algorithm ideal for small graphs and scenarios requiring all-pairs shortest paths. While slower than Dijkstra and Bellman–Ford, its simplicity and ability to handle negative edges make it valuable in system design and interview problems.

---
