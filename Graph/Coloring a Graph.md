# Graph Coloring: M-Coloring vs Bipartite Graph Coloring – Interview-Ready Guide


* **M-Coloring Problem** (general graph coloring)
* **Bipartite Graph Checking / Coloring** (2-coloring)
* Why **both problems are fundamentally different**
* Why **different algorithms are required**

The content is structured exactly like a **GitHub README.md** and is meant for **SDE interviews in top MNCs**.

---

# 📘 Introduction

Graph coloring problems ask:

> *Can we color vertices of a graph such that no two adjacent vertices have the same color?*

However, **not all coloring problems are equal**.

* **M-Coloring** → General graph, any number of colors
* **Bipartite Graph** → Special graph that can be colored with **exactly 2 colors**

👉 This difference leads to **completely different algorithms, complexity, and guarantees**.

---

# 🧠 High-Level Difference (INTERVIEW MUST-KNOW)

| Feature    | M-Coloring   | Bipartite Coloring      |
| ---------- | ------------ | ----------------------- |
| Graph Type | Any graph    | Special graph           |
| Colors     | M (given)    | Exactly 2               |
| Guarantee  | No guarantee | Guaranteed if bipartite |
| Complexity | Exponential  | Linear                  |
| Approach   | Backtracking | BFS / DFS               |

---

# 🎨 1️⃣ M-Coloring Problem

## Problem Definition

Given:

* An undirected graph
* An integer **M**

Determine whether the graph can be colored using **at most M colors** such that:

```
No two adjacent vertices share the same color
```

---

## 🧠 Core Idea (Why It’s Hard)

* General graph coloring is **NP-Complete**
* We must try **all possible color assignments**
* Greedy approaches do NOT always work

Hence, **backtracking** is required.

---

## 📊 ASCII Diagram – M-Coloring

```
   (0)
  /   \
(1)---(2)

M = 2 ❌ Not possible
M = 3 ✔ Possible
```

---

## 🧮 Algorithm (Backtracking)

1. Assign colors one by one
2. Check if current color is safe
3. If conflict → backtrack

---

## 📘 C++ Implementation – M-Coloring

```cpp
bool isSafe(int node, int color[], vector<vector<int>>& graph, int n, int col) {
    for(int k = 0; k < n; k++) {
        if(graph[node][k] && color[k] == col)
            return false;
    }
    return true;
}

bool solve(int node, vector<vector<int>>& graph, int m, int n, int color[]) {
    if(node == n) return true;

    for(int col = 1; col <= m; col++) {
        if(isSafe(node, color, graph, n, col)) {
            color[node] = col;
            if(solve(node + 1, graph, m, n, color)) return true;
            color[node] = 0;
        }
    }
    return false;
}

bool graphColoring(vector<vector<int>>& graph, int m, int n) {
    int color[n] = {0};
    return solve(0, graph, m, n, color);
}
```

---

## ⏱ Time & Space Complexity (M-Coloring)

* **Time**: `O(M^N)` (exponential)
* **Space**: `O(N)` (recursion + color array)

---

# 🔵 2️⃣ Bipartite Graph Coloring (2-Coloring)

## Problem Definition

A graph is **bipartite** if:

* Vertices can be divided into two sets
* No edges exist within the same set

Equivalent to:

```
Graph can be colored using ONLY 2 colors
```

---

## 🧠 Core Idea (Why It’s Easy)

* Bipartite graphs have **special structure**
* Any **odd-length cycle** makes graph non-bipartite
* Linear-time checking is possible

---

## 📊 ASCII Diagram – Bipartite

```
0 ---- 1
|      |
3 ---- 2

Even cycle → Bipartite
```

Odd cycle:

```
0 ---- 1
 \    /
   2

❌ Not Bipartite
```

---

## 🧮 Algorithm (BFS / DFS Coloring)

1. Start with any node, color it 0
2. Neighbors get opposite color
3. Conflict → not bipartite

---

## 📘 C++ Implementation – Bipartite Check (BFS)

```cpp
bool isBipartite(int V, vector<int> adj[]) {
    vector<int> color(V, -1);

    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while(!q.empty()) {
                int node = q.front(); q.pop();
                for(int neigh : adj[node]) {
                    if(color[neigh] == -1) {
                        color[neigh] = 1 - color[node];
                        q.push(neigh);
                    }
                    else if(color[neigh] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
```

---

## ⏱ Time & Space Complexity (Bipartite)

* **Time**: `O(V + E)`
* **Space**: `O(V)`

---

# ❓ Why M-Coloring and Bipartite Use Different Algorithms

### Key Reason

| Aspect     | M-Coloring   | Bipartite  |
| ---------- | ------------ | ---------- |
| Constraint | General      | Special    |
| Colors     | Arbitrary M  | Fixed = 2  |
| Complexity | NP-Complete  | Polynomial |
| Algorithm  | Backtracking | BFS / DFS  |

👉 **Using bipartite logic for M-coloring will fail** because:

* More than 2 colors
* Conflicts can appear later
* No structural guarantee

👉 **Using M-coloring for bipartite is wasteful** and inefficient.

---

# 🎯 When to Use Which

## Use M-Coloring When

✔ General graph coloring needed
✔ M > 2
✔ Constraint satisfaction problem

## Use Bipartite Check When

✔ Need to check odd cycles
✔ Graph is expected to be bipartite
✔ Fast linear-time solution required

---

# 🛑 When NOT to Use

* Do NOT use M-coloring for bipartite graphs (overkill)
* Do NOT use bipartite logic for general coloring

---

# 🔄 Comparison with Other Graph Problems

| Problem        | Related Concept    |
| -------------- | ------------------ |
| Bipartite      | 2-coloring         |
| M-Coloring     | CSP / Backtracking |
| Graph Coloring | Scheduling         |
| Clique         | Coloring dual      |

---

# 🌍 Real-World Applications

* Timetable scheduling
* Register allocation (compilers)
* Frequency assignment
* Job scheduling
* Network conflict resolution

---

# 💬 Interview Q&A

### Q1: Is every bipartite graph 2-colorable?

Yes.

### Q2: Is every 2-colorable graph bipartite?

Yes.

### Q3: Why is M-coloring hard?

It is NP-Complete.

### Q4: Can bipartite graph have cycle?

Yes, even-length cycles only.

### Q5: Why BFS preferred for bipartite?

Level-based coloring simplifies logic.

---

# 🎯 Final Takeaway

> **Bipartite coloring is a special, efficient case of graph coloring, while M-coloring is a general NP-hard constraint problem.**

Understanding *why* their algorithms differ is a **strong interview differentiator**.

---

Repository complete.
