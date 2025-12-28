# 📘 String Dynamic Programming Algorithms – Complete Interview Repository

This repository-style **README.md** is curated for **SDE interviews at top MNCs**. It deeply covers **string DP problems that look similar but behave very differently**, a common interview trap.

Algorithms covered:

1. **Longest Common Substring (LCSubstr)** – length + actual substring
2. **Longest Common Subsequence (LCS)**

   * Memoization (Top-Down)
   * Tabulation (Bottom-Up)
   * Space Optimization
   * Reconstruction of the subsequence
3. **Longest Palindromic Substring (LPS – substring)**

---

## 📂 Repository Structure

```
string-dp-interview/
│
├── README.md   # Complete theory + C++ code + interview notes
```

---

# 1️⃣ Longest Common Substring (LCSubstr)

## 🔍 Problem Statement

Given two strings `s` and `t`, find the **longest substring (contiguous)** common to both strings and return the substring.

---

## 🧠 Core Intuition

Substring means **characters must be continuous**.

* Match → grow diagonally
* Mismatch → reset to `0`

---

## 📐 DP Definition

`dp[i][j]` = length of longest common substring **ending at** `s[i-1]` and `t[j-1]`

### Transition

```
if s[i-1] == t[j-1]
    dp[i][j] = 1 + dp[i-1][j-1]
else
    dp[i][j] = 0
```

---

## 🖼️ Text Diagram

```
s =  a b c d e
     | |   | |
t =  a b x d e

Only diagonal growth allowed
Mismatch breaks substring
```

---

## ✅ Examples

### Example 1

```
Input:
  s = "abcde"
  t = "abfce"

Output:
  "ab"
```

**Explanation:** Only `"ab"` appears contiguously in both strings.

### Example 2

```
Input:
  s = "zxabcdezy"
  t = "yzabcdezx"

Output:
  "abcdez"
```

**Explanation:** Continuous match of length 6.

---

## 💻 C++ Implementation (Length + Substring)

```cpp
string longestCommonSubstring(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    int len = 0, end = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                if (dp[i][j] > len) {
                    len = dp[i][j];
                    end = i;
                }
            }
        }
    }
    return s.substr(end - len, len);
}
```

---

## ⏱️ Complexity

| Time     | Space    |
| -------- | -------- |
| O(n × m) | O(n × m) |

---

## ✅ When to Use

* Pattern matching
* DNA / gene similarity
* Plagiarism detection

## ❌ When NOT to Use

* When skipping characters is allowed → use **LCS**

---

# 2️⃣ Longest Common Subsequence (LCS)

## 🔍 Problem Statement

Find the **longest sequence** that appears in both strings **in order**, but **not necessarily contiguous**, and also return the sequence.

---

## 🧠 Key Insight

| Substring  | Subsequence         |
| ---------- | ------------------- |
| Continuous | Can skip characters |
| Reset to 0 | Take max            |

---

## 📐 DP Definition

`dp[i][j]` = length of LCS of `s[0..i-1]` and `t[0..j-1]`

### Transition

```
if s[i-1] == t[j-1]
    dp[i][j] = 1 + dp[i-1][j-1]
else
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

---

## ✅ Examples

### Example 1

```
Input:
  s = "abcde"
  t = "ace"

Output:
  "ace"
```

**Explanation:** Characters are in order but not contiguous.

### Example 2

```
Input:
  s = "AGGTAB"
  t = "GXTXAYB"

Output:
  "GTAB"
```

**Explanation:** Classic textbook LCS example.

---

## 🔁 2.1 Memoization (Top-Down)

```cpp
int solve(int i, int j, string &s, string &t, vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i-1] == t[j-1])
        return dp[i][j] = 1 + solve(i-1, j-1, s, t, dp);
    return dp[i][j] = max(solve(i-1, j, s, t, dp),
                           solve(i, j-1, s, t, dp));
}
```

---

## 📊 2.2 Tabulation + Subsequence Reconstruction

```cpp
string lcs(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    string ans = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) {
            ans.push_back(s[i-1]);
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
```

---

## ♻️ 2.3 Space Optimized LCS (Length Only)

```cpp
int lcsLength(string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> prev(m+1, 0), cur(m+1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1])
                cur[j] = 1 + prev[j-1];
            else
                cur[j] = max(prev[j], cur[j-1]);
        }
        prev = cur;
    }
    return prev[m];
}
```

⚠️ **Note:** Space optimization does **not support reconstruction**.

---

## 🌍 Real-World Applications

* Git diff / merge tools
* DNA alignment
* Version control systems

---

# 3️⃣ Longest Palindromic Substring

## 🔍 Problem Statement

Find the **longest contiguous substring** of a string that is a palindrome.

---

## ❌ Common Interview Trap

> LCS(s, reverse(s)) ❌ **does NOT give longest palindromic substring**

Reason: index alignment is not guaranteed.

---

## ✅ Examples

### Example 1

```
Input:
  s = "babad"

Output:
  "bab"  ("aba" is also valid)
```

### Example 2

```
Input:
  s = "cbbd"

Output:
  "bb"
```

### Example 3

```
Input:
  s = "forgeeksskeegfor"

Output:
  "geeksskeeg"
```

---

## ✅ Best Interview Approach: Expand Around Center

### Idea

Each palindrome expands from its center (odd & even).

---

## 🖼️ Diagram

```
   g e e k s s k e e g
           ↑
   expand left & right
```

---

## 💻 C++ Implementation

```cpp
class Solution {
public:
    int expand(string &s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--; r++;
        }
        return r - l - 1;
    }

    string longestPalindrome(string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            int len1 = expand(s, i, i);
            int len2 = expand(s, i, i + 1);
            int len = max(len1, len2);
            if (len > end - start) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};
```

---

## ⏱️ Complexity

| Time  | Space |
| ----- | ----- |
| O(n²) | O(1)  |

---

## ⚖️ Comparison Summary

| Algorithm             | Continuous | Skipping | Reconstruction |
| --------------------- | ---------- | -------- | -------------- |
| LC Substring          | ✅          | ❌        | ✅              |
| LCS                   | ❌          | ✅        | ✅              |
| Space-Optimized LCS   | ❌          | ✅        | ❌              |
| Palindromic Substring | ✅          | ❌        | ✅              |

---

## 🎯 Interview-Ready Notes

* Reset to `0` → substring
* `max()` on mismatch → subsequence
* LCS(reverse) = **palindromic subsequence**, not substring
* Space optimization loses path info

---

## ❓ Interview Q&A

**Q: Why can’t we reconstruct LCS in space-optimized DP?**
A: Previous states are overwritten, path info is lost.

**Q: Best palindrome approach for interviews?**
A: Expand Around Center — clean and optimal.

**Q: Can Manacher’s do better?**
A: Yes (O(n)), but rarely expected.

---

## ✅ Final Takeaway

These problems are frequently confused in interviews. **Correct identification + explanation of trade-offs** matters more than code length.

📌 *If you can explain why an approach fails, you stand out as a strong SDE candidate.*
