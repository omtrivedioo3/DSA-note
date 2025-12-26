# Binary Search Tree (BST) – Insert, Delete, Floor & Ceil

* Inserting a node in BST
* Deleting a node from BST (all cases)
* Finding **Floor** value in BST
* Finding **Ceil** value in BST

The focus is on **correct logic, edge cases, and interview clarity**, not just code.

---

# 📘 What is a Binary Search Tree (BST)?

A **Binary Search Tree** is a binary tree where:

```
For every node N:
- All nodes in left subtree  < N.val
- All nodes in right subtree > N.val
```

This property allows **efficient searching, insertion, and deletion**.

---

# 🌳 Example BST

```
        8
       / \
      3   10
     / \    \
    1   6    14
       / \   /
      4   7 13
```

---

# 1️⃣ Insert a Node in BST

## 🧠 Intuition

* Compare the key with current node
* Move **left** if smaller, **right** if larger
* Insert when a NULL position is found

---

## 📘 C++ Code – Insert

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* insertBST(TreeNode* root, int key) {
    if(root == nullptr)
        return new TreeNode(key);

    if(key < root->val)
        root->left = insertBST(root->left, key);
    else if(key > root->val)
        root->right = insertBST(root->right, key);

    return root;
}
```

---

## ⏱ Complexity

* **Time:** O(h)
* **Space:** O(h) (recursive stack)

Where `h` is the height of the BST.

---

# 2️⃣ Delete a Node from BST (MOST IMPORTANT)

## 🧠 Deletion Cases

### Case 1: Leaf Node

```
Delete directly
```

### Case 2: One Child

```
Replace node with its child
```

### Case 3: Two Children

```
Replace with inorder successor (minimum in right subtree)
```

---

## 📘 C++ Code – Delete

```cpp
TreeNode* findMin(TreeNode* root) {
    while(root->left)
        root = root->left;
    return root;
}

TreeNode* deleteBST(TreeNode* root, int key) {
    if(root == nullptr) return nullptr;

    if(key < root->val)
        root->left = deleteBST(root->left, key);
    else if(key > root->val)
        root->right = deleteBST(root->right, key);
    else {
        // Case 1 & 2
        if(!root->left) return root->right;
        if(!root->right) return root->left;

        // Case 3
        TreeNode* succ = findMin(root->right);
        root->val = succ->val;
        root->right = deleteBST(root->right, succ->val);
    }
    return root;
}
```

---

## ⏱ Complexity

* **Time:** O(h)
* **Space:** O(h)

---

# 3️⃣ Floor Value in BST

## 📌 Definition

> **Floor(x)** = Greatest value in BST **≤ x**

---

## 🧠 Logic

* If node value == x → return x
* If node value > x → move left
* If node value < x → store candidate, move right

---

## 📘 C++ Code – Floor

```cpp
int floorBST(TreeNode* root, int x) {
    int ans = -1;
    while(root) {
        if(root->val == x) return x;
        if(root->val > x)
            root = root->left;
        else {
            ans = root->val;
            root = root->right;
        }
    }
    return ans;
}
```

---

# 4️⃣ Ceil Value in BST

## 📌 Definition

> **Ceil(x)** = Smallest value in BST **≥ x**

---

## 🧠 Logic

* If node value == x → return x
* If node value < x → move right
* If node value > x → store candidate, move left

---

## 📘 C++ Code – Ceil

```cpp
int ceilBST(TreeNode* root, int x) {
    int ans = -1;
    while(root) {
        if(root->val == x) return x;
        if(root->val < x)
            root = root->right;
        else {
            ans = root->val;
            root = root->left;
        }
    }
    return ans;
}
```

---

# ⏱ Overall Time & Space Complexity

| Operation | Time | Space |
| --------- | ---- | ----- |
| Insert    | O(h) | O(h)  |
| Delete    | O(h) | O(h)  |
| Floor     | O(h) | O(1)  |
| Ceil      | O(h) | O(1)  |

---

# 🎯 When to Use BST

✔ Ordered data required
✔ Range queries (floor / ceil)
✔ Dynamic insert & delete

---

# 🛑 When NOT to Use BST

✖ When tree can become skewed
✖ Strict O(log n) needed → use AVL / Red-Black Tree

---

# 🔄 Comparison with Other Data Structures

| Structure    | Search   | Insert   | Delete   | Ordered |
| ------------ | -------- | -------- | -------- | ------- |
| BST          | O(h)     | O(h)     | O(h)     | ✔       |
| Balanced BST | O(log n) | O(log n) | O(log n) | ✔       |
| HashMap      | O(1) avg | O(1)     | O(1)     | ❌       |
| Array        | O(n)     | O(n)     | O(n)     | ✔       |

---

# 🌍 Real-World Applications

* Database indexing
* File systems
* Range queries
* Ordered symbol tables
* Auto-complete systems

---

# 💬 Interview-Ready Q&A

### Q1: Why use inorder successor in deletion?

To preserve BST ordering.

### Q2: Can we use inorder predecessor instead?

Yes, both are valid.

### Q3: Worst-case complexity of BST?

O(n) when tree is skewed.

### Q4: Why floor/ceil efficient in BST?

BST property prunes half the tree at each step.

---

# 🎯 Final Takeaway

> **BST operations rely on ordered structure; correctness comes from choosing the correct subtree at every step.**

If you can clearly explain insert, delete, floor, and ceil, you demonstrate strong tree fundamentals.

---

Repository complete.
