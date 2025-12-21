# Min Heap & Max Heap (From Scratch) – Ultra-Deep Interview Guide

## 📌 Repository: `heap-min-max-from-scratch`

This repository contains a **complete, interview-ready implementation and explanation of Min Heap and Max Heap built from scratch (without STL)**. It is designed specifically for **SDE interviews in top MNCs**.

You will learn:

* What a heap really is (array + tree view)
* How Min Heap and Max Heap differ
* How insertion, deletion, and heapify work internally
* Full C++ implementation from scratch
* Use cases, complexity, comparisons, and interview Q&A

---

# 📘 Introduction

A **Heap** is a **complete binary tree** that satisfies the **heap property**:

* **Min Heap** → Parent ≤ Children
* **Max Heap** → Parent ≥ Children

Heaps are typically implemented using **arrays**, not pointers.

---

# 🧠 Why Heaps Are Important (Interview Perspective)

Heaps are the backbone of:

* Priority Queue
* Dijkstra’s Algorithm
* Top-K problems
* Scheduling systems

Interviewers expect you to:

* Understand heap internals
* Explain heapify
* Write heap from scratch (no STL)

---

# 🌳 Heap as Tree + Array (Mental Model)

### Tree Representation

```
        10
      /    \
     20     30
    /  \
   40  50
```

### Array Representation (0-indexed)

```
Index:  0   1   2   3   4
Value: [10, 20, 30, 40, 50]
```

### Index Relationships

```
Parent(i) = (i - 1) / 2
Left(i)   = 2*i + 1
Right(i)  = 2*i + 2
```

---

# 🔵 Min Heap

## Building Min Heap FROM ARRAY (FROM SCRATCH)

In interviews, you are often given an **unsorted array** and asked to:

> "Convert this array into a Min Heap"

### Key Idea

* Leaf nodes already satisfy heap property
* Start heapifying from **last non-leaf node** downwards

### Index of last non-leaf node

```
(n / 2) - 1
```

---

### Min Heap – Build Algorithm (Bottom-Up)

```
for i = (n/2 - 1) down to 0
    heapifyDown(i)
```

This is more efficient than inserting one by one.

---

## Min Heap Property

```
For every node i:
heap[i] ≤ heap[left(i)] AND heap[i] ≤ heap[right(i)]
```

---

## Operations in Min Heap

1. Insert
2. Get Min
3. Delete Min
4. Heapify (up & down)

---

## 📘 Min Heap – C++ Implementation (From Scratch)

