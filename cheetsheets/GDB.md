# GDB

> my gdb cheetsheet
>
> ref: [gdb tutorial](http://www.unknownroad.com/rtfm/gdbtut/gdbtoc.html) gdb-notes-x86-64

## breakpoint

### view

```
i(nfo) b
```

### add

```
b function_name
b file_name:line_number
```

### remove

```
d(elete) break_point_number
dis(able) break_point_number
```

### check

### variable/registers

```
p /x(hexdicmal) variable_name & $register_name & call_some_function(arguments)
```

### memory

```
x/number(1,2,3...) | g(8-bytes) & w(4-bytes) & i(instruction) | x(hexdicmal)d(decimal) direct_address & $register
```

