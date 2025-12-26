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

/* Define P as a shorthand 
for the pair<int, int> type */
#define P pair<int,int>

class Solution {
public:
    /* Function to find the shortest distance of all 
    the vertices from the source vertex S. */
    vector <int> dijkstra(int V, vector<vector<int>> adj[], 
                          int S) {
                                
        // Priority queue 
        priority_queue <P, vector<P>, greater<P>> pq;
        
        // Distance array
        vector<int> dist(V, 1e9);
        
        // Distance of source node from itself is 0
        dist[S] = 0;
        
        // Add the source node to the priority queue
        pq.push({0, S});
        
        // Until the priority queue is empty
        while(!pq.empty()) {
            
            // Get the tentative distance
            int dis = pq.top().first;
            
            // Get the node
            int node = pq.top().second;
            pq.pop();
            
            // Traverse all its neighbors
            for(auto it : adj[node]) {
                
                int adjNode = it[0]; // node
                int edgeWt = it[1]; // edge weight
                
                /* If the tentative distance to 
                reach adjacent node is smaller 
                than the known distance */
                if(dis + edgeWt < dist[adjNode]) {
                    
                    // Update the known distance
                    dist[adjNode] = dis + edgeWt;
                    
                    // Push the new pair in priority queue
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        
        // Return the result
        return dist;
    }
};

int main() {
    
    int V = 2, S = 0;
    vector<vector<int>> adj[V] = {
        {{1, 9}}, 
        {{0, 9}}
    };
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to find the shortest distance 
    of each node from the source node */
    vector<int> ans = sol.dijkstra(V, adj, S);
    
    // Output
    cout << "The shortest distance of nodes from the source node is: ";
    for(int i=0; i < V; i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
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
