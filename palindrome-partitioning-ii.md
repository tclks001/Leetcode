
> Problem: [132. 分割回文串 II](https://leetcode.cn/problems/palindrome-partitioning-ii/description/)

# 思路

- 前缀哈希求回文，动态规划。

# 解题过程

## 心路历程：
### 1. 暴力DP
- 如果`s`是回文串，则 $$minCut(s)=0$$
- 否则在某处把`s`分为`s1`和`s2`， $$minCut(s)=min(minCut(s1)+minCut(s2)+1)$$
- 记忆化一下，最多算 $$n^2$$ 个
- 算一个的时间也是 $$n$$ ，算下来就是 $$O(n^3)$$ ，会超时
### 2. 二分答案
- 要是知道应该怎么分，直接分就好了。二分答案不行
### 3. 回文DP
- 假设`dp[i]`表示字符串`s[0~i]`的最少切割次数
- 如果`s[i]`加入进来无法形成回文串，则 $$dp[i]=dp[i-1]+1$$
- 如果`s[k~i]`能形成回文串，则 $$dp[i]=dp[k-1]+1$$
#### 需要解决的问题：
- 从 $$i$$ 往前算当前是不是回文串，能不能 $$O(n)$$ ?
### 4. 回文前缀哈希
- 如果一段字符串从前或者从后哈希一样，则回文。
- 我们要计算`[0,i]`的字符串中，所有满足`[k,i]`是回文串的k的位置。
- 也就是说，需要从两个不同的方向分别求出`[x,i]`的字符串哈希。
- 假设我们已经求出了`[x+1,i]`在两个方向上的哈希值。假设前缀哈希为`H`，后缀哈希为`R`，选择的大质数是`P`

在计算到`[x+1,i]`时，当前的哈希值为

$$H=s[x+1]*P^{i-x-1}+...+s[i-1]*P+s[i]$$

$$R=s[x+1]+s[x+2]*P+...+s[i]*P^{i-x-1}$$
- 现在我们需要求`[x,i]`时的哈希值

$$H=s[x]*P^{i-x}+...+s[i-1]*P+s[i]$$

$$R=s[x]+s[x+1]*P+...+s[i]*P^{i-x-1}$$

- 对比可发现，可通过一个递推关系进行`H`和`R`的更新

$$H = H + Pn * s[x]$$

$$R = P * R + s[x]$$

其中`Pn`每次递归自乘一个`P`

- 如果`H==R`，则说明`[x,i]`回文。
## 思路总结
- 我们需要一个函数，以 $$O(n)$$ 求出一个字符串从中间的某个位置到结尾是回文子串的索引位置
- 我们获得了这个索引集，就可以进行动态规划了。
- 如果`[0,i]`是回文串，那么 $$dp[i]=0$$
- 如果`[x,i]`是回文串，那么 $$dp[i]=min(dp[i],dp[x-1]+1)$$
# 复杂度

- 时间复杂度:  $$O(n^2)$$ （遍历 $$n$$ ，求回文位置和比较 $$n$$ ）
- 空间复杂度:  $$O(n)$$ （保存动态规划的状态）

# Code
```C++ []
class Solution {
    const int P = 19260817;
    vector<int> pos(const string& s) {
        int n = s.size();
        unsigned long long H = s[n - 1], R = s[n - 1];
        unsigned long long Pn = P;
        vector<int> res(1, n - 1);
        for (int i = n - 2; i >= 0; --i) {
            H = H + Pn * s[i];
            R = P * R + s[i];
            Pn = Pn * P;
            if (H == R) {
                res.push_back(i);
            }
        }
        return res;
    }

public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, 10000);
        for (int i = 0; i < n; ++i) {
            vector<int> tmp = pos(s.substr(0, i + 1));
            // [0,i]本身就是回文串
            if (*(tmp.end() - 1) == 0) {
                dp[i] = 0;
            } else {
                for (int& p : tmp) {
                    dp[i] = min(dp[i], dp[p - 1]);
                }
                ++dp[i];
            }
        }
        return dp[n - 1];
    }
};
```
  
