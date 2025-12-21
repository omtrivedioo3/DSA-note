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

# 🎯 Summary

Bellman–Ford is essential when working with **negative weights or negative cycles**. Although slower than Dijkstra, it guarantees correctness in every scenario where Dijkstra fails.

