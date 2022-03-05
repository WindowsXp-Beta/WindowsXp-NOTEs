# Optimization Note

CPE ( cycles per element )

计算方法：$T = CPE\times n+Overhead$

n是问题规模，T以时钟周期为单位。

延迟：完成运算所需要的总时间

发射时间：两个连续同类型运算之间需要的最小时钟周期数。

容量：执行该运算的功能单元的数量。

吞吐量：每时钟周期发射多少个操作。*容量除以发射时间*



## 优化方法

### code motion 代码移动

```c
for (int i; i < strlen(str); i++);
/* TO */
int length = strlen(str);
for (int i; i < length; i++);
```

### Reducing Procedure Calls 减少过程调用

有可能破坏封装

### 消除不必要的内存引用

```c
```

