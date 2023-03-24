# PostgreSQL

## manipulation

启动，将log信息打印到server.log里。不加`-l /usr/local/var/postgres/server.log`则打印到终端里。

```bash
pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log start
```

查看状态。

```bash
pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log status
```

停止。

```bash
pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log stop -s -m fast
```

### psql

```bash
# Connect to the database on given server host running on given port with given username, without a password prompt:
psql -h host -p port -U username database
```

### createdb

```bash
# Create a database owned by the current user:
createdb database_name
```

### command line

```sql
-- execute a sql script
\i /path/to/sql/script.sql
\q -- exit
\dt -- shows all tables in the current schema
\c database_name -- show tables in $database_name
```

## SQL syntax

> PostgreSQL中string要使用单引号包裹 ''

### data types

#### numeric & decimal

> The types `decimal` and `numeric` are equivalent. Both types are part of the SQL standard.

usage: `numeric` can store numbers with a very large number of digits. It is especially recommended for storing monetary amounts and other quantities where exactness is required.

#### basic

|             Name              |       Aliases       |           Description            |
| :---------------------------: | :-----------------: | :------------------------------: |
|           `bigint`            |       `int8`        |    signed eight-byte integer     |
|           `boolean`           |       `bool`        |   logical Boolean (true/false)   |
|     character [ (*`n`*) ]     |  char [ (*`n`*) ]   |  fixed-length character string   |
| character varying [ (*`n`*) ] | varchar [ (*`n`*) ] | variable-length character string |
|           `integer`           |    `int`, `int4`    |     signed four-byte integer     |

#### composite data types

A *composite type* represents the structure of a row or record; it is essentially just a list of field names and their data types.

```sql
CREATE TYPE complex AS (
    r       double precision,
    i       double precision
);
```

#### json

jsonb支持索引，不存储空格，key order，duplicate key（if duplicate，last is kept）

### operator

- Arithmetic operators
- Comparison operators
- Logical operators
- Bitwise operators

#### ||

```sql
string1 || string2 || string_n
```

The PostgreSQL `||` operator allows you to concatenate 2 or more strings together.

### aggregate

#### string_agg

```sql
STRING_AGG ( expression, separator [order_by_clause] )
```

将select出来的expression用separator拼起来。

separtor因为是string，所以要用单引号包裹。

#### count

`count(*)` is the same as `count(1)`，都会返回行数

`count(columnName)`则会统计非null的行

### join

[using VS on](https://www.neilwithdata.com/join-using)

main idea: 用On的时候产生的表会有重复列（就是on的条件那列），using可以避免重复。

### subsquery

A subquery or Inner query or Nested query is a query within another PostgreSQL query and **embedded within the WHERE clause.**

A subquery is used to return data that will be used in the main query as a condition

- A subquery can have only one column in the SELECT clause, unless multiple columns are in the main query for the subquery to compare its selected columns.
- Subqueries that return more than one row can only be used with multiple value operators, such as the IN, EXISTS, NOT IN, ANY/SOME, ALL operator.

In fact these 

## CTE(with)

the **WITH query** provides a way to write auxiliary statements for use in a larger query.

> it can be only used in a query(`select ...`)

## issues encountered

1. data directory was initialized by PostgreSQL version 13, which is not compatible with this version 14.0 [ref](https://stackoverflow.com/questions/69424563/data-directory-was-initialized-by-postgresql-version-13-which-is-not-compatible)

    ```bash
    brew postgresql-upgrade-database
    ```