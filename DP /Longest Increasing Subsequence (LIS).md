# Longest Increasing Subsequence (LIS) – Complete DP Master Guide

## 📌 Repository: `longest-increasing-subsequence`

This repository provides a **complete, interview-grade deep dive** into the **Longest Increasing Subsequence (LIS)** problem.

It covers **ALL standard approaches** expected in SDE interviews:

* Recursion (brute force intuition)
* Memoization (Top-down DP)
* Tabulation (Bottom-up DP)
* Space Optimization
* Printing the actual LIS

This README is structured exactly like a **professional GitHub repository** and is suitable for **top MNC SDE interviews**.

---

# 📘 Problem Definition

Given an integer array `nums`, find:

1. **Length of the Longest Increasing Subsequence**
2. **Print one such LIS**

> A subsequence is a sequence that can be derived by deleting elements **without changing order**.

Example:

```
Input:  [10, 9, 2, 5, 3, 7, 101, 18]
Output: Length = 4
One LIS = [2, 3, 7, 101]
```

---

# 🧠 Core DP Intuition (VERY IMPORTANT)

At every index, you have two choices:

```
Take current element  OR  Skip current element
```

But you can only **take** it if it is **greater than the previously taken element**.

This decision-making forms the basis of DP.

---

# 📊 State Definition (Interview Critical)

Let:

```
dp[i][prev]
```

Represent:

* `i` → current index
* `prev` → index of previous element included in LIS (`-1` if none)

---

# 1️⃣ Recursive Solution (Brute Force)

## Idea

Try all subsequences.

## Code (Recursion)

```cpp
int solve(int idx, int prev, vector<int>& nums) {
    if(idx == nums.size()) return 0;

    int notTake = solve(idx + 1, prev, nums);
    int take = 0;

    if(prev == -1 || nums[idx] > nums[prev])
        take = 1 + solve(idx + 1, idx, nums);

    return max(take, notTake);
}
```

## Complexity

* Time: **O(2^n)** ❌
* Space: O(n) recursion stack

---

# 2️⃣ Memoization (Top-Down DP)

## Idea

Store overlapping subproblems.

## Code (Memoization)

```cpp
int solve(int idx, int prev, vector<int>& nums, vector<vector<int>>& dp) {
    if(idx == nums.size()) return 0;
    if(dp[idx][prev + 1] != -1) return dp[idx][prev + 1];

    int notTake = solve(idx + 1, prev, nums, dp);
    int take = 0;

    if(prev == -1 || nums[idx] > nums[prev])
        take = 1 + solve(idx + 1, idx, nums, dp);

    return dp[idx][prev + 1] = max(take, notTake);
}
```

## Complexity

* Time: **O(n²)**
* Space: **O(n²)**

---

# 3️⃣ Tabulation (Bottom-Up DP)

## DP Table Meaning

```
dp[i][j] = LIS starting at i with previous index j-1
```

## Code (Tabulation)

```cpp
int lis(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int idx = n - 1; idx >= 0; idx--) {
        for(int prev = idx - 1; prev >= -1; prev--) {
            int notTake = dp[idx + 1][prev + 1];
            int take = 0;
            if(prev == -1 || nums[idx] > nums[prev])
                take = 1 + dp[idx + 1][idx + 1];
            dp[idx][prev + 1] = max(take, notTake);
        }
    }
    return dp[0][0];
}
```

## Complexity

* Time: **O(n²)**
* Space: **O(n²)**

---

# 4️⃣ Space Optimization

## Idea

We only need the next row.

## Code (Space Optimized)

```cpp
int lis(vector<int>& nums) {
    int n = nums.size();
    vector<int> next(n + 1, 0), cur(n + 1, 0);

    for(int idx = n - 1; idx >= 0; idx--) {
        for(int prev = idx - 1; prev >= -1; prev--) {
            int notTake = next[prev + 1];
            int take = 0;
            if(prev == -1 || nums[idx] > nums[prev])
                take = 1 + next[idx + 1];
            cur[prev + 1] = max(take, notTake);
        }
        next = cur;
    }
    return next[0];
}
```

## Complexity

