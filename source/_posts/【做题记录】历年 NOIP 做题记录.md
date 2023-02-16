---
title: 【做题记录】历年 NOIP 做题记录

date: 2022-11-16 21:28:32

description: 本文为历年 NOIP 的做题记录。

katex: true

tags:

- 做题记录
 
categories: 

- OI

- 历年真题

sticky: 1

cover: /img/12.jpg
---

## NOIP 2016

### D1T1 玩具谜题

- [题目链接](https://www.luogu.com.cn/problem/P1563) {% label AC green %}

题解：

{% note success flat %}

依题意模拟即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/19612125)

------

### D1T2 蚯蚓

- [题目链接](https://www.luogu.com.cn/problem/P2827) {% label AC green %}

题解：

{% note success flat %}

可以发现，每秒产生的两种蚯蚓的长度都是单调不增的，因此用三个队列维护所有的蚯蚓即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/94383339)

------

### D1T3 换教室

- [题目链接](https://www.luogu.com.cn/problem/P1850) {% label AC green %}

题解：

{% note success flat %}

注意到每条路径的贡献仅取决于这条路径所对应的两个时间段是否提出了更换教室的申请，因此记 $f_{i, j, 0/1}$ 表示考虑第 $i\sim n$ 节课，一共提出了 $j$ 次申请，第 $i + 1$ 节课是否提出了申请的答案，转移是平凡的。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/94840233)

------

### D2T1 组合数问题

- [题目链接](https://www.luogu.com.cn/problem/P2822) {% label AC green %}

题解：

{% note success flat %}

注意到从 $\displaystyle \binom{n}{m}$ 转变为 $\displaystyle \binom{n}{m + 1}$ 的过程相当于乘上一个数再除以一个数，因此我们可以先预处理出所有数的质因数分解，然后动态维护每一个组合数的质因数分解，并判断其是否能被 $k$ 整除即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/94850780)

------

### D2T2 愤怒的小鸟

- [题目链接](https://www.luogu.com.cn/problem/P2831) {% label AC green %}

题解：

{% note success flat %}

对于给定的两个点，我们可以很方便地求出经过它们的曲线所对应的 $a$ 和 $b$，那么我们考虑预处理出经过点 $i$ 和点 $j$ 的曲线能够经过的所有点的集合 $curve_{i, j}$。

考虑设 $f_S$ 表示干掉集合 $S$ 内的所有猪至少需要多少只小鸟，转移时可以考虑刷表法，枚举 $i$ 和 $j$，并执行 $f_{S~\cup~curve_{i, j}} \gets f_S + 1$。

这个做法的复杂度是 $\mathcal{O}(Tn^22^n)$ 的。不过，我们注意到，对于第一只不存在于 $S$ 内的猪，它早晚都需要被干掉，我们不如固定 $i$ 为其，那么我们就仅需枚举 $j$ 了，复杂度降至 $\mathcal{O}(Tn2^n)$。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/95085778)

------

### D2T3 天天爱跑步

- [题目链接](https://www.luogu.com.cn/problem/P1600) {% label AC green %}

题解：

{% note success flat %}

把每个玩家到达每个节点的时间写出来，那么我们相当于要判断每个节点上有多少个等式是成立的。

我们考虑把每个玩家的贡献在树上差分，然后再 $\mathcal{DFS}$ 一遍以统计子树内的贡献和即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/95107477)

------

## NOIP 2017

### D1T1 小凯的疑惑

- [题目链接](https://www.luogu.com.cn/problem/P3951) {% label AC green %}

题解：

{% note success flat %}

根据赛瓦维斯特定理可得答案为 $a\cdot b - a - b$。

~~证明摆烂。~~

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/95111838)

------

### D1T2 时间复杂度

- [题目链接](https://www.luogu.com.cn/problem/P3952) {% label AC green %}

题解：

{% note success flat %}

先用栈模拟一遍所有的循环体并判断 `ERR` 的情况，然后再用栈模拟一遍所有的循环体，根据每个循环体是否会进入计算复杂度即可。

记录一个踩了坑的地方：一个循环体即使不会进入，同样也会创建变量，并且会影响这个循环体内嵌套的其它循环体。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/95145541)

------

### D1T3 逛公园

- [题目链接](https://www.luogu.com.cn/problem/P3953) {% label AC green %}

题解：

{% note success flat %}

注意到 $k$ 最多只有 $50$，那么我们可以考虑先求出从 $1$ 号节点出发的单源最短路径，然后设 $f_{u, i}$ 表示从 $1$ 到 $u$ 的长度为 $dis_u + i$ 的路径数，转移考虑记忆化搜索即可。

如何判断无解呢？无解的情况会导致在记忆化搜索的过程中出现环形的转移，那么我们在记忆化搜索的过程中用一个数组记录一下即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/95392199)

------

## NOIP 2021

### T1 报数

- [题目链接](https://www.luogu.com.cn/problem/P7960) {% label AC green %}

题解：

{% note success flat %}

考虑先筛出所有是 $7$ 的倍数的数和十进制表示中含有数字 $7$ 的数，然后再通过后者筛出所有十进制表示中含有数字 $7$ 的数的倍数，最后再处理出每个数的下一个数应该报多少，这样所有询问均可在 $\mathcal{O}(1)$ 的时间内回答。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/94290316)

------

### T2 数列

- [题目链接](https://www.luogu.com.cn/problem/P7961) {% label AC green %}

题解：

{% note success flat %}

注意到对于一个 $a_i$ 而言，它是不会影响 $a_i$ 之前的二进制位的，而由于 $n \le 30$，所以它至多仅会影响 $a_i$ 及其之后的总共 $5$ 个二进制位，而状压这 $5$ 个二进制位的复杂度是可接受的。

因此，我们考虑设 $f_{i, j, T}$ 表示仅考虑在序列的前 $i$ 个位置上填数，使得 $S$ 中除去 $T$ 以外的部分共有 $j$ 个 $1$ 的所有方案的权值和。转移考虑从小到大枚举当前要填的数即可。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/78022616)

------

### T3 方差

- [题目链接](https://www.luogu.com.cn/problem/P7962) {% label AC green %}

题解：

{% note success flat %}

首先推导一下式子可得答案为 $\displaystyle n \cdot \sum_{i = 1}^n a_i^2 - (\sum_{i = 1}^n a_i)^2$。

发现操作的本质是交换差分，而如果差分呈单谷状排列，那么所有数都会更加紧密地靠向平均值，所以方差的最小值一定会在差分呈单谷状排列时产生。

那么我们将差分排序，然后设 $f_{i, j}$ 表示已经填了 $i$ 个差分，当前的 $\displaystyle \sum_{i = 1}^n a_i$ 为 $j$ 时最小的 $\displaystyle \sum_{i = 1}^n a_i^2$，转移时分类讨论将当前要填的差分填在左边时和填在右边时对上面两个式子的贡献即可。

设值域为 $w$，那么这样做的复杂度是 $\mathcal{O}(n^2 w)$ 的，但是由于 $a_i$ 为不降序列且 $a_i$ 远小于 $n$，所以差分数组中实际上存在很多的 $0$，而又由于它们对上面的两个式子没有贡献，因此做 $\mathcal{DP}$ 时跳过它们即可，这样复杂度就降至 $\mathcal{O}(nw^2)$ 了。

{% endnote %}

[代码实现](https://www.luogu.com.cn/record/78038305)

------

## 未完待续 ……