# 🚀 Bellman–Ford Algorithm

Bellman–Ford is a **dynamic programming-based** shortest path algorithm.
It is capable of handling:

* **Negative edge weights**
* **Negative cycle detection**

This makes it more powerful than Dijkstra, but slower.

Time Complexity: **O(V × E)** → Much slower than Dijkstra.

---

# 🧠 When to Use Bellman–Ford

Use Bellman–Ford when:

* Graph contains **negative edges**
* Need to **detect negative cycles**
* You prioritize correctness over performance
* Graph is small or moderately sized

---

# ⚠️ When NOT to Use Bellman–Ford

Do **NOT** use Bellman–Ford when:

* Graph has only **non-negative weights**
* Graph is large (high V and E)
* High performance is required

In such cases → **Use Dijkstra**, which is dramatically faster.

---

# ❌ Why NOT Use Dijkstra Instead of Bellman–Ford?

Dijkstra **fails** when:

* Any edge has a **negative weight**
* Graph structure or business logic includes discounts/penalties

Dijkstra may return **incorrect shortest paths** with negative edges.
Bellman–Ford correctly handles these cases.

---

# 📘 Full C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int N, vector<vector<int>>& edges) {
    vector<int> dist(N, INT_MAX);
    dist[0] = 0; // Source

    // Relax all edges N-1 times
    for(int i = 0; i < N - 1; i++) {
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Detect Negative Cycle
    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];
        if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Negative Cycle Detected!";
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
0 → 2 (5)
1 → 2 (-3)
2 → 3 (2)
```

### Output

```
Shortest distances from source 0:
0 4 1 3
```

Bellman–Ford handles the **negative edge (-3)** correctly.

---

# 🧩 Use Cases

* Financial arbitrage detection (negative cycles)
* Road networks with toll discounts
* Graphs where penalties reduce cost
* Network routing protocols → RIP uses Bellman–Ford
* Systems needing **negative cycle alerts**

---

# 🛑 Limitations

* Much slower than Dijkstra
* Not suitable for high-scale or real-time systems
* Recomputes all edges repeatedly (DP-based)
* High time complexity → O(V × E)

---

# 🔥 Bellman–Ford vs Dijkstra (Summary)

| Feature                  | Dijkstra                      | Bellman–Ford                 |
| ------------------------ | ----------------------------- | ---------------------------- |
| Negative weights         | ❌ No                          | ✔ Yes                        |
| Negative cycle detection | ❌ No                          | ✔ Yes                        |
| Speed                    | Fast                          | Slow                         |
| Approach                 | Greedy                        | Dynamic Programming          |
| Use case                 | Large, positive-weight graphs | Graphs with negative weights |

---
🔁 Why Does Bellman–Ford Relax Edges N−1 Times?

This is one of the most important conceptual questions interviewers ask about Bellman–Ford.

🧠 Core Theoretical Reason (One-Line Answer)

In a graph with N vertices, the shortest path between any two vertices can have at most N−1 edges (if no cycle is involved).

That is why Bellman–Ford performs exactly N−1 relaxation iterations.

📘 Detailed Explanation (Interview-Grade)
1️⃣ What One Relaxation Iteration Achieves

Each full pass over all edges allows Bellman–Ford to correctly compute:

Shortest paths that use at most one more edge than before.

Bellman–Ford works like Dynamic Programming on path length:

Iteration	Shortest paths guaranteed
1st	Paths using ≤ 1 edge
2nd	Paths using ≤ 2 edges
3rd	Paths using ≤ 3 edges
…	…
N−1	Paths using ≤ N−1 edges
2️⃣ Why a Shortest Path Never Needs ≥ N Edges

If a path uses N or more edges in a graph with N vertices:

At least one vertex must repeat

A repeated vertex implies a cycle

Cycle analysis:

Cycle Type	Effect
Positive	Removing cycle shortens path
Zero	Removing cycle doesn’t change path
Negative	Distance decreases indefinitely ❌

👉 Therefore:

Valid shortest paths never include cycles

Maximum edges required = N−1

⚠️ Why the Extra Iteration Detects Negative Cycles

After N−1 iterations, distances are finalized.

If one more relaxation still improves distance:

dist[u] + w < dist[v]


Then:

Path uses ≥ N edges

A cycle exists

Since distance decreases → negative cycle

That is why the final pass works.

# 🎯 Summary

Bellman–Ford is essential when working with **negative weights or negative cycles**. Although slower than Dijkstra, it guarantees correctness in every scenario where Dijkstra fails.

