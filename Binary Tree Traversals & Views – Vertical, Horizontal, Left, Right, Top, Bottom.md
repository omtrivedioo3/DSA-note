# Binary Tree Traversals & Views – Vertical, Horizontal, Left, Right, Top, Bottom


This repository contains a **complete, interview-ready guide to all major Binary Tree traversals and views**, including:

* Vertical Order Traversal
* Level Order (Horizontal Traversal)
* Left View
* Right View
* Top View
* Bottom View

It explains **why different data structures (map, priority queue, queue)** are used, with **full C++ implementations**, diagrams, complexity analysis, and interview Q&A.

---

# 📘 Introduction

Binary Tree *views* represent how a tree looks when observed from different directions:

* **Horizontal** → Level by level
* **Vertical** → Column by column
* **Left / Right** → Side views
* **Top / Bottom** → Overhead views

These problems test:

* Tree traversal mastery
* Coordinate-based thinking
* BFS vs DFS understanding
* Proper use of maps & priority queues

---

# 🧠 Core Coordinate System Idea

To represent directions, we use **coordinates**:

* **Vertical level (x)** → left (-1), right (+1)
* **Depth / level (y)** → top (0) to bottom (+1)

```
          (x=0,y=0)
             1
           /   \
   (-1,1) 2     3 (1,1)
          \   /
      (-1,2)4 5(0,2)
```

This coordinate system enables vertical, top, and bottom views.

---

# 🌐 1. Horizontal (Level Order) Traversal

## Idea

Traverse tree **level by level** using BFS.

---

## C++ Implementation

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for(int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->data);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}
```

---

# 📏 2. Vertical Order Traversal

## Idea

Group nodes by **vertical line (x)**, then sort by:

1. Level (y)
2. Node value (if required)

---

## ❓ Why 2D Map + Priority Queue?

### 2D Map:

```
map<x, map<y, multiset>>
```

Ensures:

* Left → right order (x)
* Top → bottom order (y)

### Priority Queue / multiset:

Used to **maintain sorted order** when:

* Multiple nodes share same (x, y)

This guarantees **deterministic & ordered output**.

normal map<int,vector<int>>mp works but it wont give correct order at each level

---

## C++ Implementation (Vertical Traversal)

```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    map<int, map<int, multiset<int>>> nodes;
    queue<pair<TreeNode*, pair<int,int>>> q;
    q.push({root, {0, 0}});

    while(!q.empty()) {
        auto temp = q.front(); q.pop();
        TreeNode* node = temp.first;
        int x = temp.second.first;
        int y = temp.second.second;

        nodes[x][y].insert(node->data);

        if(node->left)
            q.push({node->left, {x - 1, y + 1}});
        if(node->right)
            q.push({node->right, {x + 1, y + 1}});
    }

    vector<vector<int>> ans;
    for(auto &p : nodes) {
        vector<int> col;
        for(auto &q : p.second) {
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
        ans.push_back(col);
    }
    return ans;
}
```

---

# 👈 3. Left View

## Idea

First node at each level when traversing left-first.

```cpp
vector<int> leftView(TreeNode* root) {
    vector<int> res;
    if(!root) return res;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            if(i == 0) res.push_back(node->data);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return res;
}
```

---

# 👉 4. Right View

## Idea

Last node at each level.

```cpp
vector<int> rightView(TreeNode* root) {
    vector<int> res;
    if(!root) return res;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            if(i == sz - 1) res.push_back(node->data);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return res;
}
```

---

# ⬆️ 5. Top View

## Idea

For each vertical line, **pick first node encountered**.

```cpp
vector<int> topView(TreeNode* root) {
    map<int, int> mp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        auto [node, x] = q.front(); q.pop();
        if(mp.find(x) == mp.end())
            mp[x] = node->data;
        if(node->left) q.push({node->left, x - 1});
        if(node->right) q.push({node->right, x + 1});
    }

    vector<int> res;
    for(auto &p : mp) res.push_back(p.second);
    return res;
}
```

---

# ⬇️ 6. Bottom View

## Idea

For each vertical line, **overwrite with last node**.

```cpp
vector<int> bottomView(TreeNode* root) {
    map<int, int> mp;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        auto [node, x] = q.front(); q.pop();
        mp[x] = node->data;
        if(node->left) q.push({node->left, x - 1});
        if(node->right) q.push({node->right, x + 1});
    }

    vector<int> res;
    for(auto &p : mp) res.push_back(p.second);
    return res;
}
```

---

# ⏱ Time & Space Complexity

| Traversal   | Time       | Space |
| ----------- | ---------- | ----- |
| Level Order | O(N)       | O(N)  |
| Left/Right  | O(N)       | O(N)  |
| Top/Bottom  | O(N log N) | O(N)  |
| Vertical    | O(N log N) | O(N)  |

---

# 🎯 When to Use These Traversals

✔ UI tree rendering
✔ Hierarchical data visualization
✔ Compiler parse trees
✔ Tree-based analytics
✔ Interview tree problems

---

# 🛑 When NOT to Use

✖ If simple DFS is sufficient
✖ When order doesn’t matter
✖ Extremely memory-constrained environments

---

# 🔄 Comparison Summary

| View       | Key Idea                |
| ---------- | ----------------------- |
| Level      | BFS                     |
| Left/Right | Level extremes          |
| Top        | First node per vertical |
| Bottom     | Last node per vertical  |
| Vertical   | 2D coordinate sorting   |

---

# 🌍 Real-World Applications

* File system trees
* Organizational charts
* Syntax trees
* UI layout engines

---

# 💬 Interview Questions & Answers

### Q1: Why BFS preferred for views?

Because BFS processes nodes level by level.

### Q2: Why map in vertical traversal?

To maintain left-to-right ordering.

### Q3: Why multiset/priority queue?

To handle nodes with same coordinates deterministically.

### Q4: Can DFS be used?

Yes, but BFS is simpler and safer.

---

# 🎯 Final Summary

Binary tree views are variations of BFS with coordinate tracking. Vertical traversal is the most complex and requires ordered data structures to ensure correctness — a key interview insight.

---

Repository file complete!
