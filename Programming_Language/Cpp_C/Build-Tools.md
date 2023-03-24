# ng

> Generate ninja

[official doc](https://chromium.googlesource.com/chromium/src/tools/gn/+/48062805e19b4697c5fbd926dc649c78b6aaa138/docs/language.md)

## languages

### strings

```
a = "mypath"
b = "$a/foo.cc"  # b -> "mypath/foo.cc"
c = "foo${a}bar.cc"  # c -> "foomypathbar.cc"
```

### lists

```
a = [ "first" ]
a += [ "second" ]  # [ "first", "second" ]
a += [ "third", "fourth" ]  # [ "first", "second", "third", "fourth" ] 
b = a + [ "fifth" ]  # [ "first", "second", "third", "fourth", "fifth" ] 
a = [ "first", "second", "third" ]
b = a[1]  # -> "second"
```

### conditions

```
if (is_linux || (is_win && target_cpu == "x86")) {
	sources -= [ "something.cc" ]
} else if (...) {
	...
} else {
	...
}
```

### functions

#### simple

```
print("hello, world")
assert(is_win, "This should only be executed on Windows")
```

```
static_library("mylibrary") {
  sources = [ "a.cc" ]
}
```

## Naming

### file and directory

the default form is relative

```
"foo.cc"
"src/foo.cc"
"../src/foo.cc"
```

source tree absolute names

```
"//net/foo.cc"
"//base/test/foo.cc"
```

### labels

## Target Declartion

### execution

### group

This target type allows you to create meta-targets that just collect a set of dependencies into one named target. Groups can additionally specify configs that apply to their dependents.

### static_library

### shared_library