# Cycle Detection in Graphs (Directed & Undirected)

# 📘 Introduction

A **cycle** in a graph exists if we can start from a node and return to the same node by following edges.

Cycle detection is a **fundamental graph problem** used in:

* Dependency resolution
* Deadlock detection
* Network analysis
* Compiler design

⚠️ **Important:**

> **Cycle detection in directed and undirected graphs requires DIFFERENT logic.**

---

# 🧠 Why Different Solutions for Directed vs Undirected Graphs?

## 🔹 Undirected Graph

* Edges are **bidirectional**
* DFS naturally goes back to parent
* We must ignore the immediate parent edge

## 🔹 Directed Graph

* Edges have **direction**
* Parent concept alone is insufficient
* We must detect **back edges in the same DFS path**

👉 This is why **the same algorithm cannot be used for both graphs**.

---

# 📊 ASCII Diagram – Core Difference

### Undirected Graph

```
0 —— 1 —— 2
 \         /
  ---------
```

Back-edge to parent is NOT a cycle.

### Directed Graph

```
0 → 1 → 2
    ↑     ↓
    ←-----
```

Back-edge in recursion stack = cycle.

---

# 🔄 Cycle Detection in UNDIRECTED Graph

## 🧮 Algorithm (DFS + Parent Tracking)

### Idea

* Perform DFS
* For every visited neighbor:

  * If neighbor ≠ parent → cycle exists

---

## 📘 C++ Implementation (Undirected Graph)

```cpp
bool dfsUndirected(int node, int parent, vector<int> adj[], vector<bool>& vis) {
    vis[node] = true;
    for (int neigh : adj[node]) {
        if (!vis[neigh]) {
            if (dfsUndirected(neigh, node, adj, vis)) return true;
        }
        else if (neigh != parent) {
            return true; // cycle detected
        }
    }
    return false;
}

bool isCycleUndirected(int V, vector<int> adj[]) {
    vector<bool> vis(V, false);
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            if (dfsUndirected(i, -1, adj, vis)) return true;
        }
    }
    return false;
}
```
# 🔄 Find nodes that form Cycle  in Undirected Graph
```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> graph;
    vector<int> parent;
    vector<bool> visited, inCycle;

    int cycleStart = -1, cycleEnd = -1;

    // DFS to detect cycle in undirected graph
    bool dfs(int node, int par) {
        visited[node] = true;
        parent[node] = par;

        for (int neigh : graph[node]) {
            if (neigh == par) continue;

            if (!visited[neigh]) {
                if (dfs(neigh, node))
                    return true;
            } 
            else {
                // Cycle detected
                cycleStart = neigh;
                cycleEnd = node;
                return true;
            }
        }
        return false;
    }

    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {

        // Step 1: Build graph
        graph.resize(n);
        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        visited.assign(n, false);
        parent.assign(n, -1);
        inCycle.assign(n, false);

        // Step 2: Find cycle using DFS
        dfs(0, -1);

        // Step 3: Mark all nodes in the cycle
        int cur = cycleEnd;
        inCycle[cur] = true;

        while (cur != cycleStart) {
            cur = parent[cur];
            inCycle[cur] = true;
        }
	}
};
```
---

# 🔄 Cycle Detection in DIRECTED Graph

## 🧮 Algorithm 1: DFS + Recursion Stack

### Idea

* Maintain two arrays:

  * `vis[]` → visited nodes
  * `pathVis[]` → nodes in current DFS path
* If we revisit a node already in `pathVis` → cycle

---

## 📘 C++ Implementation (Directed Graph – DFS)

```cpp
bool dfsDirected(int node, vector<int> adj[], vector<bool>& vis, vector<bool>& pathVis) {
    vis[node] = true;
    pathVis[node] = true;

    for (int neigh : adj[node]) {
        if (!vis[neigh]) {
            if (dfsDirected(neigh, adj, vis, pathVis)) return true;
        }
        else if (pathVis[neigh]) {
            return true; // cycle detected
        }
    }

    pathVis[node] = false;
    return false;
}

bool isCycleDirected(int V, vector<int> adj[]) {
    vector<bool> vis(V, false), pathVis(V, false);
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            if (dfsDirected(i, adj, vis, pathVis)) return true;
        }
    }
	// pathVis has all nodes which form cycles
    return false;
}
```

---

# 🔄 Alternative Directed Graph Solution (Kahn’s Algorithm)

## 🧠 Idea

* If topological sort does NOT include all nodes → cycle exists
class Solution {
private:
    /* Function to return the topological
     sorting of given graph */
    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> ans;
	    vector<int> inDegree(V, 0);
	    
	    for(int i=0; i<V; i++) {
	        for(auto it : adj[i]) inDegree[it]++;
	    }
	    
	    queue<int> q;
	    
	    for(int i=0; i<V; i++) {
	        if(inDegree[i] == 0) q.push(i);
	    }
	    
	    // Until the queue is empty
	    while(!q.empty()) {
	        
	        // Get the node
	        int node = q.front();
	        
	        ans.push_back(node);
	        q.pop();
	        for(auto it : adj[node]) {
	            inDegree[it]--;
	       
	            if(inDegree[it] == 0) q.push(it);
	        }
	    }
	    return ans;
    }
    
public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> topo;
        
        topo = topoSort(V, adj);
        
        if(topo.size() < V) return true;
        return false;
    }
};
### Time Complexity

```
O(V + E)
```

---

# 🧩 Use Cases

✔ Dependency graphs
✔ Course scheduling
✔ Deadlock detection
✔ Build systems
✔ Workflow validation

---

# ⏱ Time & Space Complexity

| Graph Type | Algorithm    | Time     | Space |
| ---------- | ------------ | -------- | ----- |
| Undirected | DFS + Parent | O(V + E) | O(V)  |
| Directed   | DFS + Stack  | O(V + E) | O(V)  |
| Directed   | Kahn’s       | O(V + E) | O(V)  |

---

# 🎯 When to Use Cycle Detection

Use cycle detection when:

* Graph represents dependencies
* Order matters
* System deadlocks must be avoided

---

# 🛑 When NOT to Use

Do NOT use when:

* Graph is trivial
* Tree structure is guaranteed
* No dependency constraints

---

# 🔄 Comparison with Other Algorithms

| Algorithm        | Use Case                        |
| ---------------- | ------------------------------- |
| Cycle Detection  | Dependency validation           |
| Topological Sort | Ordering DAG                    |
| DSU              | Undirected connectivity         |
| SCC              | Strong cycles in directed graph |

---

# 🌍 Real-World Applications

* Package managers (npm, pip)
* Compiler dependency checks
* Operating system deadlock detection
* Workflow engines
* CI/CD pipelines

---

# 💬 Interview Questions & Answers

### Q1: Why parent logic works only for undirected graphs?

Because edges are bidirectional; parent edge must be ignored.

### Q2: Why recursion stack is needed for directed graphs?

To detect back edges within the same DFS path.

### Q3: Can DSU detect cycles in directed graphs?

No.

### Q4: Can BFS detect cycles?

Yes (Kahn’s algorithm for directed graphs).

### Q5: Time complexity?

O(V + E)

---

# 🎯 Final Summary

Cycle detection is graph-type dependent. Undirected graphs use parent-based DFS, while directed graphs require recursion-stack or topological techniques. Using the wrong approach leads to incorrect results — a critical interview concept.