```cpp
class Solution {
private:
    vector<int> arr; // list to store the min-heap
    int count; // to store the count of elements in min-heap
    
    // Function to recursively heapify the array upwards
    void heapifyUp(vector<int> &arr, int ind) {
        int parentInd = (ind - 1)/2; 

        // If current index holds smaller value than the parent
        if(ind > 0 && arr[ind] < arr[parentInd]) {
            // Swap the values at the two indices
            swap(arr[ind], arr[parentInd]);

            // Recursively heapify the upper nodes
            heapifyUp(arr, parentInd);
        } 

        return;
    }
    
    // Function to recursively heapify the array downwards
    void heapifyDown(vector<int> &arr, int ind) {
        int n = arr.size(); // Size of the array

        // To store th index of smallest element
        int smallestInd = ind; 

        // Indices of the left and right children
        int leftChildInd = 2*ind + 1, rightChildInd = 2*ind + 2;
        
        // If the left child holds smaller value, update the smallest index
        if(leftChildInd < n && arr[leftChildInd] < arr[smallestInd]) 
            smallestInd = leftChildInd;

        // If the right child holds smaller value, update the smallest index
        if(rightChildInd < n && arr[rightChildInd] < arr[smallestInd]) 
            smallestInd = rightChildInd;

        // If the smallest element index is updated
        if(smallestInd != ind) {
            // Swap the largest element with the current index
            swap(arr[smallestInd] , arr[ind]);

            // Recursively heapify the lower subtree
            heapifyDown(arr, smallestInd);
        }

        return; 
    }
    
public:
    // Method to intialize the min-heap data structure
    void initializeHeap(){
        arr.clear();
        count = 0;
    }
    
    // Method to insert a given value in the min-heap
    void insert(int key){
        // Insert the value at the back of the list 
        arr.push_back(key);
        
        // Heapify upwards
        heapifyUp(arr, count);
        count = count+1; // Increment the counter;
        
        return;
    }
        
    // Method to change the value at a given index in min-heap
    void changeKey(int index, int new_val){
        // If the current value is replaced with a smaller value
        if(arr[index] > new_val) {
            arr[index] = new_val;
            heapifyUp(arr, index);
        }

        // Else if the current value is replaced with a larger value
        else {
            arr[index] = new_val;
            heapifyDown(arr, index);
        }

        return;
    }
    
    // Method to extract the minimum value from the min-heap
    void extractMin(){
        int ele = arr[0]; // minimum value in the heap
        
        // Swap the top value with the value at last index
        swap(arr[0], arr[count-1]); 
        
        arr.pop_back(); // Pop the minimum value from the list
        count = count - 1; // Decrement the counter
        
        // Heapify the root value downwards
        heapifyDown(arr, 0);
    }
    
    // Method to return if the min-heap is empty
    bool isEmpty(){
        return (count == 0);
    }
    
    // Method to return the minimum value in the min-heap
    int getMin(){
        // Returning the value stored at the root
        return arr[0];
    }
    
    // Method to return the size of min-heap
    int heapSize(){
        return count;
    }

    void buildMinHeap(vector<int> &nums) {
          int n = nums.size();
          
          // Iterate backwards on the non-leaf nodes
          for(int i = n/2 - 1; i >= 0; i--) {
              // Heapify each node downwards
              heapifyDown(nums, i);
          }
          
          return;
      }
};
```

---

# 🔴 Max Heap

## Building Max Heap FROM ARRAY (FROM SCRATCH)

Same idea as Min Heap, but heap property is reversed.

---

### Max Heap – Build Algorithm

```
for i = (n/2 - 1) down to 0
    heapifyDown(i)
```

---

## Max Heap Property

```
For every node i:
heap[i] ≥ heap[left(i)] AND heap[i] ≥ heap[right(i)]
```

---

## 📘 Max Heap – C++ Implementation (From Scratch)

