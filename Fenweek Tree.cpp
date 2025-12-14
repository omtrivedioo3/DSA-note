// A Fenwick Tree (Binary Indexed Tree) is a compact data structure that supports:
// Point updates
// Prefix sums
// Range sum queries
// All in O(log n) time.

//   You only need one operation (usually sum)
// Fenwick supports only operations that are:
// prefix-computable
// invertible
// associative
// (i.e., sum, xor — NOT min/max)

// Time Complexity
// Operation	Time
// Update	O(log n)
// Prefix sum	O(log n)
// Range sum	O(log n)
// Space	O(n)

// i += (i & -i)  → jump to next responsible index
// i -= (i & -i)  → move to parent segment


// Fenwick Tree vs Segment Tree Table
// Feature         	Fenwick Tree	       Segment Tree
// Point update	      ✔ O(log n)	         ✔ O(log n)
// Range sum	          ✔ O(log n)	         ✔ O(log n)
// Range min/max	      ❌ No	               ✔ Yes
// Range update	        ⚠ Hard	           ✔ Lazy works
// Multiple ops	      ❌ No              	✔ Yes
// Memory	            ✔ O(n)	             ❌ O(4n)
// Simplicity	       ✔ Easy	              ❌ Hard
// Speed	             ✔ Faster	           ❌ Slightly slower

class Fenwick {
public:
    int n;
    vector<long long> bit;     // 1-indexed BIT array

    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // Build BIT from an array
    Fenwick(vector<long long> &a) {
        n = a.size();
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            add(i, a[i]);
    }

    // Add value 'val' to index i (0-indexed)
    void add(int i, long long val) {
        for (++i; i <= n; i += (i & -i))
            bit[i] += val;
    }

    // Prefix sum query: sum(a[0..i])
    long long sum(int i) {
        long long s = 0;
        for (++i; i > 0; i -= (i & -i))
            s += bit[i];
        return s;
    }

    // Range sum query: sum(a[l..r])
    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
