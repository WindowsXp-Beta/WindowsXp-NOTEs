# DB insight

## How does InnoDB store data and index?

- 在 InnoDB 中，数据表的物理存储结构是以主键为关键字的 B+ 树，每一行数据直接就保存在 B+ 树的叶子节点上。
- 在 InnoDB 中，表的索引也是以 B+ 树的方式来存储的，和存储数据的 B+ 树的区别是，在索引树中，叶子节点保存的不是行数据，而是行的主键值。
- 如果通过索引来检索一条记录，需要先后查询索引树和数据树这两棵树：先在索引树中检索到行记录的主键值，然后再用主键值去数据树中去查找这一行数据。

## How does DB execute a SQL statement?

logical plan

<img src="https://pic3.zhimg.com/80/v2-454c1c9aed7dfc61612d9b4b22ceb47a_1440w.jpg" style="zoom:67%;" />

parse -> plan -> optimize