```cpp
class Solution {
private:
    vector<int> arr; // list to store the max-heap
    int count; // to store the count of elements in max-heap
    
    // Function to recursively heapify the array upwards
    void heapifyUp(int ind) {
        int parentInd = (ind - 1)/2; 

        // If current index holds larger value than the parent
        if(ind > 0 && arr[ind] > arr[parentInd]) {
            // Swap the values at the two indices
            swap(arr[ind], arr[parentInd]);
            
            // Recursively heapify the upper nodes
            heapifyUp(parentInd);
        } 

        return;
    }
    
    // Function to recursively heapify the array downwards
    void heapifyDown(int ind) {
        int n = arr.size(); // Size of the array

        // To store the index of largest element
        int largestInd = ind; 

        // Indices of the left and right children
        int leftChildInd = 2*ind + 1, rightChildInd = 2*ind + 2;
        
        // If the left child holds larger value, update the largest index
        if(leftChildInd < n && arr[leftChildInd] > arr[largestInd]) 
            largestInd = leftChildInd;

        // If the right child holds larger value, update the largest index
        if(rightChildInd < n && arr[rightChildInd] > arr[largestInd]) 
            largestInd = rightChildInd;

        // If the largest element index is updated
        if(largestInd != ind) {
            // Swap the largest element with the current index
            swap(arr[largestInd] , arr[ind]);

            // Recursively heapify the lower subtree
            heapifyDown(largestInd);
        }

        return; 
    }
    
public:
    // Method to intialize the max-heap data structure
    void initializeHeap(){
        arr.clear();
        count = 0;
    }
    
    // Method to insert a given value in the max-heap
    void insert(int key){
        // Insert the value at the back of the list 
        arr.push_back(key);
        
        // Heapify upwards
        heapifyUp(count);
        count = count + 1; // Increment the counter;
        
        return;
    }
        
    // Method to change the value at a given index in max-heap
    void changeKey(int index, int new_val){
        // If the current value is replaced with a larger value
        if(arr[index] < new_val) {
            arr[index] = new_val;
            heapifyUp(index);
        }

        // Otherwise (if the current value is replaced with smaller value)
        else {
            arr[index] = new_val;
            heapifyDown(index);
        }

        return;
    }
    
    // Method to extract the maximum value from the max-heap
    void extractMax(){
        int ele = arr[0]; // maximum value in the heap
        
        // Swap the top value with the value at last index
        swap(arr[0], arr[count-1]); 
        
        arr.pop_back(); // Pop the maximum value from the list
        count = count - 1; // Decrement the counter
        
        // Heapify the root value downwards
        heapifyDown(0);
    }
    
    // Method to return if the max-heap is empty
    bool isEmpty(){
        return (count == 0);
    }
    
    // Method to return the maximum value in the max-heap
    int getMax(){
        // Return the value stored at the root
        return arr[0];
    }
    
    // Method to return the size of max-heap
    int heapSize(){
        return count;
    }

    void buildMaxHeap(vector<int> &nums) {
        int n = nums.size();
        
        // Iterate backwards on the non-leaf nodes
        for(int i = n/2 - 1; i >= 0; i--) {
            // Heapify each node downwards
            heapifyDown(nums, i);
        }
        
        return;
    }
};
```

---

# ⏱ Time & Space Complexity

## Heapify Complexity (INTERVIEW FAVORITE)

| Operation          | Time     |
| ------------------ | -------- |
| Heapify Up         | O(log n) |
| Heapify Down       | O(log n) |
| Build Heap (array) | **O(n)** |

👉 Important: **Building heap is O(n), NOT O(n log n)**.

---

| Operation   | Min Heap | Max Heap |
| ----------- | -------- | -------- |
| Insert      | O(log n) | O(log n) |
| Delete      | O(log n) | O(log n) |
| Get Min/Max | O(1)     | O(1)     |
| Space       | O(n)     | O(n)     |

---

# 🎯 When to Use Heap

✔ Need fast min/max repeatedly
✔ Priority-based processing
✔ Top-K problems
✔ Scheduling systems

---

# 🛑 When NOT to Use Heap

✖ Need full sorted order
✖ Random access required
✖ Frequent search of arbitrary element

---

# 🔄 Comparison with Other Data Structures

| Structure    | Get Min  | Insert   | Delete   |
| ------------ | -------- | -------- | -------- |
| Heap         | O(1)     | O(log n) | O(log n) |
| Sorted Array | O(1)     | O(n)     | O(n)     |
| BST          | O(log n) | O(log n) | O(log n) |

---

# 🌍 Real-World Applications

* CPU scheduling
* Dijkstra’s algorithm
* Load balancing
* Event simulation
* Streaming data (Top-K)

---

# 💬 Interview Q&A

### Q1: Why heap uses array instead of pointers?

Array representation is compact and cache-friendly.

### Q2: Why heap height is log n?

Because it is a complete binary tree.

### Q3: Difference between heap and BST?

Heap enforces partial order; BST enforces total order.

### Q4: Can heap be used for sorting?

Yes, via Heap Sort.

---

# 🎯 Final Takeaway

> **Heaps provide efficient priority-based access but do not maintain full ordering.**

Understanding heap internals and being able to code them from scratch is a **core SDE interview skill**.

---

Repository complete.
