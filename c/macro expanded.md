# White space makes a big difference to macro expansion
```c
#define a(y) a_expanded(y)

#define a (y) a_expanded (y)
```