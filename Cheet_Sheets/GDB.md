# GDB

> my gdb cheetsheet
>
> ref: [gdb tutorial](http://www.unknownroad.com/rtfm/gdbtut/gdbtoc.html) [gdb-notes-x86-64](./gdbnotes-x86-64.pdf)

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

## check

### variable/registers

```
p /x(hexdicmal) variable_name & $register_name & call_some_function(arguments)
```

### memory

```
x/number(1,2,3...) | g(8-bytes) & w(4-bytes) & i(instruction) | x(hexdicmal)d(decimal) direct_address & $register
```

## tui

1. `gdb -tui`

2. `layout split` after gdb started

    `help layout`

    ```
    src   : Displays source and command windows.
    asm   : Displays disassembly and command windows.
    split : Displays source, disassembly and command windows.
    regs  : Displays register window.
    ```

## with qemu

qemu run with flags: `-s` `-S`

- 在启动qemu时加上-s - S 参数， 其中-s参数相当于 -gdb tcp::1234,意思是qemu监听tcp的1234端口， -S是指让qemu停在镜像的入口点

在gdb中:

`target remote localhost::${tcp_port}`

then use `continue` to launch the kernel

## Q&A

1. When I start gdb, it gives a long warning about auto-loading being declined. What's wrong?

    > [ref](http://cs107e.github.io/guides/gdb/#when-i-start-gdb-it-gives-a-long-warning-about-auto-loading-being-declined-whats-wrong)

    - Open your user config file `~/.gdbinit` **not your working directory** in an editor. If file doesn't yet exist, you will need to create it.

    - Append this line verbatim:

        ```
          set auto-load safe-path /
        ```

    - Save the file and exit your editor.

    - Run gdb again. The previous warning should be gone and and the local config file is now auto-loaded.