* Time: **O(n²)**
* Space: **O(n)**

---

# 5️⃣ Printing the LIS (MOST ASKED)

## Idea

Use `parent` array to reconstruct sequence.

## Code (Print LIS)

```cpp
vector<int> printLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1), parent(n);
    int last = 0, len = 1;

    for(int i = 0; i < n; i++) parent[i] = i;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if(dp[i] > len) {
            len = dp[i];
            last = i;
        }
    }

    vector<int> lis;
    while(parent[last] != last) {
        lis.push_back(nums[last]);
        last = parent[last];
    }
    lis.push_back(nums[last]);
    reverse(lis.begin(), lis.end());
    return lis;
}
```

---

# 6️⃣ Binary Search Approach (Patience Sorting – O(n log n))

## Idea (INTERVIEW FAVORITE)

We maintain a temporary array `tails[]` where:

> `tails[i]` = **smallest possible tail value of an increasing subsequence of length `i+1`**

This array is always **sorted**, so we can apply **binary search**.

---

## Text-Based Visualization

Example:

```
nums = [10, 9, 2, 5, 3, 7, 101, 18]
```

Step-by-step tails:

```
10
9
2
2 5
2 3
2 3 7
2 3 7 101
2 3 7 18
```

Length of `tails` = **LIS length = 4**

---

## C++ Code – Binary Search LIS (Length Only)

```cpp
int lisBinarySearch(vector<int>& nums) {
    vector<int> tails;

    for(int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if(it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    return tails.size();
}
```

---

## Complexity

* **Time:** O(n log n)
* **Space:** O(n)

⚠️ This method **does NOT directly print LIS** without extra bookkeeping.

---

# 7️⃣ Number of Longest Increasing Subsequences (COUNT LIS)

## Problem Statement

Find **how many LIS exist** (not just length).

Example:

```
nums = [1,3,5,4,7]
Output: 2
```

LIS = [1,3,5,7] and [1,3,4,7]

---

## DP Idea

We maintain two arrays:

* `len[i]` → length of LIS ending at `i`
* `cnt[i]` → number of LIS ending at `i`

---

## Transition Logic (VERY IMPORTANT)

For every pair `j < i`:

```
if nums[j] < nums[i]:
  if len[j] + 1 > len[i]:
      len[i] = len[j] + 1
      cnt[i] = cnt[j]
  else if len[j] + 1 == len[i]:
      cnt[i] += cnt[j]
```

---

## C++ Code – Count LIS

```cpp
int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> len(n, 1), cnt(n, 1);

    int maxLen = 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[j] < nums[i]) {
                if(len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
        maxLen = max(maxLen, len[i]);
    }

    int result = 0;
    for(int i = 0; i < n; i++) {
        if(len[i] == maxLen)
            result += cnt[i];
    }
    return result;
}
```

---

# 🔄 Comparison with Other Approaches

| Approach        | Time  | Space | Prints LIS |
| --------------- | ----- | ----- | ---------- |
| Recursion       | O(2ⁿ) | O(n)  | ❌          |
| Memoization     | O(n²) | O(n²) | ❌          |
| Tabulation      | O(n²) | O(n²) | ❌          |
| Parent Tracking | O(n²) | O(n)  | ✔          |

---

# 🎯 When to Use LIS DP

✔ Sequence analysis problems
✔ Scheduling problems
✔ Optimization problems

---

# 🛑 When NOT to Use

✖ When order doesn’t matter
✖ For contiguous subarrays

---

# 🌍 Real-World Applications

* Stock price trend analysis
* Version control diff tools
* Bioinformatics (DNA sequence alignment)
* Task scheduling

---

# 💬 Interview-Ready Q&A

### Q1: Why is LIS O(n²) DP acceptable?

Because constraints are usually ≤ 2000.

### Q2: Can LIS be solved in O(n log n)?

Yes (Patience Sorting), but printing LIS is harder.

### Q3: Difference between subsequence and subarray?

Subsequence is non-contiguous.

---

# 🎯 Final Takeaway

> **LIS is a classic DP problem that tests recursion, DP optimization, and sequence reconstruction.**



Repository complete.
