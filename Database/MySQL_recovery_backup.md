# MySQL recovery & backup

- 物理备份

  包括文件夹的raw copy和存储db内容的文件。

  适合：large,important的db，which需要快速恢复。

- 逻辑备份

  存储db的逻辑结构CREATE database，CREATE TABLE语句和内容（插入语句或delimeter text files）

  适合更小的数据，或者重建数据结构。

  可移植（比如从Mysql移植到Oracle）

- Online(hot)&Offline(cold)

- local & remote backup

- snapshot backups

  > may use copy-on-write techniques，当发生写操作时，将要被改写的原数据部分进行备份。

  mysql itself does not support snapshot

  无法防止硬盘挂。

- Full & incremental backup

  bin-log:记录对于db所做的改变。
  
  增量恢复：恢复给定时间间隔内对数据库所做的change。
  
  point in time recovery：基于bin-log，typically follow一次全量恢复，然后redo data modifications直到将server恢复到指定的时间。

## backup methods

1. hot backup with mysql enterprise backup

   physical backup对于整个instance或者selected的db，table or both

   包括增量和压缩备份

2. mysqldump

   create text data files (以及包括建表声明的文件) mysqldump with -tab option

3. 在replica上做备份（如果在原server上做备份有性能问题）

   还要备份connection metadata repository和applier metadata repository无论使用哪种方式备份

4. 如果myisam table corrupt了，使用repair table或者mysaimchk -r first，99% will work。

5. 使用file system snapshot。

## recovery example

### OS crash & power failure

- disk data is avaliable after a restart

- InnoDB也许不会包含consistent数据因为crash，但是InnoDB会读取log并找到pending commits或者uncommitted的transaction。

  然后自动rollback没有commit的事务，flush commit的事务

### FS crash & hardware problem

- 格式化硬盘或者install a new one。
- 需要从backup恢复MySQL。

**combination of full backups as well as incremental backups**

#### 确定备份policy

[official doc](https://dev.mysql.com/doc/mysql-backup-excerpt/8.0/en/backup-policy.html)

1. 每周进行一次full backup

   `mysqldump --all-databases --master-data --single-transaction > backup_sunday_1_PM.sql`

   生成的文件包含一系列SQL的insert语句。

   > 需要global read lock

2. 增量备份

   start mysql server with `--log-bin` option to enable the log，log会写到bin-log file里。

   to free up disk space, purge them from time to time

   我们需要保存 incremental changes来进行增量备份，each time mysql server restart，它会创建一个新的binary log file，你也可以在运行中使用flush --logs或者mysqladmin flush-logs来关闭当前的bin-log file并开启一个新的。然后可以把老的存到安全的存储上。

#### 恢复

[official doc](https://dev.mysql.com/doc/mysql-backup-excerpt/8.0/en/recovery-from-backups.html)

1. 使用最近一次的full backup，恢复到做全量备份的时间点。

   `mysql < backup_sunday_1_PM.sql`

2. 使用增量备份继续恢复。

   `mysqlbinlog gbichot2-bin.000007 gbichot2-bin.000008 | mysql`

   > 可以每天进行一次mysqladmin flush-logs，并将这个bin-log文件保存到安全的地方。

3. 但这样还是无法恢复到最新的，只能恢复到前一天的，这是因为我们的bin-log和data存在一个地方，如果我们将bin-log存到另外一个安全的地方，就可以保留有最新的bin-log file。这可以通过在命令中指定bin-log file的存储位置来实现。

## mysqldump

什么时候使用存储过程，函数等，
